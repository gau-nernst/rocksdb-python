#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include "rocksdb/options.h"

using ROCKSDB_NAMESPACE::ColumnFamilyOptions;
using ROCKSDB_NAMESPACE::DBOptions;
using ROCKSDB_NAMESPACE::DbPath;
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
        .def("OptimizeForSmallDb", &DBOptions::OptimizeForSmallDb,
             py::arg("cache") = nullptr, py::return_value_policy::reference_internal)
        .def("IncreaseParallelism", &DBOptions::IncreaseParallelism,
             py::arg("total_threads") = 16, py::return_value_policy::reference_internal)
        .def_readwrite("create_if_missing", &DBOptions::create_if_missing)
        .def_readwrite("create_missing_column_families", &DBOptions::create_missing_column_families)
        .def_readwrite("error_if_exists", &DBOptions::error_if_exists)
        .def_readwrite("paranoid_checks", &DBOptions::paranoid_checks)
        .def_readwrite("flush_verify_memtable_count",  &DBOptions::flush_verify_memtable_count)
        .def_readwrite("track_and_verify_wals_in_manifest", &DBOptions::track_and_verify_wals_in_manifest)
        .def_readwrite("verify_sst_unique_id_in_manifest", &DBOptions::verify_sst_unique_id_in_manifest)
        .def_readwrite("info_log_level", &DBOptions::info_log_level)
        .def_readwrite("max_open_files", &DBOptions::max_open_files)
        .def_readwrite("max_file_opening_threads", &DBOptions::max_file_opening_threads)
        .def_readwrite("max_total_wal_size", &DBOptions::max_total_wal_size)
        .def_readwrite("use_fsync", &DBOptions::use_fsync)
        .def_readwrite("db_paths", &DBOptions::db_paths)
        .def_readwrite("wal_dir", &DBOptions::wal_dir)
        .def_readwrite("delete_obsolete_files_period_micros", &DBOptions::delete_obsolete_files_period_micros)
        .def_readwrite("max_background_jobs", &DBOptions::max_background_jobs)
        .def_readwrite("max_background_compactions", &DBOptions::max_background_compactions)
        .def_readwrite("max_subcompactions", &DBOptions::max_subcompactions)
        .def_readwrite("max_background_flushes", &DBOptions::max_background_flushes)
        .def_readwrite("max_log_file_size", &DBOptions::max_log_file_size)
        .def_readwrite("log_file_time_to_roll", &DBOptions::log_file_time_to_roll)
        .def_readwrite("keep_log_file_num", &DBOptions::keep_log_file_num)
        .def_readwrite("recycle_log_file_num", &DBOptions::recycle_log_file_num)
        .def_readwrite("max_manifest_file_size", &DBOptions::max_manifest_file_size)
        .def_readwrite("table_cache_numshardbits", &DBOptions::table_cache_numshardbits)
        .def_readwrite("WAL_ttl_seconds", &DBOptions::WAL_ttl_seconds)
        .def_readwrite("WAL_size_limit_MB", &DBOptions::WAL_size_limit_MB)
        .def_readwrite("manifest_preallocation_size", &DBOptions::manifest_preallocation_size)
        .def_readwrite("allow_mmap_reads", &DBOptions::allow_mmap_reads)
        .def_readwrite("allow_mmap_writes", &DBOptions::allow_mmap_writes)
        .def_readwrite("use_direct_reads", &DBOptions::use_direct_reads)
        .def_readwrite("use_direct_io_for_flush_and_compaction", &DBOptions::use_direct_io_for_flush_and_compaction)
        .def_readwrite("allow_fallocate", &DBOptions::allow_fallocate)
        .def_readwrite("is_fd_close_on_exec", &DBOptions::is_fd_close_on_exec)
        .def_readwrite("stats_dump_period_sec", &DBOptions::stats_dump_period_sec)
        .def_readwrite("stats_persist_period_sec", &DBOptions::stats_persist_period_sec)
        .def_readwrite("stats_history_buffer_size", &DBOptions::stats_history_buffer_size)
        .def_readwrite("advise_random_on_open", &DBOptions::advise_random_on_open)
        .def_readwrite("db_write_buffer_size", &DBOptions::db_write_buffer_size);

    py::class_<DbPath>(m, "DbPath")
        .def(py::init<>())
        .def(py::init<const std::string &, uint64_t>())
        .def_readonly("path", &DbPath::path)
        .def_readonly("target_size", &DbPath::target_size)
        .def("__repr__", [](const DbPath &p)
             { return "<rocksdb::DbPath path=" + p.path + ", target_size=" + std::to_string(p.target_size) + ">"; });

    py::class_<Options, DBOptions, ColumnFamilyOptions>(m, "Options")
        .def(py::init<>());

    py::class_<WriteOptions>(m, "WriteOptions")
        .def(py::init<>());

    py::class_<ReadOptions>(m, "ReadOptions")
        .def(py::init<>());
}
