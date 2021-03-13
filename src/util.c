#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <memory.h>
#include <stdio.h>

#include "tensorflow/c/c_api.h"

#include "util.h"

TF_Status* tf_global_status = NULL;

SEXP tf_c_xptr_addr(SEXP buffer_xptr) {
    char buffer[256];
    memset(buffer, 0, 256);
    sprintf(buffer, "%p", R_ExternalPtrAddr(buffer_xptr));
    return Rf_mkString(buffer);
}

SEXP tf_c_xptr_valid(SEXP xptr, SEXP cls_sexp) {
    if ((TYPEOF(cls_sexp) != STRSXP) || (Rf_length(cls_sexp) != 1)) {
        Rf_error("`class` must be a character vector of length 1");
    }

    const char* cls = Rf_translateCharUTF8(STRING_ELT(cls_sexp, 0));
    int valid = (TYPEOF(xptr) == EXTPTRSXP) && Rf_inherits(xptr, cls) && (R_ExternalPtrAddr(xptr) != NULL);
    return Rf_ScalarLogical(valid);
}
