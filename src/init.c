
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

SEXP tf_c_version();

static const R_CallMethodDef CallEntries[] = {
  {"tf_c_version", (DL_FUNC) &tf_c_version, 0},
  {NULL, NULL, 0}
};

void R_init_tf(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
