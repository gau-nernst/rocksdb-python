# RocksDB Python

[![Build with conda](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_conda.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build_conda.yaml)

Cross-platform Python bindings for [RocksDB](https://github.com/facebook/rocksdb). Other RocksDB Python bindings libraries usually don't provide Windows builds. This repo aims to target all OSes, including Windows.

This project helps me to learn using C++ libraries in Python with [pybind11](https://github.com/pybind/pybind11).

# Installation

## From wheels

TBD

## From source

### Inside a conda environment (easiest)

[`conda-forge`](https://anaconda.org/conda-forge/rocksdb) provides pre-built RocksDB for Linux x64, MacOS x64 and ARM64, Windows x64.

```bash
# on Linux and MacOS
conda install rocksdb -c conda-forge
pip install git+https://github.com/gau-nernst/rocksdb-python.git

# on Windows
conda install rocksdb zlib -c conda-forge
LZ4_LIB=liblz4 BZ2_LIB=libbz2 pip install git+https://github.com/gau-nernst/rocksdb-python.git
```

### With Homebrew (MacOS only)

[Homebrew](https://formulae.brew.sh/formula/rocksdb) provides pre-built RocksDB for MacOS, both x64 and ARM64.

```bash
brew install rocksdb
pip install git+https://github.com/gau-nernst/rocksdb-python.git
```

### Build RocksDB from source

Refer to: https://github.com/facebook/rocksdb/blob/main/INSTALL.md

On Linux and MacOS, you can install RocksDB's dependencies and compile RocksDB with `make`.

```bash
# install dependencies on Ubuntu
sudo apt-get -y install libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev

# install dependencies on MacOS with Homebrew
brew install snappy lz4 zstd  # zlib and bzip2 come with MacOS

git clone https://github.com/gau-nernst/rocksdb-python
cd rocksdb-python
git clone https://github.com/facebook/rocksdb --branch v8.0.0
PORTABLE=1 EXTRA_CFLAGS=-fPIC EXTRA_CXXFLAGS=-fPIC make -C rocksdb static_lib -j4
cp rocksdb/include .
cp rocksdb/librocksdb.a .
pip install .
```

Building RocksDB on Windows is complicated. vcpkg can help you, but it doesn't allow building Release target from CLI. You can refer to my automated GHA workflow at [.github/workflows/build_rocksdb.yaml](.github/workflows/build_rocksdb.yaml) to see how to build RocksDB (and its dependencies) with CMake.

### Other notes

`setup.py` assumes RocksDB was compiled with all dependencies enabled i.e. snappy, lz4, zlib, zstd, bz2. It will also try to add header paths for compilation and library paths for linking:

- On all platforms: `./rocksdb` for source build; `$CONDA_PREFIX$` for conda libs (automatically added by conda)
- On Windows: `$CONDA_PREFIX$/Library/` for conda libs
- On MacOS: `$(brew --prefix)` for Homebrew libs

On Windows, RocksDB's dependencies library files may have different names depending on how you build them. To link them correctly, specify their names via environment variables.

e.g. with RocksDB installed from conda-forge

```bash
LZ4_LIB=liblz4 BZ2_LIB=libbz2 pip install .
```

## My RocksDB build

Static library. Also build static deps.

## Basic usage

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
