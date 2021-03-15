
#ifndef TF_UTIL_H_INCLUDED
#define TF_UTIL_H_INCLUDED

#include "tensorflow/c/c_api.h"

extern TF_Status* tf_global_status;

static inline void tf_check_status(TF_Status* status) {
    if (TF_GetCode(status) != TF_OK) {
        Rf_error(TF_Message(status));
    }
}

static inline void tf_check_trivial_alloc(void* ptr, const char* ptr_type) {
    if (ptr == NULL) {
        Rf_error("Failed to alloc a new %s", ptr_type); // # nocov
    }
}

static inline const char* tf_cstring_from_sexp(SEXP value, const char* arg) {
    if ((TYPEOF(value) != STRSXP) || (Rf_length(value) != 1)) {
        Rf_error("`%s` must be a character vector of length 1", arg);
    }

    SEXP value0 = STRING_ELT(value, 0);
    if (value0 == NA_STRING) {
        Rf_error("`%s` can't be NA_character_");
    }

    return Rf_translateCharUTF8(STRING_ELT(value, 0));
}

static inline int tf_int_from_sexp(SEXP value, const char* arg) {
    if ((TYPEOF(value) != INTSXP) || (Rf_length(value) != 1)) {
        Rf_error("`%s` must be am integer vector of length 1", arg);
    }

    return INTEGER(value)[0];
}

#endif
