
#include <cstdint>
#include <memory>
#include "tensor-convert.h"

template <class dest_type_t, class src_type_t>
void tf_copy_tensor_data(void* dest_void, void* src_void, int64_t n_elements) {
    dest_type_t* dest = (dest_type_t*) dest_void;
    src_type_t* src = (src_type_t*) src_void;

    for (int64_t i = 0; i < n_elements; i++) {
        dest[i] = static_cast<dest_type_t>(src[i]);
    }
}

void tf_copy_double_from_float(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<double, float>(dest_void, src_void, n_elements);
}

void tf_copy_float_from_double(void* dest_void, void* src_void, int64_t n_elements) {
    tf_copy_tensor_data<float, double>(dest_void, src_void, n_elements);
}
