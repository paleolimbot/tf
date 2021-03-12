
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

# some predictions so we can check results later
predictions <- model %>% predict(test_images[1:2, , , drop = FALSE])

dput(predictions[1, ])
predictions1 <- c(
  2.67113851037948e-08, 4.62104746828951e-12, 2.38624675574783e-11,
  6.06263705904553e-10, 1.00199695762804e-10, 0.0023099051322788,
  2.37655743973164e-08, 0.0459560267627239, 1.49679912908596e-08,
  0.951733946800232
)

# also save some images as package data
tf_fashion_mnist_test_images <- test_images[1:100, , ]
usethis::use_data(tf_fashion_mnist_test_images, overwrite = TRUE)
