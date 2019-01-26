setup = T

if(setup) {
  ### Read in dataset
  #geneexpr <- as.data.frame(data.table::fread("~/data/datasets/alzheimers/ge.csv"))
  folder = getwd()
  setwd('~/R_workspace/daglearn')
  geneexpr <- as.data.frame(data.table::fread("alzheimers/ge.csv"))
}

nnode <- 100
cols <- 1:nnode
X <- geneexpr[, cols]
dat <- sparsebnUtils::sparsebnData(X, type = "c")

### Set up hyperparameters
lambdas.ls <- seq(1, 1e-4, length.out = 100)
lambdas.ls <- c(seq(1, 0.1, length.out = 15), 10^(seq(log10(0.1), log10(1e-4), length.out = 6)[-1]))
ccdr.blocks.lambda <- 0.8
ccdr.alpha <- 5
verbose <- TRUE

### Run algorithm
Rccdr2::ccdr.run(dat, lambdas = lambdas.ls,
                 gamma = -1,
                 sigmas = rep(1, ncol(dat$data)),
                 blocks = -3, blocks.lambda = ccdr.blocks.lambda,
                 alpha = ccdr.alpha, verbose = verbose, randomize = FALSE)

Rccdr2::ccdr2.run(dat, lambdas = lambdas.ls,
                  blocks.lambda = ccdr.blocks.lambda,
                  alpha = ccdr.alpha, verbose = verbose)
