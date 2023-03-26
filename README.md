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

Install RocksDB (https://github.com/facebook/rocksdb/blob/main/INSTALL.md)

On Ubuntu, from source

```bash
sudo apt-get -y install libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev
git clone https://github.com/facebook/rocksdb --branch v8.0.0
cd rocksdb
make static_lib -j $(nproc)
```

On MacOS, with Homebrew

```bash
brew install rocksdb
```

On Windows, with vcpkg

```bash
vcpkg install rocksdb:x64-windows
```

Build Python bindings (this repo)

```bash
git clone https://github.com/gau-nernst/rocksdb-python
cd rocksdb-python
pip install .
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
