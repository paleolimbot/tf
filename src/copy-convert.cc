
#include <cstdint>
#include <memory>
#include "copy-convert.h"

template <class dest_type_t, class src_type_t>
void tf_copy_tensor_data(void* dest_void, void* src_void, int64_t n_elements) {
    dest_type_t* dest = (dest_type_t*) dest_void;
    src_type_t* src = (src_type_t*) src_void;

    for (int64_t i = 0; i < n_elements; i++) {
        dest[i] = static_cast<dest_type_t>(src[i]);
    }
}

void tf_copy_double_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, double>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, double>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, double>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, float>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, float>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, float>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_int16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, int16_t>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_int32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, int32_t>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_int64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, int64_t>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_int8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, int8_t>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_uint16_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, uint16_t>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_uint32_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, uint32_t>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_uint64_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, uint64_t>(dest_void, src_void, n_elements);
}

void tf_copy_double_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int16_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int16_t, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int32_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int32_t, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int64_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int64_t, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_int8_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<int8_t, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint16_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint16_t, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint32_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint32_t, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint64_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint64_t, uint8_t>(dest_void, src_void, n_elements);
}

void tf_copy_uint8_t_from_uint8_t(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<uint8_t, uint8_t>(dest_void, src_void, n_elements);
}
