
library(tidyverse)

tensorflow_version <- desc::desc(".")$get_version() %>%
  as.character() %>%
  str_extract("^[0-9]+\\.[0-9]+\\.[0-9]+")

curl::curl_download(
  glue::glue(
    "https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-darwin-x86_64-{ tensorflow_version }.tar.gz"
  ),
  "data-raw/tensorflow.tar.gz"
)

untar("data-raw/tensorflow.tar.gz", exdir = "data-raw/tensorflow")

# Copy includes to src/ because these are only for compilation, not for sharing
# with other packages. Use tensorflow-internal so that a previously installed
# tensorflow in /usr/local/include doesn't get used accidentally.
unlink("src/include-internal/tensorflow-internal", recursive = TRUE)
fs::dir_copy(
  "data-raw/tensorflow/include/tensorflow",
  "src/include-internal/tensorflow-internal"
)

# need to update tensorflow includes because they all start with tensorflow/
tf_headers <- list.files(
  "src/include-internal/tensorflow-internal",
  recursive = TRUE,
  full.names = TRUE
)

tf_headers %>%
  walk(~{
    read_file(.x) %>%
      str_replace_all('"tensorflow/', '"tensorflow-internal/') %>%
      write_file(paste(.x, ".new"))
  })

unlink(tf_headers)
stopifnot(file.rename(paste(tf_headers, ".new"), tf_headers))

