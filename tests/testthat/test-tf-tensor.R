
test_that("tensors can be created", {
  t <- as_tf_tensor(matrix(1))
  expect_s3_class(t, "tf_tensor")
  expect_match(format(t), "<tf_tensor<DOUBLE")
  expect_output(print(t), "<tf_tensor<DOUBLE")

  attrs <- tf_tensor_attributes(t)
  expect_identical(attrs$data_type, 2L)
  expect_identical(attrs$data_type_label, "DOUBLE")
  expect_identical(attrs$length, 1)
  expect_identical(attrs$num_dims, 2L)
  expect_identical(attrs$shape, c(1, 1))
})
