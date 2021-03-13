
#ifndef TF_UTIL_H_INCLUDED
#define TF_UTIL_H_INCLUDED

#include "tensorflow/c/c_api.h"

extern TF_Status* tf_global_status;

static inline void tf_check_trivial_alloc(void* ptr, const char* ptr_type) {
    if (ptr == NULL) {
        Rf_error("Failed to alloc a new %s", ptr_type); // # nocov
    }
}

#endif
