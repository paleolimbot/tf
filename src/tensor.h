
#ifndef TF_TENSOR_H_INCLUDED
#define TF_TENSOR_H_INCLUDED

#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

void tensor_xptr_destroy(SEXP tensor_xptr);

static inline TF_Tensor* tf_tensor_from_tensor_xptr(SEXP tensor_xptr) {
    return (TF_Tensor*) R_ExternalPtrAddr(tensor_xptr);
}

static inline SEXP tf_tensor_xptr_from_tensor(TF_Tensor* tensor) {
    SEXP tensor_xptr = PROTECT(R_MakeExternalPtr(tensor, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(tensor_xptr, tensor_xptr_destroy);
    Rf_setAttrib(tensor_xptr, R_ClassSymbol, Rf_mkString("tf_tensor"));
    UNPROTECT(1);
    return tensor_xptr;
}

// When a tensor is passed to the TensorFlow C API, its delete
// method will get called from the C API. Keeping the pointer address
// will lead to a double delete, so provide a method to release the pointer
// and let something else manage the memory.
static inline void tf_tensor_xptr_release_tensor(SEXP tensor_xptr) {
    R_SetExternalPtrAddr(tensor_xptr, NULL);
}

static inline const char* tf_data_type_label(int dt) {
    switch (dt) {
    case TF_FLOAT: return "FLOAT";
    case TF_DOUBLE: return "DOUBLE";
    case TF_INT32: return "INT32";
    case TF_UINT8: return "UINT8";
    case TF_INT16: return "INT16";
    case TF_INT8: return "INT8";
    case TF_STRING: return "STRING";
    case TF_COMPLEX64: return "COMPLEX64";
    case TF_INT64: return "INT64";
    case TF_BOOL: return "BOOL";
    case TF_QINT8: return "QINT8";
    case TF_QUINT8: return "QUINT8";
    case TF_QINT32: return "QINT32";
    case TF_BFLOAT16: return "BFLOAT16";
    case TF_QINT16: return "QINT16";
    case TF_QUINT16: return "QUINT16";
    case TF_UINT16: return "UINT16";
    case TF_COMPLEX128: return "COMPLEX128";
    case TF_HALF: return "HALF";
    case TF_RESOURCE: return "RESOURCE";
    case TF_VARIANT: return "VARIANT";
    case TF_UINT32: return "UINT32";
    default: return "<unknown>";
    }
}

#endif
