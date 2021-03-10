
#' Title
#'
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
#'
tf_load_session_from_saved_model <- function(export_dir, tags) {
  new_tf_session(.Call("tf_c_load_session_from_saved_model", path.expand(export_dir), tags))
}

new_tf_session <- function(x) {
  if (typeof(x) != "externalptr") {
    stop("`x` must be an 'externalptr'")
  }

  structure(x, class = "tf_session")
}
