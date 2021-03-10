
test_that("tf_graph_new() works", {
  expect_s3_class(tf_graph_new(), "tf_graph")
})

test_that("tf_graph can be formatted and printed", {
  expect_match(format(tf_graph_new()), "<tf_graph at")
  expect_output(print(tf_graph_new()), "<tf_graph at")
})

test_that("tf_graph_import_graph_def() errors for invalid buffer", {
  expect_error(
    tf_graph_import_graph_def("this is definitely not a valid buffer"),
    "Invalid GraphDef"
  )
})
