
#' Create TensorFlow Tensors
#'
#' @param x An object to convert to a tensor
#' @param .ptype An R vector template (e.g., [double()], [integer()],
#'   [raw()], [complex()], or [character()]).
#' @param ... Unused
#'
#' @return An object of class 'tf_tensor'
#' @export
#'
#' @examples
#' (t <- as_tf_tensor(matrix(1)))
#' tf_tensor_attributes(t)
#'
as_tf_tensor <- function(x, ...) {
  UseMethod("as_tf_tensor")
}

#' @rdname as_tf_tensor
#' @export
as_tf_tensor.tf_tensor <- function(x, ...) {
  x
}

#' @rdname as_tf_tensor
#' @export
as_tf_tensor.array <- function(x, ...) {
  stopifnot(typeof(x) == "double")

  # aperm() takes care of the row-major/column-major difference
  # in the same way that keras does
  x[] <- aperm(x, rev(seq_along(dim(x))))

  .Call("tf_c_tensor_xptr_from_array_real", x)
}

#' @rdname as_tf_tensor
#' @export
tf_tensor_clone <- function(x) {
  .Call("tf_c_tensor_xptr_clone_tensor_xptr", x)
}

#' @rdname as_tf_tensor
#' @export
as.array.tf_tensor <- function(x, ..., .ptype = tf_ptype_from_tensor(x)) {
  stopifnot(tf_tensor_valid(x))
  result <- .Call("tf_c_array_real_from_tensor_xptr", x, .ptype)
  # aperm() takes care of the row-major/column-major difference
  # in the same way that keras does
  dim(result) <- rev(dim(result))
  aperm(result, rev(seq_along(dim(result))))
}

#' @rdname as_tf_tensor
#' @export
tf_ptype_from_tensor <- function(x) {
  attrs <- tf_tensor_attributes(x)
  switch(
    attrs$data_type_label,
    "FLOAT" =,
    "DOUBLE" = double(),
    stop(
      sprintf(
        "Can't automatically choose ptype for tf_tensor with data type '%s'",
        attrs$data_type_label
      )
    )
  )
}

#' Inspect Tensors
#'
#' @param x A [tf_tensor][as_tf_tensor]
#'
#' @export
#'
tf_tensor_attributes <- function(x) {
  stopifnot(tf_tensor_valid(x))
  .Call("tf_c_tensor_xptr_attributes", x)
}

#' @rdname tf_tensor_attributes
#' @export
tf_tensor_valid <- function(x) {
  externalptr_valid(x, "tf_tensor")
}

#' @export
format.tf_tensor <- function(x, ...) {
  if (!tf_tensor_valid(x)) {
    return("<tf_tensor NULL>")
  }

  attrs <- tf_tensor_attributes(x)
  sprintf(
    "<tf_tensor<%s>[%s] at %s>",
    attrs$data_type_label,
    paste0(attrs$shape, collapse = ", "),
    externalptr_addr(x)
  )
}

#' @export
print.tf_tensor <- function(x, ...) {
  cat(format(x))
  cat("\n")
  invisible(x)
}
