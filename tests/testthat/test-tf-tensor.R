
test_that("tensors can be created", {
  t <- as_tf_tensor(matrix(1))
  expect_identical(as_tf_tensor(t), t)
  expect_s3_class(t, "tf_tensor")
  expect_match(format(t), "<tf_tensor<FLOAT")
  expect_output(print(t), "<tf_tensor<FLOAT")

  attrs <- tf_tensor_attributes(t)
  expect_identical(attrs$data_type, 1L)
  expect_identical(attrs$data_type_label, "FLOAT")
  expect_identical(attrs$length, 1)
  expect_identical(attrs$num_dims, 2L)
  expect_identical(attrs$shape, c(1, 1))

  expect_identical(
    tf_tensor_attributes(tf_tensor_clone(t)),
    tf_tensor_attributes(t)
  )

  expect_identical(as.array(t), as.array(matrix(1)))
})

test_that("tf_tensor() to array conversion works", {
  arr <- array(as.numeric(1:12), dim = c(2, 6))
  ten <- as_tf_tensor(arr)
  expect_identical(as.array(ten), arr)

  arr <- array(as.numeric(1:24), dim = c(2, 3, 4))
  ten <- as_tf_tensor(arr)
  expect_identical(as.array(ten), arr)
})
