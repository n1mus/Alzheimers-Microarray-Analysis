#' @export
ccdr2.run <- function(data,
                      lambdas = NULL,
                      blocks.lambda = 0.5,
                      error.tol = 1e-2,
                      max.iters = NULL,
                      alpha = 10,
                      verbose = FALSE
){
    # Rccdr2::ccdr.run(data, lambdas = lambdas.ls,
    #                  gamma = -1,
    #                  sigmas = rep(1, ncol(dat$data)),
    #                  blocks = -3,
    #                  blocks.lambda = ccdr.blocks.lambda,
    #                  alpha = ccdr.alpha,
    #                  verbose = verbose,
    #                  randomize = FALSE)

    nnode <- ncol(data$data)
    ccdr.run(data,
             sigmas = rep(1, nnode), ###
             lambdas = lambdas,
             blocks = -3,                     ###
             blocks.lambda = blocks.lambda,
             randomize = FALSE,               ###
             gamma = -1,                      ###
             error.tol = error.tol,
             max.iters = max.iters,
             alpha = alpha,
             verbose = verbose)
}
