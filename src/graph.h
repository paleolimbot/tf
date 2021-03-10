
#ifndef TF_GRAPH_H_INCLUDED
#define TF_GRAPH_H_INCLUDED

#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

void graph_xptr_destroy(SEXP graph_xptr);

static inline SEXP tf_graph_xptr_new() {
    TF_Graph* graph = TF_NewGraph();
    if (graph == NULL) {
        Rf_error("Failed to alloc TF_Graph"); // # nocov
    }

    SEXP graph_xptr = PROTECT(R_MakeExternalPtr(graph, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(graph_xptr, &graph_xptr_destroy);
    UNPROTECT(1);
    return graph_xptr;
}

static inline TF_Graph* tf_graph_from_graph_xptr(SEXP graph_xptr) {
    return (TF_Graph*) R_ExternalPtrAddr(graph_xptr);
}

#endif
