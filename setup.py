import platform
from glob import glob

from pybind11.setup_helpers import Pybind11Extension, ParallelCompile, naive_recompile
from setuptools import setup

IS_WIN = platform.system() == "Windows"
__version__ = "0.0.1"


def get_libraries():
    libraries = ["rocksdb", "lz4", "snappy"]
    if IS_WIN:
        libraries.extend(["Rpcrt4", "Shlwapi"])  # for port_win.cc
        libraries.extend(["zlibstatic", "zstd_static"])
        libraries.append("Cabinet")  # for XPRESS
    else:
        libraries.extend(["bz2", "z", "zstd"])
    return libraries


ext_m = Pybind11Extension(
    "rocksdb_python",
    sorted(glob("src/*.cpp")),
    include_dirs=["rocksdb/include"],
    libraries=get_libraries(),
    library_dirs=["."],
    define_macros=[("VERSION_INFO", __version__)],
    cxx_std=17,
)
ext_modules = [ext_m]

ParallelCompile("NPY_NUM_BUILD_JOBS", needs_recompile=naive_recompile).install()
setup(
    name="rocksdb-python",
    version=__version__,
    ext_modules=ext_modules,
    packages=["rocksdb_python"],
)
