#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "rocksdb/write_batch.h"

using ROCKSDB_NAMESPACE::WriteBatch;

class PyWriteBatch
{
public:
    PyWriteBatch(){};
    void Put(const py::bytes &py_key, const py::bytes &py_value);
    WriteBatch *batch;
};
