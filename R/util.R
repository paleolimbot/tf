
externalptr_addr <- function(x) {
  .Call("tf_c_xptr_addr", x)
}
