
#' Create TensorFlow Buffers
#'
#' These can be any binary representation but are often
#' [Protocol Buffers](https://developers.google.com/protocol-buffers).
#' Files that contain them often have a .pb extension.
#'
#' @param x An object
#' @param file A filename from which to read or write a protobuf
#' @param ... Unused
#'
#' @return An object of class 'tf_buffer'
#' @export
#'
#' @examples
#' (buf <- as_tf_buffer(charToRaw("this is a buffer")))
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
as_tf_buffer.raw <- function(x, ...) {
  .Call("tf_c_buffer_xptr_from_raw", x)
}

#' @rdname as_tf_buffer
#' @export
tf_buffer_clone <- function(x) {
  .Call("tf_c_buffer_xptr_clone_buffer_xptr", x)
}

#' @rdname as_tf_buffer
#' @export
tf_buffer_length <- function(x) {
  .Call("tf_c_buffer_xptr_length", x)
}

#' @rdname as_tf_buffer
#' @export
tf_buffer_valid <- function(x) {
  externalptr_valid(x, "tf_buffer")
}

#' @rdname as_tf_buffer
#' @export
as.raw.tf_buffer <- function(x, ...) {
  .Call("tf_c_buffer_xptr_clone_raw", x, NULL)
}

#' @rdname as_tf_buffer
#' @export
write_pb <- function(x, file) {
  x <- as_tf_buffer(x)
  con <- file(file, open = "wb")
  on.exit(close(con))
  writeBin(as.raw(x), con)
  invisible(x)
}

#' @rdname as_tf_buffer
#' @export
read_pb <- function(file) {
  con <- file(file, open = "rb")
  on.exit(close(con))
  as_tf_buffer(readBin(con, "raw", file.size(file)))
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
