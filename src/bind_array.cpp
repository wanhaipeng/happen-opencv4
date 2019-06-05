#include <iostream>
#include <string>
#include <vector>
#include <numeric>
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

std::vector<int> ndarray_to_tensor(py::array_t<Dtype>& input, py::list& output) {
    py::buffer_info input_buf = input.request();
    if (input_buf.ndim < 1) {
        throw std::runtime_error("numpy.ndarray dims not valid");
    }
    // get shape from ndarray
    std::vector<int> input_shape;
    for (auto it_shape : input_buf.shape) {
        input_shape.push_back((int)it_shape);
    }
    Dtype* ptr = (Dtype*)input_buf.ptr;
    output.append(0.0);
    return input_shape;
}

void set_list(py::list& input) {
    input[0] = 10.0;
}

py::array_t<Dtype> tensor_to_ndarray(std::vector<int> input_shape, std::vector<Dtype> input_data) {
    if (input_shape.size() < 1) {
        throw std::runtime_error("input shape not valid");
    }
    // fill numpy array
    void* ptr = (void*)input_data.data();
    py::ssize_t itemsize = sizeof(Dtype);
    std::string format = py::format_descriptor<Dtype>::format();
    py::ssize_t ndim = input_shape.size();
    std::vector<py::ssize_t> shape;
    for (auto it : input_shape) {
        shape.push_back(it);
    }
    std::vector<py::ssize_t> stride;
    for (int i = 1 ; i < input_shape.size(); i++) {
        py::ssize_t inner_stride =
            std::accumulate(shape.begin() + i, shape.end(), sizeof(Dtype), std::multiplies<py::ssize_t>());
        stride.push_back(inner_stride);
    }
    stride.push_back(sizeof(Dtype));
    py::buffer_info output_buf(
        ptr,
        itemsize,
        format,
        ndim,
        shape,
        stride
    );
    return py::array_t<Dtype>(output_buf);
}

void test_dict(py::dict& input_dict) {
    for (auto it : input_dict) {
        std::cout << it.first << std::endl;
        // std::cout << it.second.ptr() << std::endl;
        const py::handle h = it.second.inc_ref();
        // py::array_t<Dtype> inner_array = py::array_t<Dtype>::ensure(h);
        py::array_t<Dtype> inner_array = py::array_t<Dtype>::ensure(it.second);
        py::print(inner_array);
    }
}

// define a module to be imported by python
PYBIND11_MODULE(bind_array, mymodule) {
  using namespace pybind11::literals; // for _a literal to define arguments
  mymodule.doc() = "bind numpy module to export code";
  mymodule.def("test_array_2d", &test_array_2d);
  mymodule.def("ndarray_to_tensor", &ndarray_to_tensor);
  mymodule.def("set_list", &set_list);
  mymodule.def("tensor_to_ndarray", &tensor_to_ndarray);
  mymodule.def("test_dict", &test_dict);
}