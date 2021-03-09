
#' Import a graph definition
#'
#' @param graph_def A [tf_buffer][as_tf_buffer] or [raw()] vector
#'   containing the
#'
#' @return An object of class 'tf_graph'.
#' @export
#'
tf_graph_import_graph_def <- function(graph_def) {
  graph_def <- as_tf_buffer(graph_def)
  new_tf_graph(.Call("tf_c_graph_xptr_import_graph_def", graph_def))
}

new_tf_graph <- function(x) {
  if (typeof(x) != "externalptr") {
    stop("`x` must be an 'externalptr'")
  }

  structure(x, class = "tf_graph")
}
