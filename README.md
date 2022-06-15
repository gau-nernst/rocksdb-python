# RocksDB Python

[![Build RocksDB Linux](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_linux.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_linux.yaml)
[![Build RocksDB macOS](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_mac.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_mac.yaml)
[![Build RocksDB Windows](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_win.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_rocksdb_win.yaml)
[![Build](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build.yaml)

Cross-platform Python bindings for RocksDB. Other RocksDB Python bindings libraries usually don't provide Windows builds. This repo aims to target all OSes, including Windows.

This project helps me to learn using C++ libraries in Python with pybind11.

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
