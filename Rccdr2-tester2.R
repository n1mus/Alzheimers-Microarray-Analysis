### TEST CYTOMETRY ---------------------------------------------
library("sparsebn")
library("Rccdr2")

### continuous
data(cytometryContinuous)
dat <- sparsebnData(cytometryContinuous$data, type = "c")
lambdas <- seq(1, 0.01, length = 50)
out <- ccdr2.run(dat, lambdas = lambdas, blocks.lambda = 0.01, verbose = TRUE)
out

### TEST MVTNORM ---------------------------------------------

library("mvtnorm")
library("sparsebn")
library("Rccdr2")

### Generate some random data
pp <- 50
nn <- 100

mvmean <- rep(0, pp)
mvcov <- diag(rep(1, pp))
mvcov <- random.spd(pp)
dat <- sparsebnData(rmvnorm(n = nn, mean = mvmean, sigma = mvcov), type = "c")

### Run the algorithm
lambdas <- seq(1, 1e-6, length = 50)
final.ccdr <- ccdr2.run(data = dat, lambdas = lambdas, blocks.lambda = 0.1, alpha = 3, verbose = TRUE)
