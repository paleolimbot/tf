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
        TF_DeleteGraph(graph);
        TF_DeleteImportGraphDefOptions(options);
        
        Rf_error(error_buf);
    }

    Rf_setAttrib(graph_xptr, R_ClassSymbol, Rf_mkString("tf_graph"));
    UNPROTECT(1);
    return graph_xptr;
}

// Iterate through the operations of a graph.  To use:
// size_t pos = 0;
// TF_Operation* oper;
// while ((oper = TF_GraphNextOperation(graph, &pos)) != nullptr) {
//   DoSomethingWithOperation(oper);
// }
// TF_CAPI_EXPORT extern TF_Operation* TF_GraphNextOperation(TF_Graph* graph, size_t* pos);
