
#ifndef TF_COPY_CONVERT_H
#define TF_COPY_CONVERT_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void tf_copy_double_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_double(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_float(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_double_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_float_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int16_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int32_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int64_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_int8_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint16_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint32_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint64_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);
void tf_copy_uint8_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements);



#ifdef __cplusplus
}
#endif

#endif
