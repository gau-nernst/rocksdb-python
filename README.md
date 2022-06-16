# RocksDB Python

[![Build RocksDB Linux](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_linux.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_linux.yaml)
[![Build RocksDB macOS](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_mac.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_mac.yaml)
[![Build RocksDB Windows](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_win.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_win.yaml)

[![Build](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build.yaml)

Cross-platform Python bindings for [RocksDB](https://github.com/facebook/rocksdb). Other RocksDB Python bindings libraries usually don't provide Windows builds. This repo aims to target all OSes, including Windows.

This project helps me to learn using C++ libraries in Python with [pybind11](https://github.com/pybind/pybind11).

# Installation

## From wheels

TBD

## From source

Build RocksDB

You need to build RocksDB (and optionally 3rd-party compression libraries) from source. Refer to the [official instructions](https://github.com/facebook/rocksdb/blob/main/INSTALL.md) for more information. Additionally, you can also refer to [Building on Windows](https://github.com/facebook/rocksdb/wiki/Building-on-Windows) if you are building on Windows.

I have GitHub Actions Workflows that build RocksDB binaries and all supported 3rd-party compression libraries. Refer to [`.github/workflows/build_rocksdb_{linux/mac/win}.yaml`](.github/workflows/) for my specific build commands. Thus you can also download my pre-built binaries from [GitHub Actions](https://github.com/gau-nernst/rocksdb-python/actions) (look for the artifacts under **Build RocksDB for Linux/macOS/Windows**). macOS builds are universal2 (support both Apple Intel x86_64 and Apple Silicon ARM64).

OS | Arch | Snappy | LZ4 | Zlib | Zstd | Bzip2 | XPRESS
---|--------------|--------|-----|------|------|-------|--------
Linux | x86_64 | ✅ | ✅ | ✅ | ✅ | ✅ | 
macOS | universal2 | ✅ | ✅ | ✅ | ✅ | ✅ | 
Windows | x86_64 | ✅ | ✅ | ✅ | ✅ | | ✅ (comes with Windows)

Place the built binaries in the root directory of this repo. e.g. `librocksdb.a` on Linux and macOS, `rocksdb.lib` on Windows.

Build Python bindings (this repo)

```
pip install pybind11
python setup.py build_ext -i
```

# Basic usage

```python
from rocksdb_python import Options, PyDB, ReadOptions, WriteOptions

options = Options()
options.IncreaseParallelism()
options.create_if_missing = True

db = PyDB(options, "./test.db")
db.Put(WriteOptions(), b"key", b"value")
v = db.Get(ReadOptions(), b"key")
assert v == b"value"
```
