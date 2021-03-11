
externalptr_addr <- function(x) {
  .Call("tf_c_xptr_addr", x)
}

new_data_frame <- function(x) {
  structure(x, row.names = c(NA, length(x[[1]])), class = "data.frame")
}
