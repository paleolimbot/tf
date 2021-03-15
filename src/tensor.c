#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <memory.h>
#include "tensorflow/c/c_api.h"
#include "tensor.h"
#include "util.h"

void tensor_xptr_destroy(SEXP tensor_xptr) {
    TF_Tensor* tensor = (TF_Tensor*) R_ExternalPtrAddr(tensor_xptr);
    TF_DeleteTensor(tensor);
}

SEXP tf_c_tensor_xptr_attributes(SEXP tensor_xptr) {
    TF_Tensor* tensor = tf_tensor_checked_from_tensor_xptr(tensor_xptr);

    int data_type = TF_TensorType(tensor);
    int num_dims = TF_NumDims(tensor);

    const char* names[] = {"data_type", "data_type_label", "length", "num_dims", "shape", ""};
    SEXP result = PROTECT(Rf_mkNamed(VECSXP, names));
    SET_VECTOR_ELT(result, 0, Rf_ScalarInteger(data_type));
    SET_VECTOR_ELT(result, 1, Rf_mkString(tf_data_type_label(data_type)));
    SET_VECTOR_ELT(result, 2, Rf_ScalarReal(TF_TensorElementCount(tensor)));
    SET_VECTOR_ELT(result, 3, Rf_ScalarInteger(num_dims));

    // use real because these are int64_t
    SEXP shape = PROTECT(Rf_allocVector(REALSXP, num_dims));
    for (int i = 0; i < num_dims; i++) {
        REAL(shape)[i] = TF_Dim(tensor, i);
    }
    SET_VECTOR_ELT(result, 4, shape);
    UNPROTECT(1);

    UNPROTECT(1);
    return result;
}

SEXP tf_c_tensor_xptr_clone_tensor_xptr(SEXP tensor_xptr) {
    TF_Tensor* tensor = tf_tensor_checked_from_tensor_xptr(tensor_xptr);
    int dt = TF_TensorType(tensor);
    int num_dims = TF_NumDims(tensor);
    size_t size = TF_TensorByteSize(tensor);
    int64_t dims[num_dims];
    for (int i = 0; i < num_dims; i++) {
        dims[i] = TF_Dim(tensor, i);
    }

    TF_Tensor* new_tensor = TF_AllocateTensor(dt, dims, num_dims, size);
    tf_check_trivial_alloc(new_tensor, "TF_Tensor");
    memcpy(TF_TensorData(new_tensor), TF_TensorData(tensor), size);

    return tf_tensor_xptr_from_tensor(new_tensor);
}
