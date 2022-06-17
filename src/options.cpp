#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/chrono.h>
namespace py = pybind11;

#include "rocksdb/options.h"

using ROCKSDB_NAMESPACE::ColumnFamilyOptions;
using ROCKSDB_NAMESPACE::DBOptions;
using ROCKSDB_NAMESPACE::DbPath;
using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::ReadTier;
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

    py::class_<DBOptions> db_options(m, "DBOptions");
    db_options
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
        .def_readwrite("flush_verify_memtable_count", &DBOptions::flush_verify_memtable_count)
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
        .def_readwrite("db_write_buffer_size", &DBOptions::db_write_buffer_size)
        .def_readwrite("access_hint_on_compaction_start", &DBOptions::access_hint_on_compaction_start)
        .def_readwrite("compaction_readahead_size", &DBOptions::compaction_readahead_size)
        .def_readwrite("random_access_max_buffer_size", &DBOptions::random_access_max_buffer_size)
        .def_readwrite("writable_file_max_buffer_size", &DBOptions::writable_file_max_buffer_size)
        .def_readwrite("use_adaptive_mutex", &DBOptions::use_adaptive_mutex)
        .def_readwrite("bytes_per_sync", &DBOptions::bytes_per_sync)
        .def_readwrite("wal_bytes_per_sync", &DBOptions::wal_bytes_per_sync)
        .def_readwrite("strict_bytes_per_sync", &DBOptions::strict_bytes_per_sync)
        .def_readwrite("enable_thread_tracking", &DBOptions::enable_thread_tracking)
        .def_readwrite("delayed_write_rate", &DBOptions::delayed_write_rate)
        .def_readwrite("enable_pipelined_write", &DBOptions::enable_pipelined_write)
        .def_readwrite("unordered_write", &DBOptions::unordered_write)
        .def_readwrite("allow_concurrent_memtable_write", &DBOptions::allow_concurrent_memtable_write)
        .def_readwrite("enable_write_thread_adaptive_yield", &DBOptions::enable_write_thread_adaptive_yield)
        .def_readwrite("max_write_batch_group_size_bytes", &DBOptions::max_write_batch_group_size_bytes)
        .def_readwrite("write_thread_max_yield_usec", &DBOptions::write_thread_max_yield_usec)
        .def_readwrite("write_thread_slow_yield_usec", &DBOptions::write_thread_slow_yield_usec)
        .def_readwrite("skip_stats_update_on_db_open", &DBOptions::skip_stats_update_on_db_open)
        .def_readwrite("skip_checking_sst_file_sizes_on_db_open", &DBOptions::skip_checking_sst_file_sizes_on_db_open)
        .def_readwrite("allow_2pc", &DBOptions::allow_2pc)
        .def_readwrite("fail_if_options_file_error", &DBOptions::fail_if_options_file_error)
        .def_readwrite("dump_malloc_stats", &DBOptions::dump_malloc_stats)
        .def_readwrite("avoid_flush_during_recovery", &DBOptions::avoid_flush_during_recovery)
        .def_readwrite("avoid_flush_during_shutdown", &DBOptions::avoid_flush_during_shutdown)
        .def_readwrite("allow_ingest_behind", &DBOptions::allow_ingest_behind)
        .def_readwrite("two_write_queues", &DBOptions::two_write_queues)
        .def_readwrite("manual_wal_flush", &DBOptions::manual_wal_flush)
        .def_readwrite("wal_compression", &DBOptions::wal_compression)
        .def_readwrite("atomic_flush", &DBOptions::atomic_flush)
        .def_readwrite("avoid_unnecessary_blocking_io", &DBOptions::avoid_unnecessary_blocking_io)
        .def_readwrite("write_dbid_to_manifest", &DBOptions::write_dbid_to_manifest)
        .def_readwrite("log_readahead_size", &DBOptions::log_readahead_size)
        .def_readwrite("best_efforts_recovery", &DBOptions::best_efforts_recovery)
        .def_readwrite("max_bgerror_resume_count", &DBOptions::max_bgerror_resume_count)
        .def_readwrite("bgerror_resume_retry_interval", &DBOptions::bgerror_resume_retry_interval)
        .def_readwrite("allow_data_in_errors", &DBOptions::allow_data_in_errors)
        .def_readwrite("db_host_id", &DBOptions::db_host_id)
        .def_readwrite("enforce_single_del_contracts", &DBOptions::enforce_single_del_contracts);

    py::enum_<DBOptions::AccessHint>(db_options, "AccessHint")
        .value("NONE", DBOptions::AccessHint::NONE)
        .value("NORMAL", DBOptions::AccessHint::NORMAL)
        .value("SEQUENTIAL", DBOptions::AccessHint::SEQUENTIAL)
        .value("WILLNEED", DBOptions::AccessHint::WILLNEED)
        .export_values();

    py::class_<DbPath>(m, "DbPath")
        .def(py::init<>())
        .def(py::init<const std::string &, uint64_t>())
        .def_readonly("path", &DbPath::path)
        .def_readonly("target_size", &DbPath::target_size)
        .def("__repr__", [](const DbPath &p)
             { return "<rocksdb::DbPath path=" + p.path + ", target_size=" + std::to_string(p.target_size) + ">"; });

    py::class_<Options, DBOptions, ColumnFamilyOptions>(m, "Options")
        .def(py::init<>())
        .def(py::init<const DBOptions &, const ColumnFamilyOptions &>())
        .def("PrepareForBulkLoad", &Options::PrepareForBulkLoad,
             py::return_value_policy::reference_internal)
        .def("OptimizeForSmallDb", &Options::OptimizeForSmallDb,
             py::return_value_policy::reference_internal)
        .def("DisableExtraChecks", &Options::DisableExtraChecks,
             py::return_value_policy::reference_internal);

    py::enum_<ReadTier>(m, "ReadTier")
        .value("kReadAllTier", ReadTier::kReadAllTier)
        .value("kBlockCacheTier", ReadTier::kBlockCacheTier)
        .value("kPersistedTier", ReadTier::kPersistedTier)
        .value("kMemtableTier", ReadTier::kMemtableTier)
        .export_values();

    py::class_<ReadOptions>(m, "ReadOptions")
        .def(py::init<>())
        .def(py::init<bool, bool>())
        .def_readwrite("readahead_size", &ReadOptions::readahead_size)
        .def_readwrite("max_skippable_internal_keys", &ReadOptions::max_skippable_internal_keys)
        .def_readwrite("read_tier", &ReadOptions::read_tier)
        .def_readwrite("verify_checksums", &ReadOptions::verify_checksums)
        .def_readwrite("fill_cache", &ReadOptions::fill_cache)
        .def_readwrite("tailing", &ReadOptions::tailing)
        .def_readwrite("total_order_seek", &ReadOptions::total_order_seek)
        .def_readwrite("auto_prefix_mode", &ReadOptions::auto_prefix_mode)
        .def_readwrite("prefix_same_as_start", &ReadOptions::prefix_same_as_start)
        .def_readwrite("pin_data", &ReadOptions::pin_data)
        .def_readwrite("background_purge_on_iterator_cleanup", &ReadOptions::background_purge_on_iterator_cleanup)
        .def_readwrite("ignore_range_deletions", &ReadOptions::ignore_range_deletions)
        .def_readwrite("deadline", &ReadOptions::deadline)
        .def_readwrite("io_timeout", &ReadOptions::io_timeout)
        .def_readwrite("value_size_soft_limit", &ReadOptions::value_size_soft_limit)
        .def_readwrite("adaptive_readahead", &ReadOptions::adaptive_readahead);

    py::class_<WriteOptions>(m, "WriteOptions")
        .def(py::init<>())
        .def_readwrite("sync", &WriteOptions::sync)
        .def_readwrite("disableWAL", &WriteOptions::disableWAL)
        .def_readwrite("ignore_missing_column_families", &WriteOptions::ignore_missing_column_families)
        .def_readwrite("no_slowdown", &WriteOptions::no_slowdown)
        .def_readwrite("low_pri", &WriteOptions::low_pri)
        .def_readwrite("memtable_insert_hint_per_batch", &WriteOptions::memtable_insert_hint_per_batch);
}
