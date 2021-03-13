
if(!file.exists("../windows/include/tensorflow/c/c_api.h")){
  if(getRversion() < "3.3.0") setInternet2()
  download.file("https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-windows-x86_64-2.4.0.zip", "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")

  # a few missing headers in the windows package that result in failed compile
  unlink("../windows/include", recursive = TRUE)
  unzip("include-2.4.0.zip", exdir = "../windows/include")
}
