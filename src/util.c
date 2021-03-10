#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <memory.h>
#include <stdio.h>

SEXP tf_c_xptr_addr(SEXP buffer_xptr) {
    char buffer[256];
    memset(buffer, 0, 256);
    sprintf(buffer, "%p", R_ExternalPtrAddr(buffer_xptr));
    return Rf_mkString(buffer);
}
