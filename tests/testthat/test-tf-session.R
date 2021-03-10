
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
