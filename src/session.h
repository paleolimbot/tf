
#ifndef TF_SESSION_H_INCLUDED
#define TF_SESSION_H_INCLUDED

#include <R.h>
#include <Rinternals.h>

#include <stdlib.h>

#include "tensorflow/c/c_api.h"

#include "buffer.h"
#include "graph.h"
#include "util.h"

void session_xptr_destroy(SEXP session_xptr);

static inline SEXP tf_session_xptr_from_session(TF_Session* session) {
    SEXP session_xptr = PROTECT(R_MakeExternalPtr(session, R_NilValue, R_NilValue));
    Rf_setAttrib(session_xptr, R_ClassSymbol, Rf_mkString("tf_session"));
    R_RegisterCFinalizer(session_xptr, &session_xptr_destroy);
    UNPROTECT(1);
    return session_xptr;
}

static inline SEXP tf_session_xptr_attach_graph_xptr(SEXP session_xptr, SEXP graph_xptr) {
    // graph can be NULL or a valid graph external pointer
    if (graph_xptr != R_NilValue) {
        tf_graph_checked_from_graph_xptr(graph_xptr);
    }

    SEXP old_graph = PROTECT(R_ExternalPtrTag(session_xptr));
    R_SetExternalPtrTag(session_xptr, graph_xptr);
    UNPROTECT(1);
    return old_graph;
}

static inline TF_Session* tf_session_from_session_xptr(SEXP session_xptr) {
    return (TF_Session*) R_ExternalPtrAddr(session_xptr);
}

static inline TF_Session* tf_session_checked_from_session_xptr(SEXP session_xptr) {
    if (!Rf_inherits(session_xptr, "tf_session")) {
        Rf_error("TF_Buffer* externalptr must inherit from 'tf_session'");
    }

    TF_Session* session = tf_session_from_session_xptr(session_xptr);
    if (session == NULL) {
        Rf_error("TF_Session* externalptr points to NULL");
    }

    return session;
}

static inline TF_Graph* tf_graph_from_session_xptr(SEXP session_xptr) {
    return tf_graph_from_graph_xptr(R_ExternalPtrTag(session_xptr));
}

static inline TF_Graph* tf_graph_checked_from_session_xptr(SEXP session_xptr) {
    tf_session_checked_from_session_xptr(session_xptr);
    return tf_graph_checked_from_graph_xptr(R_ExternalPtrTag(session_xptr));
}

#endif
