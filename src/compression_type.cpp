#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "rocksdb/compression_type.h"

using ROCKSDB_NAMESPACE::CompressionType;

void init_compression_type(py::module_ &m)
{
    py::enum_<CompressionType>(m, "CompressionType")
        .value("kNoCompression", CompressionType::kNoCompression)
        .value("kSnappyCompression", CompressionType::kSnappyCompression)
        .value("kZlibCompression", CompressionType::kZlibCompression)
        .value("kBZip2Compression", CompressionType::kBZip2Compression)
        .value("kLZ4Compression", CompressionType::kLZ4Compression)
        .value("kLZ4HCCompression", CompressionType::kLZ4HCCompression)
        .value("kXpressCompression", CompressionType::kXpressCompression)
        .value("kZSTD", CompressionType::kZSTD)
        .value("kDisableCompressionOption", CompressionType::kDisableCompressionOption)
        .export_values();
}
