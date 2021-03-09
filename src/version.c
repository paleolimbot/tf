#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

SEXP tf_c_version() {
    return Rf_mkString(TF_Version());
}
