#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include "tensorflow/c/c_api.h"

#include "buffer.h"
#include "graph.h"

// constructors --------------

void session_xptr_destroy(SEXP session_xptr) {
    // finalizers are safe to call on null but CloseSession is probably not
    TF_Session* session = (TF_Session*) R_ExternalPtrAddr(session_xptr);
    if (session != NULL) {
        TF_Status* status = TF_NewStatus();
        TF_CloseSession(session, status);
        TF_DeleteSession(session, status);
        TF_DeleteStatus(status);
    }
}

SEXP tf_c_session_xptr_graph(SEXP session_xptr) {
    return R_ExternalPtrTag(session_xptr);
}

SEXP tf_c_load_session_from_saved_model(SEXP export_dir_sexp, SEXP tags_sexp) {
    if (Rf_length(export_dir_sexp) != 1) {
        Rf_error("`export_dir` must be a character vector of lenfth 1");
    }

    // translateChar allocs are freed at the end of .Call()
    const char* export_dir = Rf_translateCharUTF8(STRING_ELT(export_dir_sexp, 0));

    // tags_len + 1 plus the "" terminator so that  tags is
    // null-terminated and never length zero
    int tags_len = Rf_length(tags_sexp);
    const char* tags[tags_len + 1];
    for (int i = 0; i < tags_len; i++) {
        tags[i] = Rf_translateCharUTF8(STRING_ELT(tags_sexp, i));
    }
    tags[tags_len] = "";

    SEXP graph_xptr = PROTECT(tf_graph_xptr_new());
    TF_Graph* graph = tf_graph_from_graph_xptr(graph_xptr);

    TF_Status* status = TF_NewStatus();
    TF_SessionOptions* session_options = TF_NewSessionOptions();
    
    if (status == NULL || session_options == NULL) {
        // # nocov start
        TF_DeleteStatus(status);
        TF_DeleteSessionOptions(session_options);
        Rf_error("Failed to alloc status or session options");
        // # nocov end
    }

    TF_Session* session = TF_LoadSessionFromSavedModel(
        session_options,
        NULL,
        export_dir,
        tags, tags_len,
        graph,
        NULL,
        status
    );

    if (TF_GetCode(status) != TF_OK) {
        char error_buf[8096];
        memset(error_buf, 0, 8096);
        strncpy(error_buf, TF_Message(status), 8096 - 1);

        TF_DeleteSession(session, status);
        TF_DeleteStatus(status);
        TF_DeleteSessionOptions(session_options);

        Rf_error(error_buf);
    }

    // attach graph to the session to protect from garbage collection
    SEXP session_xptr = PROTECT(R_MakeExternalPtr(session, graph_xptr, R_NilValue));
    R_RegisterCFinalizer(session_xptr, &session_xptr_destroy);
    UNPROTECT(2);
    return session_xptr;
}
