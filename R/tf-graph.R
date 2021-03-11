
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

#' @rdname tf_graph_import_graph_def
#' @export
tf_graph_list_operations <- function(x) {
  new_data_frame(.Call("tf_c_graph_xptr_list_operations", x))
}

#' @export
format.tf_graph <- function(x, ...) {
  ops <- tf_graph_list_operations(x)
  ops_lab <- if (nrow(ops) != 1) "operations" else "operation"
  sprintf("<tf_graph at %s [%d %s]>", externalptr_addr(x), nrow(ops), ops_lab)
}

#' @export
print.tf_graph <- function(x, ...) {
  cat(format(x))
  ops <- tf_graph_list_operations(x)
  if (nrow(ops) > 0) {
    print(ops, ...)
  }

  invisible(x)
}
