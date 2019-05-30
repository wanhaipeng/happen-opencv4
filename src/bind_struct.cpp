#include <iostream>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

typedef struct Tensor {
  std::string name;
  std::vector<int> shape;
}tensor;

typedef struct Runtime {
  Runtime(int a) {status = a; p_bmrt = NULL;}
  void* p_bmrt;
  int status;
}runtime;

void fill_tensor(tensor* input_tensor, std::vector<int>& data) {
  input_tensor->shape.push_back(data[0]);
  input_tensor->shape.push_back(data[1]);
  input_tensor->shape.push_back(data[2]);
  input_tensor->shape.push_back(data[3]);
}

// define a module to be imported by python
PYBIND11_MODULE(bind_struct, mymodule) {
  using namespace pybind11::literals; // for _a literal to define arguments
  mymodule.doc() = "struct module to export code";
  // export the tensor strcut
  py::class_<tensor>(mymodule, "tensor")
    .def(py::init<>())
    .def_readwrite("name", &tensor::name)
    .def_readwrite("shape", &tensor::shape);
  py::class_<runtime>(mymodule, "runtime", py::dynamic_attr())
    .def(py::init<int>())
    .def_readonly("p_bmrt", &runtime::p_bmrt)
    .def_readwrite("status", &runtime::status)
    .def("__repr__",
        [](const runtime &a) {
          return "<bind_struct.runtime status '" + std::to_string(a.status) + "'>";
        });
  mymodule.def("fill_tensor", &fill_tensor, "fill tensor shape", "input_tensor"_a, "data"_a);
}