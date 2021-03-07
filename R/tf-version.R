
#' TensorFlow information
#'
#' @export
#'
#' @examples
#' tf_version()
#'
tf_version <- function() {
  .Call("tf_c_version")
}
