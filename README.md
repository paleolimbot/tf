
<!-- README.md is generated from README.Rmd. Please edit that file -->

# tf

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![R-CMD-check](https://github.com/paleolimbot/tf/workflows/R-CMD-check/badge.svg)](https://github.com/paleolimbot/tf/actions)
<!-- badges: end -->

The goal of tf is to wrap the [TensorFlow C
API](https://www.tensorflow.org/install/lang_c). It is proof-of-concept
only at this point but is able to load and run a SavedModel exported
from keras.

## Installation

You can install the development version from
[GitHub](https://github.com/) with:

``` r
# install.packages("remotes")
remotes::install_github("paleolimbot/tf")
```

You will also need to have the [TensorFlow C
API](https://www.tensorflow.org/install/lang_c) installed. You can
install this on MacOS with Homebrew (`brew install tensorflow`). On
Linux you will need to download the API, decompress to /usr/local, and
configure the linker:

``` bash
curl https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-linux-x86_64-2.4.0.tar.gz \
  -o tensorflow.tar.gz
sudo tar -C /usr/local -xzf tensorflow.tar.gz
sudo ldconfig
```

Getting this to work on Windows is a battle for another day but a binary
of the library does exist.

## Example

This is a basic example which shows you how to solve a common problem:

``` r
library(tf)

# load a saved model!
saved <- system.file("extdata/fashion_mnist.zip", package = "tf")
session <- tf_load_session_from_saved_model(saved, "serve")

# run a prediction!
result <- tf_session_run(
  session,
  "serving_default_flatten_input",
  "StatefulPartitionedCall",
  list(tf_fashion_mnist_test_images[1, , , drop = FALSE])
)

as.array(result[[1]])
#>               [,1]
#>  [1,] 2.718336e-07
#>  [2,] 1.742129e-07
#>  [3,] 1.181251e-08
#>  [4,] 1.540148e-08
#>  [5,] 7.448015e-08
#>  [6,] 1.142487e-02
#>  [7,] 3.363150e-06
#>  [8,] 2.745604e-02
#>  [9,] 1.336718e-05
#> [10,] 9.611018e-01
```
