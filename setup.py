import platform
from glob import glob

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

IS_WIN = platform.system() == "Windows"
__version__ = "0.0.1"


libraries = ["rocksdb"]
extra_win_libs = [
    "Rpcrt4",  # for RpcStringFreeA, UuidCreateSequential, UuidToStringA
    "Shlwapi",  # for PathIsDirectoryA, PathIsRelativeA
]
extra_unix_libs = [
    "z",    # zlib
    "bz2",  # bzip2
]
if IS_WIN:
    libraries.extend(extra_win_libs)
else:
    libraries.extend(extra_unix_libs)

ext_m = Pybind11Extension(
    "rocksdb_python",
    sorted(glob("src/*.cpp")),
    include_dirs=["rocksdb/include"],
    libraries=libraries,
    library_dirs=["./"],
    define_macros=[("VERSION_INFO", __version__)],
    cxx_std=17,
)
ext_modules = [ext_m]

setup(
    name="rocksdb-python",
    version=__version__,
    ext_modules=ext_modules,
    packages=["rocksdb_python"],
)
