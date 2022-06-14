from glob import glob

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

__version__ = "0.0.1"


ext_m = Pybind11Extension(
    "rocksdb_python",
    sorted(glob("src/*.cpp")),
    include_dirs=["rocksdb/include"],
    libraries=["rocksdb", "z", "bz2"],
    library_dirs=["./"],
    define_macros = [('VERSION_INFO', __version__)],
    cxx_std=17,
)
ext_modules = [ext_m]

setup(
    name="rocksdb-python",
    version=__version__,
    ext_modules=ext_modules,
    packages=["rocksdb_python"],
)
