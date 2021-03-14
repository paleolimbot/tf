#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <stdlib.h>

#include "tensorflow/c/c_api.h"

#include "buffer.h"
#include "graph.h"
#include "tensor.h"
#include "util.h"

TF_Session* tf_session_from_session_xptr(SEXP session_xptr) {
    return (TF_Session*) R_ExternalPtrAddr(session_xptr);
}

TF_Session* tf_session_checked_from_session_xptr(SEXP session_xptr) {
    if (!Rf_inherits(session_xptr, "tf_session")) {
        Rf_error("TF_Buffer* externalptr must inherit from 'tf_session'");
    }

    TF_Session* session = tf_session_from_session_xptr(session_xptr);
    if (session == NULL) {
        Rf_error("TF_Session* externalptr points to NULL");
    }

    return session;
}

TF_Graph* tf_graph_from_session_xptr(SEXP session_xptr) {
    return tf_graph_from_graph_xptr(R_ExternalPtrTag(session_xptr));
}

TF_Graph* tf_graph_checked_from_session_xptr(SEXP session_xptr) {
    tf_session_checked_from_session_xptr(session_xptr);
    return tf_graph_checked_from_graph_xptr(R_ExternalPtrTag(session_xptr));
}

// constructors --------------

void session_xptr_destroy(SEXP session_xptr) {
    // finalizers are safe to call on null but CloseSession is probably not
    TF_Session* session = (TF_Session*) R_ExternalPtrAddr(session_xptr);
    if (session != NULL) {
        TF_CloseSession(session, tf_global_status);
        TF_DeleteSession(session, tf_global_status);
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

    TF_SessionOptions* session_options = TF_NewSessionOptions();
    tf_check_trivial_alloc(session_options, "TF_SessionOptions");

    TF_Session* session = TF_LoadSessionFromSavedModel(
        session_options,
        NULL,
        export_dir,
        tags, tags_len,
        graph,
        NULL,
        tf_global_status
    );

    tf_check_status(tf_global_status);

    // attach graph to the session to protect from garbage collection
    SEXP session_xptr = PROTECT(R_MakeExternalPtr(session, graph_xptr, R_NilValue));
    R_RegisterCFinalizer(session_xptr, &session_xptr_destroy);
    UNPROTECT(2);
    return session_xptr;
}

SEXP tf_c_session_xptr_run(SEXP session_xptr, 
                           SEXP oper_name_input_sexp, SEXP oper_name_output_sexp,
                           SEXP input_tensor_xptr_list) {
    TF_Session* session = tf_session_checked_from_session_xptr(session_xptr);
    TF_Graph* graph = tf_graph_checked_from_session_xptr(session_xptr);

    const char* oper_name_input = Rf_translateCharUTF8(STRING_ELT(oper_name_input_sexp, 0));
    TF_Operation* oper_input = TF_GraphOperationByName(graph, oper_name_input);
    if (oper_input == NULL) {
        Rf_error("Can't load input operation '%s' from graph", oper_name_input);
    }

    const char* oper_name_output = Rf_translateCharUTF8(STRING_ELT(oper_name_output_sexp, 0));
    TF_Operation* oper_output = TF_GraphOperationByName(graph, oper_name_output);
    if (oper_output == NULL) {
        Rf_error("Can't load output operation '%s' from graph", oper_name_output);
    }

    // inspired by example:
    // https://github.com/AmirulOm/tensorflow_capi_sample

    int num_inputs = Rf_length(input_tensor_xptr_list);
    TF_Tensor* input_values[num_inputs];
    TF_Output input[num_inputs];

    for (int i = 0; i < num_inputs; i++) {
        input_values[i] = tf_tensor_from_tensor_xptr(VECTOR_ELT(input_tensor_xptr_list, i));
        input[i].index = i;
        input[i].oper = oper_input;
    }

    int num_outputs = TF_OperationNumOutputs(oper_output);
    TF_Output output[num_outputs];
    TF_Tensor* output_values[num_outputs];

    for (int i = 0; i < num_outputs; i++) {
        output[i].index = i;
        output[i].oper = oper_output;
        output_values[0] = NULL;
    }

    // release the input values since the tensors are the responsibility
    // of TF_SessionRun once called (probably?)
    for (int i = 0; i < num_inputs; i++) {
        tf_tensor_xptr_release_tensor(VECTOR_ELT(input_tensor_xptr_list, i));
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

    tf_check_status(tf_global_status);

    // wrap output values in external pointer to ensure they are deleted
    SEXP result = PROTECT(Rf_allocVector(VECSXP, num_outputs));
    for (int i = 0; i < num_outputs; i++) {
        SET_VECTOR_ELT(result, i, tf_tensor_xptr_from_tensor(output_values[i]));
    }

    UNPROTECT(1);
    return result;
}

