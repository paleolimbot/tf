
# Keras 101!
# https://tensorflow.rstudio.com/tutorials/beginners/basic-ml/tutorial_basic_classification/
# setup once
# reticulate::virtualenv_create(
#   "keras_tutorial",
#   python = "/Library/Frameworks/Python.framework/Versions/3.6/bin/python3"
# )
# tensorflow::install_tensorflow(method = "virtualenv", envname = "keras_tutorial")

reticulate::use_virtualenv("keras_tutorial", required = TRUE)

library(keras)

fashion_mnist <- dataset_fashion_mnist()
c(train_images, train_labels) %<-% fashion_mnist$train
c(test_images, test_labels) %<-% fashion_mnist$test

class_names <- c('T-shirt/top',
                 'Trouser',
                 'Pullover',
                 'Dress',
                 'Coat',
                 'Sandal',
                 'Shirt',
                 'Sneaker',
                 'Bag',
                 'Ankle boot')

train_images <- train_images / 255
test_images <- test_images / 255

model <- keras_model_sequential()
model %>%
  layer_flatten(input_shape = c(28, 28)) %>%
  layer_dense(units = 128, activation = 'relu') %>%
  layer_dense(units = 10, activation = 'softmax')

model %>% compile(
  optimizer = 'adam',
  loss = 'sparse_categorical_crossentropy',
  metrics = c('accuracy')
)

model %>% fit(train_images, train_labels, epochs = 5, verbose = 2)

model %>% save_model_tf("inst/extdata/fashion_mnist.tf")

# also save some images as package data
tf_fashion_mnist_test_images <- test_images[1:100, , ]
usethis::use_data(tf_fashion_mnist_test_images, overwrite = TRUE)
