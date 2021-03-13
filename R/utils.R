
externalptr_addr <- function(x) {
  .Call("tf_c_xptr_addr", x)
}

externalptr_valid <- function(x, class) {
  .Call("tf_c_xptr_valid", x, class)
}

new_data_frame <- function(x) {
  structure(x, row.names = c(NA, length(x[[1]])), class = "data.frame")
}
