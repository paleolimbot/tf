
test_that("tf_graph_import_graph_def() errors for invalid buffer", {
  expect_error(
    tf_graph_import_graph_def("this is definitely not a valid buffer"),
    "Invalid GraphDef"
  )
})

test_that("new_tf_graph() errors for non-externalptr", {
  expect_error(new_tf_graph(NULL), "must be an 'externalptr'")
})
