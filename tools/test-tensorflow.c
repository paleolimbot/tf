
#include <stdio.h>
#include <tensorflow/c/c_api.h>

int main() {
  printf("TensorFlow Version '%s'\n", TF_Version());
  return 0;
}
