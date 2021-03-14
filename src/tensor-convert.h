
#ifndef TF_TENSOR_CONVERT_H
#define TF_TENSOR_CONVERT_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void tf_copy_double_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_double(void* dest_void, void* src_void, int64_t n_elements);

#ifdef __cplusplus
}
#endif

#endif
