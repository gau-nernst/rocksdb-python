#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "py_wrapper.h"

using ROCKSDB_NAMESPACE::DB;
using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::Status;
using ROCKSDB_NAMESPACE::WriteOptions;

class PyDB
{
public:
    PyDB(const Options &options, const std::string &name)
    {
        Status s = DB::Open(options, name, &db);
        if (!s.ok())
            throw std::runtime_error(s.ToString());
    }
    void Put(const WriteOptions &options, const py::bytes &py_key, const py::bytes &py_value)
    {
        std::string key = py_key;
        std::string value = py_value;
        Status s = db->Put(options, key, value);
        if (!s.ok())
            throw std::runtime_error(s.ToString());
    }
    py::bytes Get(const ReadOptions &options, const py::bytes &py_key)
    {
        std::string key = py_key;
        std::string value;
        Status s = db->Get(options, key, &value);
        if (!s.ok())
            throw std::runtime_error(s.ToString());
        return value;
    }
    void Write(const WriteOptions &options, PyWriteBatch &batch)
    {
        Status s = db->Write(options, batch.batch);
        if (!s.ok())
            throw std::runtime_error(s.ToString());
    }

private:
    DB *db;
};

void init_db(py::module_ &m)
{
    py::class_<PyDB>(m, "PyDB")
        .def(py::init<const Options &, const std::string &>())
        .def("Put", &PyDB::Put)
        .def("Get", &PyDB::Get)
        .def("Write", &PyDB::Write);
}
