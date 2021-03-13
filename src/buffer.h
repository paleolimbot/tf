
#ifndef TF_BUFFER_H_INCLUDED
#define TF_BUFFER_H_INCLUDED

#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

#include "util.h"

void buffer_xptr_destroy(SEXP buffer_xptr);

static inline SEXP tf_buffer_xptr_from_buffer(TF_Buffer* buffer) {
    SEXP buffer_xptr = PROTECT(R_MakeExternalPtr(buffer, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(buffer_xptr, buffer_xptr_destroy);
    Rf_setAttrib(buffer_xptr, R_ClassSymbol, Rf_mkString("tf_buffer"));
    UNPROTECT(1);
    return buffer_xptr;
}

static inline SEXP tf_buffer_xptr_from_string(const void* data, size_t length) {
    TF_Buffer* buffer = TF_NewBufferFromString(data, length);
    tf_check_trivial_alloc(buffer, "TF_Buffer");
    return tf_buffer_xptr_from_buffer(buffer);
}

static inline TF_Buffer* tf_buffer_from_buffer_xptr(SEXP buffer_xptr) {
    return (TF_Buffer*) R_ExternalPtrAddr(buffer_xptr);
}

static inline TF_Buffer* tf_buffer_checked_from_buffer_xptr(SEXP buffer_xptr) {
    if (!Rf_inherits(buffer_xptr, "tf_buffer")) {
        Rf_error("TF_Buffer* externalptr must inherit from 'tf_buffer'");
    }

    TF_Buffer* buffer = tf_buffer_from_buffer_xptr(buffer_xptr);
    if (buffer == NULL) {
        Rf_error("TF_Buffer* externalptr points to NULL");
    }

    return buffer;
}

#endif
