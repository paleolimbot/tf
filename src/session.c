#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <stdlib.h>

#include "tensorflow/c/c_api.h"

#include "buffer.h"
#include "graph.h"
#include "util.h"

TF_Session* tf_session_from_session_xptr(SEXP session_xptr) {
    return (TF_Session*) R_ExternalPtrAddr(session_xptr);
}

TF_Graph* tf_graph_from_session_xptr(SEXP session_xptr) {
    return (TF_Graph*) R_ExternalPtrAddr(R_ExternalPtrTag(session_xptr));
}

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
        Rf_error("`export_dir` must be a character vector of length 1");
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

SEXP tf_c_session_xptr_run(SEXP session_xptr, SEXP oper_name_input_sexp, SEXP oper_name_output_sexp) {
    TF_Session* session = tf_session_from_session_xptr(session_xptr);
    if (session == NULL) {
        Rf_error("TF_Session* is NULL");
    }

    TF_Graph* graph = tf_graph_from_session_xptr(session_xptr);
    if (graph == NULL) {
        Rf_error("TF_Graph* is NULL");
    }

    const char* oper_name_input = Rf_translateCharUTF8(STRING_ELT(oper_name_input_sexp, 0));
    TF_Operation* oper_input = TF_GraphOperationByName(graph, oper_name_input);
    if (oper_input == NULL) {
        Rf_error("Can't load input operation '%s' from graph", oper_name_input);
    }

    const char* oper_name_output = Rf_translateCharUTF8(STRING_ELT(oper_name_output_sexp, 0));
    TF_Operation* oper_output = TF_GraphOperationByName(graph, oper_name_output);
    if (oper_input == NULL) {
        Rf_error("Can't load output operation '%s' from graph", oper_name_output);
    }

    // inspired by example:
    // https://github.com/AmirulOm/tensorflow_capi_sample
    int num_inputs = 1;
    TF_Output* input = malloc(sizeof(TF_Output) * num_inputs);
    if (input == NULL) {
        Rf_error("Failed to alloc input array of size %d", num_inputs);
    }
    input[0].index = 0;
    input[0].oper = oper_input;

    int num_outputs = 1;
    TF_Output* output = malloc(sizeof(TF_Output) * num_outputs);
    if (input == NULL) {
        free(input);
        Rf_error("Failed to alloc output array of size %d", num_outputs);
    }
    output[0].index = 0;
    output[0].oper = oper_output;

    // tensor stuff, should be in its own file with externalptrs
    TF_Tensor** input_values = malloc(sizeof(TF_Tensor*) * num_inputs);
    if (input_values == NULL) {
        free(input);
        free(output);
        Rf_error("Failed to alloc input values array of size %d", num_inputs);
    }

    TF_Tensor** output_values = malloc(sizeof(TF_Tensor*) * num_outputs);
    if (output_values == NULL) {
        free(input);
        free(output);
        free(input_values);
        Rf_error("Failed to alloc output values array of size %d", num_inputs);
    }

    TF_SessionRun(
        session,
        // run options can be NULL
        NULL, 
        input, input_values, num_inputs, 
        output, output_values, num_outputs, 
        // no target operations
        NULL, 0,
        // run metadata can be NULL
        NULL,
        tf_global_status
    );

    return R_NilValue;
}

