
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include "util.h"

/* generated by data-raw/make-callentries.R */
extern SEXP tf_c_buffer_xptr_from_raw(SEXP raw_input);
extern SEXP tf_c_buffer_xptr_clone_buffer_xptr(SEXP buffer_xptr);
extern SEXP tf_c_buffer_xptr_clone_raw(SEXP buffer_xptr, SEXP max_length);
extern SEXP tf_c_buffer_valid(SEXP buffer_xptr);
extern SEXP tf_c_buffer_xptr_length(SEXP buffer_xptr);
extern SEXP tf_c_graph_xptr_new();
extern SEXP tf_c_graph_xptr_list_operations(SEXP graph_xptr);
extern SEXP tf_c_graph_xptr_import_graph_def(SEXP buffer_xptr);
extern SEXP tf_c_session_xptr_graph(SEXP session_xptr);
extern SEXP tf_c_load_session_from_saved_model(SEXP export_dir_sexp, SEXP tags_sexp);
extern SEXP tf_c_session_xptr_run(SEXP session_xptr, SEXP oper_name_input_sexp, SEXP oper_name_output_sexp, SEXP input_tensor_xptr_list);
extern SEXP tf_c_tensor_xptr_attributes(SEXP tensor_xptr);
extern SEXP tf_c_tensor_xptr_valid(SEXP tensor_xptr);
extern SEXP tf_c_array_real_from_tensor_xptr(SEXP tensor_xptr);
extern SEXP tf_c_tensor_xptr_from_array_real(SEXP array_sexp);
extern SEXP tf_c_xptr_addr(SEXP buffer_xptr);
extern SEXP tf_c_version();
static const R_CallMethodDef CallEntries[] = {
    {"tf_c_buffer_xptr_from_raw", (DL_FUNC) &tf_c_buffer_xptr_from_raw, 1},
    {"tf_c_buffer_xptr_clone_buffer_xptr", (DL_FUNC) &tf_c_buffer_xptr_clone_buffer_xptr, 1},
    {"tf_c_buffer_xptr_clone_raw", (DL_FUNC) &tf_c_buffer_xptr_clone_raw, 2},
    {"tf_c_buffer_valid", (DL_FUNC) &tf_c_buffer_valid, 1},
    {"tf_c_buffer_xptr_length", (DL_FUNC) &tf_c_buffer_xptr_length, 1},
    {"tf_c_graph_xptr_new", (DL_FUNC) &tf_c_graph_xptr_new, 0},
    {"tf_c_graph_xptr_list_operations", (DL_FUNC) &tf_c_graph_xptr_list_operations, 1},
    {"tf_c_graph_xptr_import_graph_def", (DL_FUNC) &tf_c_graph_xptr_import_graph_def, 1},
    {"tf_c_session_xptr_graph", (DL_FUNC) &tf_c_session_xptr_graph, 1},
    {"tf_c_load_session_from_saved_model", (DL_FUNC) &tf_c_load_session_from_saved_model, 2},
    {"tf_c_session_xptr_run", (DL_FUNC) &tf_c_session_xptr_run, 4},
    {"tf_c_tensor_xptr_attributes", (DL_FUNC) &tf_c_tensor_xptr_attributes, 1},
    {"tf_c_tensor_xptr_valid", (DL_FUNC) &tf_c_tensor_xptr_valid, 1},
    {"tf_c_array_real_from_tensor_xptr", (DL_FUNC) &tf_c_array_real_from_tensor_xptr, 1},
    {"tf_c_tensor_xptr_from_array_real", (DL_FUNC) &tf_c_tensor_xptr_from_array_real, 1},
    {"tf_c_xptr_addr", (DL_FUNC) &tf_c_xptr_addr, 1},
    {"tf_c_version", (DL_FUNC) &tf_c_version, 0},
    {NULL, NULL, 0}
};
/* end generated by data-raw/make-callentries.R */

void R_init_tf(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    if (tf_global_status == NULL) {
        tf_global_status = TF_NewStatus();
    }
}

void R_unload_tf(DllInfo *dll) {
    TF_DeleteStatus(tf_global_status);
    tf_global_status = NULL;
}
