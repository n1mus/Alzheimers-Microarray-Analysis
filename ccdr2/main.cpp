//
//  main.cpp
//  ccdr_proj
//
//  Created by Bryon Aragam (local) on 3/19/14.
//  Copyright (c) 2014 Bryon Aragam (local). All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <string>

#include "auxiliary.h"
#include "defines.h"
#include "algorithm.h"
#include "io.h"
#include "log.h"

bool GENERATE_NEW = false;

int main(int argc, const char * argv[]){

    #ifdef _DEBUG_ON_
        //
        // log.h logging
        //
        FILE* pFile = fopen("/Users/Zigmund-2/Desktop/ccdr2_LOG_FILE.txt", "w");
        Output2FILE::Stream() = pFile;
        FILELog::ReportingLevel() = logERROR;
        
        FILE_LOG(logINFO) << "Log file opened.";
    #endif
    
    // set seed for rand()
    srand(static_cast<unsigned int>(time(NULL)));
    
    if(GENERATE_NEW){
        //
        // Call R code from system to generate new data
        //
        printf("Checking if processor is available...");
        if(system(NULL)) puts ("Ok");
        else exit (EXIT_FAILURE);
        printf("Generating new test data in R... ");
        int system_out = system("cd /Users/Zigmund-2/Desktop/ccdr_generate/; R CMD BATCH --vanilla ccdr-generate.R ccdr-generate-1.Rout");
        if(system_out == 0) printf("Data successfully generated.\n");
        
        printf("Once data has loaded, press enter to continue...\n");
        std::cin.get();
    }
    
    //
    // Read in correlation data (generated in R)
    //
    std::vector<double> c = read_cors();
    OUTPUT << c.size() << " values read in successfully." << std::endl;
    
    //
    // Read in parameter information
    //
    std::vector<int> params = read_params();
    OUTPUT << params.size() << " values read in successfully." << std::endl << std::endl;
    
    //
    // Set CCDr parameter values
    //
    int pp_fixed = params[0];
    int nn_fixed = params[1];
    double rlam = 0.0001;
    double alpha = 3;
    int nlam = 20;
    std::vector<double> p = {2.0, 1e-2, round(sqrt(pp_fixed)), alpha, 0}; // from R: c(2.0, 1e-2, round(sqrt(pp)), 3)
    std::vector<double> lambdas = lambdaGrid(sqrt(nn_fixed), rlam * sqrt(nn_fixed), nlam);
    
    //
    // Log the model parameters and relevant test information
    //
    std::ostringstream model_info;
    model_info << "Test data information..." << std::endl << std::endl;
    model_info << "Number of nodes (pp): " << pp_fixed << std::endl;
    model_info << "Number of observations (nn): " << nn_fixed << std::endl;
    model_info << "nlam: " << nlam << std::endl;
    model_info << "gamma: " << p[0] << std::endl;
    model_info << "eps: " << p[1] << std::endl;
    model_info << "maxIters: " << p[2] << std::endl;
    model_info << "alpha: " << p[3] << std::endl;
    model_info << "rlam: " << rlam << std::endl;
    FILE_LOG(logINFO) << model_info.str();
    
    #ifdef _DEBUG_ON_
        //
        // When p is large (i.e. > 25ish), the log file will be extremely large if the debug level is
        //   3 or higher. This is because the concaveCD(Init) functions will log the numbers for each
        //   and every edge tested (whether added or not). This amount detail is only parseable for
        //   small models anyway, so we include a warning about this in case we accidentally attempt
        //   to log a huge model.
        //
        if (pp_fixed > 25 && FILELog::ReportingLevel() > logDEBUG2){
            printf("Warning: Debug level 3+ will result in extremely large log files for p > 25!\nAre you sure you want to continue? Terminate the program now or press enter to continue.");
            std::cin.get();
            printf("\np = 10 ~ 2.5MB \np = 20 ~ 15MB \np = 30 ~ 40MB");
            printf("\nAre you sure?");
            std::cin.get();
        }
    #endif
    
    //
    // Generate a random initial guess for testing
    //
    SparseMatrix b = randomSBM(pp_fixed, (int)(0.5*pp_fixed), 5);
    OUTPUT << "Dimension: " << b.dim() << std::endl;
    OUTPUT << "Active set size: " << b.activeSetSize() << std::endl;
    OUTPUT << "maxIters: " << round(sqrt(pp_fixed)) << std::endl;
    
    //
    // Instead of a random initial guess, use the zero matrix
    //
    SparseMatrix b0 = SparseMatrix(pp_fixed);

    std::vector<std::vector<int>> bl;
    for(int j = 0; j < pp_fixed; ++j){
        for(int i = 0; i < pp_fixed; ++i){
            if(i != j){
                bl.push_back({i, j});
            }
        }
    }
    
    BlockList blocks = BlockList(bl, pp_fixed);

    std::vector<double> s0(pp_fixed);
    for(int j = 0; j < s0.size(); ++j){
        s0[j] = -1.;
    }

    //
    // Run gridCCDr
    //
    clock_t t = clock();
    std::vector<SparseMatrix> grid_ccdr;
    grid_ccdr = gridCCDr(c,
        b0,
        s0, // initial value for sigmas
        nn_fixed,
        lambdas,
        p,
        1,
        blocks);
    t = clock() - t;
    OUTPUT << std::endl << "Time = " << ((float)t)/CLOCKS_PER_SEC << std::endl;

    return 0;
}

