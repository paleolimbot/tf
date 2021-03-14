#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <memory.h>
#include "tensorflow/c/c_api.h"
#include "tensor.h"
#include "util.h"
#include "tensor-convert.h"

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

SEXP tf_c_array_real_from_tensor_xptr(SEXP tensor_xptr, SEXP ptype) {
    TF_Tensor* tensor = tf_tensor_checked_from_tensor_xptr(tensor_xptr);

    int64_t size = TF_TensorElementCount(tensor);
    SEXP result = PROTECT(Rf_allocVector(TYPEOF(ptype), size));

    int data_type = TF_TensorType(tensor);
    switch (data_type) {
    case TF_FLOAT:
        tf_copy_double_from_float(REAL(result), TF_TensorData(tensor), size);
        break;
    default:
        Rf_error(
            "Can't convert tf_tensor with data type '%s' to array",
            tf_data_type_label(data_type)
        );
    }

    // not sure what to do when dim > INT_MAX
    int num_dims = TF_NumDims(tensor);
    SEXP shape = PROTECT(Rf_allocVector(INTSXP, num_dims));
    for (int i = 0; i < num_dims; i++) {
        INTEGER(shape)[i] = TF_Dim(tensor, i);
    }

    Rf_setAttrib(result, R_DimSymbol, shape);
    UNPROTECT(2);
    return result;
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
    tf_check_trivial_alloc(tensor, "TF_Tensor*");

    SEXP tensor_xptr = PROTECT(tf_tensor_xptr_from_tensor(tensor));

    // copy with conversion
    float* tensor_data = (float*) TF_TensorData(tensor);
    double* array_data = REAL(array_sexp);
    for (R_xlen_t i = 0; i < array_size; i++) {
        tensor_data[i] = array_data[i];
    }

    UNPROTECT(1);
    return tensor_xptr;
}
