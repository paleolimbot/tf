
#' TensorFlow Sessions
#'
#' @param x An object of class 'tf_session'
#' @param export_dir A directory to a saved model
#' @param tags must include the set of tags used to identify one MetaGraphDef in
#'   the SavedModel.
#'
#' @return An object of class 'tf_session'
#' @export
#'
#' @examples
#' saved <- system.file("extdata/fashion_mnist", package = "tf")
#' session <- tf_load_session_from_saved_model(saved, "serve")
#' (graph <- tf_session_graph(session))
#' tf_graph_list_operations(graph)
#'
tf_load_session_from_saved_model <- function(export_dir, tags) {
  new_tf_session(.Call("tf_c_load_session_from_saved_model", path.expand(export_dir), tags))
}

#' @rdname tf_load_session_from_saved_model
#' @export
tf_session_graph <- function(x) {
  .Call("tf_c_session_xptr_graph", x)
}

#' @rdname tf_load_session_from_saved_model
#' @export
tf_session_run <- function(x, input_operation, output_operation, input) {
  stopifnot(
    inherits(x, "tf_session"),
    is.character(input_operation), length(input_operation) == 1,
    is.character(output_operation), length(output_operation) == 1,
    all(vapply(input, tf_tensor_valid, logical(1)))
  )

  .Call("tf_c_session_xptr_run", x, input_operation, output_operation, input)
}

new_tf_session <- function(x) {
  if (typeof(x) != "externalptr") {
    stop("`x` must be an 'externalptr'")
  }

  structure(x, class = "tf_session")
}
