#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "rocksdb/write_batch.h"

using ROCKSDB_NAMESPACE::WriteBatch;

class PyWriteBatch
{
public:
    PyWriteBatch() : batch(new WriteBatch()){};
    void Put(const py::bytes &py_key, const py::bytes &py_value)
    {
        std::string key = py_key;
        std::string value = py_value;
        batch->Put(key, value);
    };
    void Delete(const py::bytes &py_key)
    {
        std::string key = py_key;
        batch->Delete(key);
    };
    WriteBatch *batch;
};

void init_write_batch(py::module_ &m)
{
    py::class_<PyWriteBatch>(m, "PyWriteBatch")
        .def(py::init<>())
        .def("Put", &PyWriteBatch::Put)
        .def("Delete", &PyWriteBatch::Delete);
}
