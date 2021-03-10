
#' Create TensorFlow Buffers
#'
#' @param x An object
#' @param ... Unused
#'
#' @return An object of class 'tf_buffer'
#' @export
#'
#' @examples
#' (buf <- as_tf_buffer("this is a buffer"))
#' tf_buffer_length(buf)
#' tf_buffer_valid(buf)
#' as.raw(buf)
#' tf_buffer_clone(buf)
#'
as_tf_buffer <- function(x, ...) {
  UseMethod("as_tf_buffer")
}

#' @rdname as_tf_buffer
#' @export
as_tf_buffer.tf_buffer <- function(x, ...) {
  x
}

#' @rdname as_tf_buffer
#' @export
as_tf_buffer.character <- function(x, ...) {
  stopifnot(length(x) == 1, !is.na(x))
  as_tf_buffer(charToRaw(x))
}

#' @rdname as_tf_buffer
#' @export
as_tf_buffer.raw <- function(x, ...) {
  new_tf_buffer(.Call("tf_c_buffer_xptr_from_raw", x))
}

#' @rdname as_tf_buffer
#' @export
tf_buffer_clone <- function(x) {
  new_tf_buffer(.Call("tf_c_buffer_xptr_clone_buffer_xptr", x))
}

#' @rdname as_tf_buffer
#' @export
tf_buffer_length <- function(x) {
  .Call("tf_c_buffer_xptr_length", x)
}

#' @rdname as_tf_buffer
#' @export
tf_buffer_valid <- function(x) {
  .Call("tf_c_buffer_valid", x)
}

new_tf_buffer <- function(x) {
  if (typeof(x) != "externalptr") {
    stop("`x` must be an 'externalptr'")
  }

  structure(x, class = "tf_buffer")
}

#' @rdname as_tf_buffer
#' @export
as.raw.tf_buffer <- function(x, ...) {
  .Call("tf_c_buffer_xptr_clone_raw", x, NULL)
}

#' @export
format.tf_buffer <- function(x, ..., width = getOption("width")) {
  if (tf_buffer_valid(x)) {
    length <- tf_buffer_length(x)
    preview <- .Call("tf_c_buffer_xptr_clone_raw", x, as.integer(width %/% 2))
    preview <- paste0(format(preview), collapse = " ")
    sprintf("[n = %d] %s", length, substr(preview, 1, width - 10))
  } else {
    "<NULL>"
  }
}

#' @export
print.tf_buffer <- function(x, ..., width = getOption("width")) {
  cat(sprintf("<tf_buffer at %s>", externalptr_addr(x)))
  cat("\n")
  cat(format(x))
  invisible(x)
}
