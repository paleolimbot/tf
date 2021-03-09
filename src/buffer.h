
#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

// tf_buffer utilities that are needed elsewhere

void buffer_xptr_destroy(SEXP buffer_xptr);

static inline SEXP tf_buffer_xptr_from_string(const void* data, size_t length) {
    SEXP buffer_xptr = PROTECT(R_MakeExternalPtr(NULL, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(buffer_xptr, &buffer_xptr_destroy);

    TF_Buffer* buffer = TF_NewBufferFromString(data, length);
    if (buffer == NULL) {
        Rf_error("Failed to alloc (TF_NewBufferFromString)"); // # nocov
    }

    R_SetExternalPtrAddr(buffer_xptr, buffer);
    
    UNPROTECT(1);
    return buffer_xptr;
}

static inline TF_Buffer* tf_buffer_from_buffer_xptr(SEXP buffer_xptr) {
    return (TF_Buffer*) R_ExternalPtrAddr(buffer_xptr);
}
