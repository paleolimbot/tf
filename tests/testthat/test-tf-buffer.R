
test_that("tf_buffer can be created from raw and character", {
  buf <- as_tf_buffer(charToRaw("this is a buffer"))
  expect_s3_class(buf, "tf_buffer")
  expect_type(buf, "externalptr")
  expect_equal(tf_buffer_length(buf), nchar("this is a buffer"))
  expect_true(tf_buffer_valid(buf))
  expect_identical(rawToChar(as.raw(buf)), "this is a buffer")
  # force a copy of the data since the above case is optimized in C
  expect_identical(
    rawToChar(as.raw(tf_buffer_clone(as_tf_buffer(as.raw(buf))))),
    "this is a buffer"
  )

  expect_identical(as_tf_buffer(buf), buf)

  expect_identical(
    as.raw(buf),
    as.raw(as_tf_buffer(charToRaw("this is a buffer")))
  )

  expect_s3_class(as_tf_buffer(charToRaw("this is a buffer")), "tf_buffer")
  expect_type(as_tf_buffer(charToRaw("this is a buffer")), "externalptr")
})

test_that("tf_buffer can be cloned", {
  buf <- as_tf_buffer(charToRaw("this is another buffer"))
  expect_identical(
    as.raw(tf_buffer_clone(buf)),
    charToRaw("this is another buffer")
  )
})

test_that("tf_buffer can be formatted/printed", {
  buf <- as_tf_buffer(charToRaw("this is yet another buffer"))
  expect_output(print(buf), "tf_buffer at")
  expect_match(format(buf), "n = 26")

  # check reduced width
  expect_identical(format(buf, width = 0), "[n = 26] ")
  expect_identical(format(buf, width = 18), "[n = 26] 74 68 69")
})

test_that("tf_buffer invalid pointers behave as expected", {
  tmp_rds <- tempfile()
  saveRDS(as_tf_buffer(charToRaw("too many buffers")), tmp_rds)
  buf_invalid <- readRDS(tmp_rds)
  unlink(tmp_rds)

  expect_false(tf_buffer_valid(buf_invalid))
  expect_error(as.raw(buf_invalid), "points to NULL")
  expect_error(tf_buffer_clone(buf_invalid), "points to NULL")
  expect_error(tf_buffer_length(buf_invalid), "points to NULL")
  expect_identical(format(buf_invalid), "<NULL>")
  expect_output(print(buf_invalid), "tf_buffer at.*?<NULL>")
})
