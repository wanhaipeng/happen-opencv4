#include <iostream>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>

typedef float Dtype;

namespace py = pybind11;

py::array_t<Dtype> test_array_2d(py::array_t<Dtype>& input1) {
    py::buffer_info buf1 = input1.request();
    if (buf1.ndim != 2) {
        throw std::runtime_error("numpy.ndarray dims must be 2!");
    }
    //申请内存
    auto result = py::array_t<Dtype>(buf1.size);
    //转换为2d矩阵
    result.resize({buf1.shape[0],buf1.shape[1]});
    py::buffer_info buf_result = result.request();
    //指针访问读写 numpy.ndarray
    Dtype* ptr1 = (Dtype*)buf1.ptr;
    Dtype* ptr_result = (Dtype*)buf_result.ptr;
    for (int i = 0; i < buf1.shape[0]; i++) {
        for (int j = 0; j < buf1.shape[1]; j++) {
            auto value1 = ptr1[i*buf1.shape[1] + j];
            ptr_result[i*buf_result.shape[1] + j] = value1 + 1;
        }
    }
    return result;
}

std::vector<py::ssize_t> ndarray_to_tensor(py::array_t<Dtype>& input) {
    py::buffer_info input_buf = input.request();
    if (input_buf.ndim < 1) {
        throw std::runtime_error("numpy.ndarray dims not valid");
    }
    // get shape from ndarray
    std::vector<py::ssize_t> input_shape = input_buf.shape;
    Dtype* ptr = (Dtype*)input_buf.ptr;
    ptr[0] = 2.0;
    return input_shape;
}

void set_list(py::list& input) {
    input[0] = 10.0;
}

// define a module to be imported by python
PYBIND11_MODULE(bind_array, mymodule) {
  using namespace pybind11::literals; // for _a literal to define arguments
  mymodule.doc() = "bind numpy module to export code";
  mymodule.def("test_array_2d", &test_array_2d);
  mymodule.def("ndarray_to_tensor", &ndarray_to_tensor);
  mymodule.def("set_list", &set_list);
}