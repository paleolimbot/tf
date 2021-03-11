#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

#include "buffer.h"
#include "graph.h"

// constructors --------------

void graph_xptr_destroy(SEXP graph_xptr) {
    TF_Graph* graph = (TF_Graph*) R_ExternalPtrAddr(graph_xptr);
    TF_DeleteGraph(graph);
}

SEXP tf_c_graph_xptr_new() {
    return tf_graph_xptr_new();
}

SEXP tf_c_graph_xptr_list_operations(SEXP graph_xptr) {
    TF_Graph* graph = tf_graph_from_graph_xptr(graph_xptr);

    // count operations to alloc outputs
    size_t n_operations = 0;
    size_t pos = 0;
    TF_Operation* oper;
    while ((oper = TF_GraphNextOperation(graph, &pos)) != NULL) {
        n_operations++;
    }

    SEXP name = PROTECT(Rf_allocVector(STRSXP, n_operations));
    SEXP op_type = PROTECT(Rf_allocVector(STRSXP, n_operations));
    SEXP device = PROTECT(Rf_allocVector(STRSXP, n_operations));
    SEXP num_outputs = PROTECT(Rf_allocVector(INTSXP, n_operations));
    SEXP num_inputs = PROTECT(Rf_allocVector(INTSXP, n_operations));

    pos = 0;
    size_t i = 0;
    while ((oper = TF_GraphNextOperation(graph, &pos)) != NULL) {
        SET_STRING_ELT(name, i, Rf_mkCharCE(TF_OperationName(oper), CE_UTF8));
        SET_STRING_ELT(op_type, i, Rf_mkCharCE(TF_OperationOpType(oper), CE_UTF8));
        SET_STRING_ELT(device, i, Rf_mkCharCE(TF_OperationDevice(oper), CE_UTF8));
        INTEGER(num_outputs)[i] = TF_OperationNumOutputs(oper);
        INTEGER(num_inputs)[i] = TF_OperationNumInputs(oper);
        i++;
    }

    const char* names[] = {"name", "op_type", "device", "num_outputs", "num_inputs", ""};
    SEXP result = PROTECT(Rf_mkNamed(VECSXP, names));
    SET_VECTOR_ELT(result, 0, name);
    SET_VECTOR_ELT(result, 1, op_type);
    SET_VECTOR_ELT(result, 2, device);
    SET_VECTOR_ELT(result, 3, num_outputs);
    SET_VECTOR_ELT(result, 4, num_inputs);
    UNPROTECT(6);
    return result;
}

SEXP tf_c_graph_xptr_import_graph_def(SEXP buffer_xptr) {
    TF_Buffer* buffer = tf_buffer_from_buffer_xptr(buffer_xptr);
    if (buffer == NULL) {
        Rf_error("TF_Buffer* is NULL");
    }

    SEXP graph_xptr = PROTECT(tf_graph_xptr_new());
    TF_Graph* graph = tf_graph_from_graph_xptr(graph_xptr);

    TF_Status* status = TF_NewStatus();
    TF_ImportGraphDefOptions* options = TF_NewImportGraphDefOptions();

    if (status == NULL || options == NULL) {
        // # nocov start
        TF_DeleteStatus(status);
        TF_DeleteImportGraphDefOptions(options);
        UNPROTECT(1);
        Rf_error("Failed to alloc status, graph, or options");
        // # nocov end
    }

    TF_GraphImportGraphDef(graph, buffer, options, status);
    if (TF_GetCode(status) != TF_OK) {
        char error_buf[8096];
        memset(error_buf, 0, 8096);
        strncpy(error_buf, TF_Message(status), 8096 - 1);

        TF_DeleteStatus(status);
        TF_DeleteImportGraphDefOptions(options);
        
        Rf_error(error_buf);
    }

    Rf_setAttrib(graph_xptr, R_ClassSymbol, Rf_mkString("tf_graph"));
    UNPROTECT(1);
    return graph_xptr;
}
