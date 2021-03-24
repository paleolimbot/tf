
test_that("tf_version() works", {
  expect_match(tf_version(), "[0-9]+\\.[0-9]+\\.[0-9]+")
})
