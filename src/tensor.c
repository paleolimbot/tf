#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <memory.h>

#include "tensorflow/c/c_api.h"

#include "tensor.h"

void tensor_xptr_destroy(SEXP tensor_xptr) {
    TF_Tensor* tensor = (TF_Tensor*) R_ExternalPtrAddr(tensor_xptr);
    TF_DeleteTensor(tensor);
}

SEXP tf_c_tensor_xptr_attributes(SEXP tensor_xptr) {
    TF_Tensor* tensor = tf_tensor_from_tensor_xptr(tensor_xptr);
    if (tensor == NULL) {
        Rf_error("TF_Tensor* is NULL");
    }

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

SEXP tf_c_tensor_xptr_valid(SEXP tensor_xptr) {
    int valid = Rf_inherits(tensor_xptr, "tf_tensor") &&
        (tf_tensor_from_tensor_xptr(tensor_xptr) != NULL);
    return Rf_ScalarLogical(valid);
}

// Note here that array_sexp is not really an R array in the sense that
// tensors are stored in row-major order. However, transforming arrays
// is more easily handled in R, so this transformation (e.g., via t())
// must be done in advance for now.
SEXP tf_c_tensor_xptr_from_array_real(SEXP array_sexp) {
    // just for the proof-of-concept
    TF_DataType dt = TF_FLOAT;
    size_t dt_size = TF_DataTypeSize(dt);

    // in R these have to be integers
    SEXP dims_sexp = Rf_getAttrib(array_sexp, R_DimSymbol);
    if (dims_sexp == R_NilValue) {
        // too hard...make caller do this in R using dim()<-
        Rf_error("Can't create TF_Tensor from dimentionless vector");
    }

    // in tensorflow these are int64_t
    int n_dims = Rf_length(dims_sexp);
    int64_t dims[n_dims];
    for (int i = 0; i < n_dims; i++) {
        dims[i] = INTEGER(dims_sexp)[i];
    }

    // Using `array_sexp` to protect the memory is problematic
    // unless we keep something in the namespace bookkeeping to make sure
    // they don't get garbage collected when their name goes out of scope
    // but tensorflow still needs them. The arrays aren't that useful anyway
    // because they are indexed in the opposite order (row-major), so we
    // use the default TF_AllocateTensor to manage the memory instead.
    // (by the docs, it is preferred to malloc() and free()).
    R_xlen_t array_size = Rf_xlength(array_sexp);
    TF_Tensor* tensor = TF_AllocateTensor(dt, dims, n_dims, array_size * dt_size);

    SEXP tensor_xptr = PROTECT(tf_tensor_xptr_from_tensor(tensor));
    if (tensor == NULL) {
        Rf_error("Failed to alloc tensor of size %ul", array_size * dt_size);
    }

    // copy with conversion
    float* tensor_data = (float*) TF_TensorData(tensor);
    double* array_data = REAL(array_sexp);
    for (R_xlen_t i = 0; i < array_size; i++) {
        tensor_data[i] = array_data[i];
    }

    UNPROTECT(1);
    return tensor_xptr;
}
