# RocksDB Python

[![Build](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build.yaml/badge.svg)](https://github.com/gau-nernst/rocksdb-python/actions/workflows/build.yaml)

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
git clone https://github.com/gau-nernst/rocksdb-python
cd rocksdb-python
pip install .

# on Windows
conda install rocksdb zlib -c conda-forge
git clone https://github.com/gau-nernst/rocksdb-python
cd rocksdb-python
LZ4_LIB=liblz4 BZ2_LIB=libbz2 pip install .
```

### With Homebrew (MacOS only)

[Homebrew](https://formulae.brew.sh/formula/rocksdb) provides pre-built RocksDB for MacOS, both x64 and ARM64.

```bash
brew install rocksdb

git clone https://github.com/gau-nernst/rocksdb-python
cd rocksdb-python
pip install .
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
PORTABLE=1 EXTRA_CFLAGS=-fPIC EXTRA_CXXFLAGS=-fPIC make -C rocksdb static_lib -j $(nproc)
pip install .
```

On Windows, you can install RocksDB and its dependencies with vcpkg. Make sure to use triplet `x64-windows-static-md`.

```bash
vcpkg install rocksdb[core,bzip2,lz4,snappy,zlib,zstd]:x64-windows-static-md

git clone https://github.com/gau-nernst/rocksdb-python
cd rocksdb-python
ZLIB_LIB=zlib pip install .
```

### Other notes

`setup.py` assumes RocksDB was compiled with all dependencies enabled i.e. snappy, lz4, zlib, zstd, bz2. It will also try to add header and library paths for linking:

- On all platforms: `./rocksdb` for source build; `$CONDA_PREFIX$` for conda libs (automatically added by conda)
- On Windows: `$CONDA_PREFIX$/Library/` for conda libs, `VCPKG_ROOT/installed/x64-windows-static-md` for vcpkg libs
- On MacOS: `$(brew --prefix)` for Homebrew libs

On Windows, RocksDB's dependencies library files may have different names depending on how you build them. To link them correctly, specify their names via environment variables.

e.g. with RocksDB installed from conda-forge

```bash
LZ4_LIB=liblz4 BZ2_LIB=libbz2 pip install .
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
