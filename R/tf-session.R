
#' TensorFlow Sessions
#'
#' @param x An object of class 'tf_session'
#' @param export_dir A directory to a saved model
#' @param tags must include the set of tags used to identify one MetaGraphDef in
#'   the SavedModel.
#' @param input_operation,output_operation Names of the input/output operations
#'   from the [tf_session_graph()].
#' @param input A `list()` of [tf_tensor][as_tf_tensor] or objects that can be
#'   converted to then (notably, arrays).
#'
#' @return An object of class 'tf_session'
#' @export
#'
#' @examples
#' saved <- system.file("extdata/fashion_mnist.zip", package = "tf")
#' session <- tf_load_session_from_saved_model(saved, "serve")
#' (graph <- tf_session_graph(session))
#' tf_graph_list_operations(graph)
#'
#' # run a prediction!
#' input <- as_tf_tensor(
#'   tf_fashion_mnist_test_images[1, , , drop = FALSE],
#'   .tf_ptype = "FLOAT"
#' )
#'
#' result <- tf_session_run(
#'   session,
#'   "serving_default_flatten_input",
#'   "StatefulPartitionedCall",
#'   list(input)
#' )
#'
#' result
#' as.array(result[[1]])
#'
tf_load_session_from_saved_model <- function(export_dir, tags) {
  export_dir <- path.expand(export_dir)

  # allow zipped version (prevents executable file warning in this package)
  if (!dir.exists(export_dir) && isTRUE(endsWith(export_dir, ".zip"))) {
    ex_dir <- tempfile()
    on.exit(unlink(ex_dir, recursive = TRUE))
    utils::unzip(export_dir, exdir = ex_dir)
    pb_files <- list.files(ex_dir, pattern = "\\.pb$", full.names = TRUE, recursive = TRUE)
    export_dir <- dirname(pb_files[1])
  }

  .Call("tf_c_load_session_from_saved_model", path.expand(export_dir), tags)
}

#' @rdname tf_load_session_from_saved_model
#' @export
tf_session_graph <- function(x) {
  .Call("tf_c_session_xptr_graph", x)
}

#' @rdname tf_load_session_from_saved_model
#' @export
tf_session_run <- function(x, input_operation, output_operation, input) {
  input <- lapply(input, as_tf_tensor)
  .Call("tf_c_session_xptr_run", x, input_operation, output_operation, input)
}

#' @export
format.tf_session <- function(x, ...) {
  if (externalptr_valid(x, "tf_session")) {
    sprintf("<tf_session at %s>", externalptr_addr(x))
  } else {
    sprintf("<tf_session <invalid>>")
  }
}

#' @export
print.tf_session <- function(x, ...) {
  cat(format(x))
  cat("\n")
  graph <- tf_session_graph(x)
  cat("Attached ")
  print(graph, ...)

  invisible(x)
}
