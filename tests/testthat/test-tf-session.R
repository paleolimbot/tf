
test_that("tf_session_new() works", {
  graph <- tf_graph_new()
  session <- tf_session_new(graph)
  expect_s3_class(session, "tf_session")
  expect_identical(tf_session_graph(session), graph)
  tf_session_close(session)
})

test_that("tf_load_session_from_saved_model() errors", {
  expect_error(
    tf_load_session_from_saved_model("not a filename", character()),
    "Could not find SavedModel"
  )
})

test_that("tf_load_session_from_saved_model() can load the example model", {
  saved <- system.file("extdata/fashion_mnist.zip", package = "tf")
  session <- tf_load_session_from_saved_model(saved, tags = "serve")
  expect_s3_class(session, "tf_session")
  expect_match(format(session), "<tf_session at")
  expect_identical(expect_output(print(session), "<tf_session at"), session)
})

test_that("tf_session_run() works", {
  saved <- system.file("extdata/fashion_mnist.zip", package = "tf")
  session <- tf_load_session_from_saved_model(saved, tags = "serve")

  expect_error(
    tf_session_run(
      session,
      "serving_default_flatten_input",
      "StatefulPartitionedCall",
      list()
    ),
    "must feed a value"
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

  input_tensor <- as_tf_tensor(
    tf_fashion_mnist_test_images[1, , , drop = FALSE],
    .tf_ptype = "FLOAT"
  )

  result <- tf_session_run(
    session,
    "serving_default_flatten_input",
    "StatefulPartitionedCall",
    list(input_tensor)
  )

  # this should have been released and deleted by TF_SessionRun
  expect_false(tf_tensor_valid(input_tensor))

  # this should be high probably of class number 10
  expect_true(tf_tensor_valid(result[[1]]))
  expect_identical(which.max(as.array(result[[1]])), 10L)
})
