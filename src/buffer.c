#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <stdlib.h>

#include "tensorflow/c/c_api.h"

#include "buffer.h"
#include "util.h"

// constructors --------------

void buffer_xptr_sexp_deallocate(void* data, size_t length) {
    // buffers built on raw/character use the tag mechanism
    // to protect the underlying SEXP from garbage collection
    // while the buffer xptr is still in scope
}

void buffer_xptr_destroy(SEXP buffer_xptr) {
    TF_Buffer* buffer = (TF_Buffer*) R_ExternalPtrAddr(buffer_xptr);
    TF_DeleteBuffer(buffer);
}

SEXP tf_c_buffer_xptr_from_raw(SEXP raw_input) {
    void* buffer_data = RAW(raw_input);
    size_t buffer_length = Rf_xlength(raw_input);
    
    TF_Buffer* buffer = TF_NewBuffer();
    tf_check_trivial_alloc(buffer, "TF_Buffer");

    buffer->data = buffer_data;
    buffer->length = buffer_length;
    buffer->data_deallocator = &buffer_xptr_sexp_deallocate;

    SEXP buffer_xptr = PROTECT(tf_buffer_xptr_from_buffer(buffer));
    R_SetExternalPtrTag(buffer_xptr, raw_input);
    UNPROTECT(1);
    return buffer_xptr;
}

// accessors --------------

SEXP tf_c_buffer_xptr_clone_buffer_xptr(SEXP buffer_xptr) {
    TF_Buffer* buffer = tf_buffer_checked_from_buffer_xptr(buffer_xptr);
    return tf_buffer_xptr_from_string(buffer->data, buffer->length);
}

SEXP tf_c_buffer_xptr_clone_raw(SEXP buffer_xptr, SEXP max_length) {
    TF_Buffer* buffer = tf_buffer_checked_from_buffer_xptr(buffer_xptr);

    size_t n_copy;
    if (max_length == R_NilValue) {
        n_copy = buffer->length;
    } else {
        int n_copy_int = INTEGER(max_length)[0];
        if (n_copy_int < 0) {
            n_copy = 0;
        } else if (((size_t) n_copy_int) > buffer->length) {
            n_copy = buffer->length;
        } else {
            n_copy = n_copy_int;
        }
    }

    SEXP result = PROTECT(Rf_allocVector(RAWSXP, n_copy));

    if (n_copy > 0) {
        memcpy(RAW(result), buffer->data, n_copy);
    }

    UNPROTECT(1);
    return result;
}

SEXP tf_c_buffer_xptr_length(SEXP buffer_xptr) {
    TF_Buffer* buffer = tf_buffer_checked_from_buffer_xptr(buffer_xptr);
    return Rf_ScalarReal(buffer->length);
}
