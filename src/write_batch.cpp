#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "rocksdb/write_batch.h"

using ROCKSDB_NAMESPACE::WriteBatch;

class PyWriteBatch
{
public:
    WriteBatch *batch;
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
    py::bytes Data() { return batch->Data(); };
    size_t GetDataSize() { return batch->GetDataSize(); };
    uint32_t Count() { return batch->Count(); };
    bool HasPut() { return batch->HasPut(); };
    bool HasDelete() { return batch->HasDelete(); };
    bool HasSingleDelete() { return batch->HasSingleDelete(); };
    bool HasDeleteRange() { return batch->HasDeleteRange(); };
    bool HasMerge() { return batch->HasMerge(); };
    bool HasBeginPrepare() { return batch->HasBeginPrepare(); };
    bool HasEndPrepare() { return batch->HasEndPrepare(); };
    bool HasCommit() { return batch->HasCommit(); };
    bool HasRollback() { return batch->HasRollback(); };
    void MarkWalTerminationPoint() { batch->MarkWalTerminationPoint(); };
    void SetMaxBytes(size_t max_bytes) { batch->SetMaxBytes(max_bytes); };
    size_t GetProtectionBytesPerKey() { return batch->GetProtectionBytesPerKey(); };
};

void init_write_batch(py::module_ &m)
{
    py::class_<PyWriteBatch>(m, "PyWriteBatch")
        .def(py::init<>())
        .def("Put", &PyWriteBatch::Put)
        .def("Delete", &PyWriteBatch::Delete)
        .def("Data", &PyWriteBatch::Data)
        .def("GetDataSize", &PyWriteBatch::GetDataSize)
        .def("Count", &PyWriteBatch::Count)
        .def("HasPut", &PyWriteBatch::HasPut)
        .def("HasDelete", &PyWriteBatch::HasDelete)
        .def("HasSingleDelete", &PyWriteBatch::HasSingleDelete)
        .def("HasDeleteRange", &PyWriteBatch::HasDeleteRange)
        .def("HasMerge", &PyWriteBatch::HasMerge)
        .def("HasBeginPrepare", &PyWriteBatch::HasBeginPrepare)
        .def("HasEndPrepare", &PyWriteBatch::HasEndPrepare)
        .def("HasCommit", &PyWriteBatch::HasCommit)
        .def("HasRollback", &PyWriteBatch::HasRollback)
        .def("MarkWalTerminationPoint", &PyWriteBatch::MarkWalTerminationPoint)
        .def("SetMaxBytes", &PyWriteBatch::SetMaxBytes)
        .def("GetProtectionBytesPerKey", &PyWriteBatch::GetProtectionBytesPerKey);
}
