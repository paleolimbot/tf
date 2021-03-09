#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

#include "buffer.h"

// constructors --------------

void graph_xptr_destroy(SEXP graph_xptr) {
    // deletion function are safe to call on nullptr
    TF_Graph* graph = (TF_Graph*) R_ExternalPtrAddr(graph_xptr);
    TF_DeleteGraph(graph);
}

SEXP tf_c_graph_xptr_import_graph_def(SEXP buffer_xptr) {
    TF_Buffer* buffer = tf_buffer_from_buffer_xptr(buffer_xptr);
    if (buffer == NULL) {
        Rf_error("TF_Buffer* is NULL");
    }

    TF_Status* status = TF_NewStatus();
    TF_Graph* graph = TF_NewGraph();
    // https://github.com/tensorflow/tensorflow/blob/master/tensorflow/c/c_api.h#L722-L829
    TF_ImportGraphDefOptions* options = TF_NewImportGraphDefOptions();

    if (status == NULL || graph == NULL || options == NULL) {
        // # nocov start
        TF_DeleteStatus(status);
        TF_DeleteGraph(graph);
        TF_DeleteImportGraphDefOptions(options);
        Rf_error("Failed to alloc status, graph, or options");
        // # nocov end
    }

    TF_GraphImportGraphDef(graph, buffer, options, status);
    if (TF_GetCode(status) != TF_OK) {
        char error_buf[8096];
        memset(error_buf, 0, 8096);
        strncpy(error_buf, TF_Message(status), 8096 - 1);

        TF_DeleteStatus(status);
        TF_DeleteGraph(graph);
        TF_DeleteImportGraphDefOptions(options);
        
        Rf_error(error_buf);
    }

    SEXP graph_xptr = PROTECT(R_MakeExternalPtr(graph, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(graph_xptr, &graph_xptr_destroy);
    UNPROTECT(1);
    return graph_xptr;
}
