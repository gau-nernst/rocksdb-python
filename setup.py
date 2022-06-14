import platform
from glob import glob

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

IS_WIN = platform.system() == "Windows"
__version__ = "0.0.1"


libraries = ["rocksdb"]
if not IS_WIN:
    libraries.extend(["z", "bz2"])
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
