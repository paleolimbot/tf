#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "tensorflow/c/c_api.h"
#include "copy-convert.h"
#include "tensor.h"
#include "util.h"

SEXP tf_c_array_from_tensor_xptr(SEXP tensor_xptr, SEXP ptype) {
    TF_Tensor* tensor = tf_tensor_checked_from_tensor_xptr(tensor_xptr);
    int64_t size = TF_TensorElementCount(tensor);
    int data_type = TF_TensorType(tensor);

    if ((TYPEOF(ptype) == STRSXP) && (data_type == TF_STRING)) {
        Rf_error("character--STRING implemented");
    } else if(TYPEOF(ptype) == STRSXP) {
        Rf_error("Can't convert tensor of type '%s' to character()", tf_data_type_label(data_type));
    }
    
    void (*copy_fun)(void* dest_void, void* src_void, int64_t n_elements);
    switch (TYPEOF(ptype)) {
    case REALSXP:
        switch (data_type) {
        case TF_BOOL: copy_fun = &tf_copy_double_from_uint8_t; break;
        case TF_FLOAT: copy_fun = &tf_copy_double_from_float; break;
        case TF_DOUBLE: copy_fun = &tf_copy_double_from_double; break;
        case TF_INT8: copy_fun = &tf_copy_double_from_int8_t; break;
        case TF_INT16: copy_fun = &tf_copy_double_from_int16_t; break;
        case TF_INT32: copy_fun = &tf_copy_double_from_int32_t; break;
        case TF_INT64: copy_fun = &tf_copy_double_from_int64_t; break;
        case TF_UINT8: copy_fun = &tf_copy_double_from_uint8_t; break;
        case TF_UINT16: copy_fun = &tf_copy_double_from_uint16_t; break;
        case TF_UINT32: copy_fun = &tf_copy_double_from_uint32_t; break;
        case TF_UINT64: copy_fun = &tf_copy_double_from_uint64_t; break;
        default: Rf_error("Can't convert tensor of type '%s' to double()", tf_data_type_label(data_type));
        }
        break;
    case INTSXP:
        switch (data_type) {
        case TF_BOOL: copy_fun = &tf_copy_int32_t_from_uint8_t; break;
        case TF_FLOAT: copy_fun = &tf_copy_int32_t_from_float; break;
        case TF_DOUBLE: copy_fun = &tf_copy_int32_t_from_double; break;
        case TF_INT8: copy_fun = &tf_copy_int32_t_from_int8_t; break;
        case TF_INT16: copy_fun = &tf_copy_int32_t_from_int16_t; break;
        case TF_INT32: copy_fun = &tf_copy_int32_t_from_int32_t; break;
        case TF_INT64: copy_fun = &tf_copy_int32_t_from_int64_t; break;
        case TF_UINT8: copy_fun = &tf_copy_int32_t_from_uint8_t; break;
        case TF_UINT16: copy_fun = &tf_copy_int32_t_from_uint16_t; break;
        case TF_UINT32: copy_fun = &tf_copy_int32_t_from_uint32_t; break;
        case TF_UINT64: copy_fun = &tf_copy_int32_t_from_uint64_t; break;
        default: Rf_error("Can't convert tensor of type '%s' to integer()", tf_data_type_label(data_type));
        }
        break;
    case LGLSXP:
        switch (data_type) {
        case TF_BOOL: copy_fun = &tf_copy_int32_t_from_uint8_t; break;
        default: Rf_error("Can't convert tensor of type '%s' to logical()", tf_data_type_label(data_type));
        }
    case RAWSXP:
        switch (data_type) {
        case TF_UINT8: copy_fun = &tf_copy_uint8_t_from_uint8_t; break;
        default: Rf_error("Can't convert tensor of type '%s' to raw()", tf_data_type_label(data_type));
        }
    case CPLXSXP:
        Rf_error("Complex vectors are not yet supported");
    default:
        Rf_error("Invalid .ptype");
    }

    // create output and copy data
    SEXP result = PROTECT(Rf_allocVector(TYPEOF(ptype), size));
    copy_fun(DATAPTR(result), TF_TensorData(tensor), size);

    // add dimensions
    int num_dims = TF_NumDims(tensor);
    SEXP shape = PROTECT(Rf_allocVector(INTSXP, num_dims));
    for (int i = 0; i < num_dims; i++) {
        INTEGER(shape)[i] = TF_Dim(tensor, i);
    }

    Rf_setAttrib(result, R_DimSymbol, shape);
    UNPROTECT(2);
    return result;
}

SEXP tf_c_tensor_xptr_from_array(SEXP array_sexp, SEXP tf_ptype) {
    int data_type = tf_int_from_sexp(tf_ptype, "tf_ptype");
    R_xlen_t size = Rf_xlength(array_sexp);
    size_t dt_size = TF_DataTypeSize(data_type);

    void (*copy_fun)(void* dest_void, void* src_void, int64_t n_elements);
    switch (data_type) {
        case TF_BOOL:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_uint8_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_uint8_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_uint8_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_uint8_t_from_uint8_t; break;
            default: 
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_FLOAT:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_float_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_float_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_float_from_double; break;
            case RAWSXP: copy_fun = tf_copy_float_from_uint8_t; break;
            default:
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_DOUBLE:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_double_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_double_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_double_from_double; break;
            case RAWSXP: copy_fun = tf_copy_double_from_uint8_t; break;
            default:
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_INT8:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_int8_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_int8_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_int8_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_int8_t_from_uint8_t; break;
            default:
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_INT16:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_int16_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_int16_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_int16_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_int16_t_from_uint8_t; break;
            default:
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_INT32:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_int32_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_int32_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_int32_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_int32_t_from_uint8_t; break;
            default:
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_INT64:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_int64_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_int64_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_int64_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_int64_t_from_uint8_t; break;
            default:
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_UINT8:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_uint8_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_uint8_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_uint8_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_uint8_t_from_uint8_t; break;
            default: 
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_UINT16:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_uint16_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_uint16_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_uint16_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_uint16_t_from_uint8_t; break;
            default: 
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_UINT32:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_uint32_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_uint32_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_uint32_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_uint32_t_from_uint8_t; break;
            default: 
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        case TF_UINT64:
            switch (TYPEOF(array_sexp)) {
            case LGLSXP: copy_fun = tf_copy_uint64_t_from_int32_t; break;
            case INTSXP: copy_fun = tf_copy_uint64_t_from_int32_t; break;
            case REALSXP: copy_fun = tf_copy_uint64_t_from_double; break;
            case RAWSXP: copy_fun = tf_copy_uint64_t_from_uint8_t; break;
            default: 
                Rf_error(
                    "Can't convert array of type '%d' to tf_tensor with data type '%s'",
                    TYPEOF(array_sexp),
                    tf_data_type_label(data_type)
                );
            }
            break;
        default: Rf_error("Unsupported tf_ptype: %s", tf_data_type_label(data_type));
    }

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

    // create tensor and copy data
    TF_Tensor* tensor = TF_AllocateTensor(data_type, dims, n_dims, size * dt_size);
    tf_check_trivial_alloc(tensor, "TF_Tensor*");
    SEXP tensor_xptr = PROTECT(tf_tensor_xptr_from_tensor(tensor));
    copy_fun(TF_TensorData(tensor), DATAPTR(array_sexp), size);

    UNPROTECT(1);
    return tensor_xptr;
}
