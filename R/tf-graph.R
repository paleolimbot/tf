
#' Import a graph definition
#'
#' @param graph_def A [tf_buffer][as_tf_buffer] or [raw()] vector
#'   containing the
#'
#' @return An object of class 'tf_graph'.
#' @export
#'
#' @examples
#' tf_graph_new()
#'
tf_graph_import_graph_def <- function(graph_def) {
  graph_def <- as_tf_buffer(graph_def)
  .Call("tf_c_graph_xptr_import_graph_def", graph_def)
}

#' @rdname tf_graph_import_graph_def
#' @export
tf_graph_new <- function() {
  .Call("tf_c_graph_xptr_new")
}

#' @export
format.tf_graph <- function(x, ...) {
  sprintf("<tf_graph at %s>", externalptr_addr(x))
}

#' @export
print.tf_graph <- function(x, ...) {
  cat(format(x))
  invisible(x)
}
