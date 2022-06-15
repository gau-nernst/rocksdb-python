#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "rocksdb/options.h"

using ROCKSDB_NAMESPACE::ColumnFamilyOptions;
using ROCKSDB_NAMESPACE::DBOptions;
using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::WriteOptions;

void init_options(py::module_ &m)
{
    py::class_<ColumnFamilyOptions>(m, "ColumnFamilyOptions")
        .def(py::init())
        .def(py::init<const Options &>())

        .def("OptimizeForPointLookup",
             &ColumnFamilyOptions::OptimizeForPointLookup,
             py::return_value_policy::reference_internal)

        .def("OptimizeLevelStyleCompaction",
             &ColumnFamilyOptions::OptimizeLevelStyleCompaction,
             py::arg("memtable_memory_budget") = 512 * 1024 * 1024,
             py::return_value_policy::reference_internal)

        .def("OptimizeUniversalStyleCompaction",
             &ColumnFamilyOptions::OptimizeUniversalStyleCompaction,
             py::arg("memtable_memory_budget") = 512 * 1024 * 1024,
             py::return_value_policy::reference_internal);

    py::class_<DBOptions>(m, "DBOptions")
        .def(py::init())
        .def(py::init<const Options &>())

        .def("IncreaseParallelism",
             &DBOptions::IncreaseParallelism,
             py::arg("total_threads") = 16,
             py::return_value_policy::reference_internal)

        .def_readwrite("create_if_missing",
                       &DBOptions::create_if_missing)

        .def_readwrite("create_missing_column_families",
                       &DBOptions::create_missing_column_families)

        .def_readwrite("error_if_exists",
                       &DBOptions::error_if_exists)

        .def_readwrite("paranoid_checks",
                       &DBOptions::paranoid_checks)

        .def_readwrite("flush_verify_memtable_count",
                       &DBOptions::flush_verify_memtable_count)

        .def_readwrite("track_and_verify_wals_in_manifest",
                       &DBOptions::track_and_verify_wals_in_manifest)

        .def_readwrite("verify_sst_unique_id_in_manifest",
                       &DBOptions::verify_sst_unique_id_in_manifest)

        .def_readwrite("max_file_opening_threads",
                       &DBOptions::max_file_opening_threads)

        .def_readwrite("use_fsync",
                       &DBOptions::use_fsync);

    py::class_<Options, DBOptions, ColumnFamilyOptions>(m, "Options")
        .def(py::init<>());

    py::class_<WriteOptions>(m, "WriteOptions")
        .def(py::init<>());

    py::class_<ReadOptions>(m, "ReadOptions")
        .def(py::init<>());
}
