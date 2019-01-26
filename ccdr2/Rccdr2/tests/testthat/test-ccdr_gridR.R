context("ccdr_gridR")

pp <- 10
nn <- 5
X.test <- matrix(runif(pp*pp), ncol = pp)
cors.test <- sparsebnUtils::cor_vector(X.test)
betas.test <- matrix(runif(pp*pp), ncol = pp)

# test_that("ccdr_gridR runs as expected", {
#     ### No error / Also tests default values for betas, nlam, gamma, eps, maxIters, alpha
#     expect_error(ccdr_gridR(cors = cors.test), NA)
# })

# test_that("Check input: rlam", {
#     ### eps is non-numeric
#     expect_error(ccdr.run(data = dat.test, lambdas.length = lambdas.length.test, rlam = "not a number"))
#
#     ### rlam is negative (note that rlam = 0 is OK)
#     expect_error(ccdr.run(data = dat.test, lambdas.length = lambdas.length.test, rlam = -1e-5))
#
#     ### Need to add a test for zero case
#
# })
