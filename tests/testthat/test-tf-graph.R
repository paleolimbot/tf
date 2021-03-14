
test_that("tf_graph_new() works", {
  expect_s3_class(tf_graph_new(), "tf_graph")
})

test_that("tf_graph_list_operations() works", {
  expect_identical(
    tf_graph_list_operations(tf_graph_new()),
    data.frame(
      name = character(),
      op_type = character(),
      device = character(),
      num_inputs = integer(),
      num_outputs = integer()
    )
  )
})

test_that("tf_graph can be formatted and printed", {
  expect_match(format(tf_graph_new()), "<tf_graph at")
  expect_output(print(tf_graph_new()), "<tf_graph at")
})

test_that("tf_graph_import_graph_def() errors for invalid buffer", {
  expect_error(
    tf_graph_import_graph_def(tf_graph_new(), charToRaw("this is definitely not a valid buffer")),
    "Invalid GraphDef"
  )
})

test_that("tf_graph_to_graph_def() can roundtrip an empty graph", {
  roundtrip_empty <- tf_graph_import_graph_def(tf_graph_new(), tf_graph_to_graph_def(tf_graph_new()))
  expect_identical(
    tf_graph_list_operations(roundtrip_empty),
    tf_graph_list_operations(tf_graph_new())
  )
})
