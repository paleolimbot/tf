
test_that("tf_load_session_from_saved_model() errors", {
  expect_error(
    tf_load_session_from_saved_model("not a filename", character()),
    "Could not find SavedModel"
  )
})

test_that("tf_load_session_from_saved_model() can load the example model", {
  saved <- system.file("extdata/fashion_mnist", package = "tf")
  session <- tf_load_session_from_saved_model(saved, tags = "serve")
  expect_s3_class(session, "tf_session")
})

test_that("tf_session_run() works", {
  saved <- system.file("extdata/fashion_mnist", package = "tf")
  session <- tf_load_session_from_saved_model(saved, tags = "serve")

  expect_error(
    tf_session_run(
      session,
      "serving_default_flatten_input",
      "StatefulPartitionedCall",
      list()
    ),
    "must feed a placeholder"
  )

  expect_error(
    tf_session_run(
      session,
      "not an input",
      "StatefulPartitionedCall",
      list()
    ),
    "Can't load input operation"
  )

  expect_error(
    tf_session_run(
      session,
      "serving_default_flatten_input",
      "not an ouutput",
      list()
    ),
    "Can't load output operation"
  )

  input_tensor <- as_tf_tensor(tf_fashion_mnist_test_images[1, , , drop = FALSE])

  result <- tf_session_run(
    session,
    "serving_default_flatten_input",
    "StatefulPartitionedCall",
    list(input_tensor)
  )

})
