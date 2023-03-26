import platform
import subprocess
from glob import glob

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

IS_WIN = platform.system() == "Windows"
__version__ = "0.0.1"

include_dirs = []
library_dirs = []


if platform.system() == "Darwin":
    try:
        proc = subprocess.run(["brew", "--prefix"], check=True, capture_output=True)
        HOMEBREW_PATH = proc.stdout.decode().strip()
        include_dirs.append(HOMEBREW_PATH + "/include")
        library_dirs.append(HOMEBREW_PATH + "/lib")
    except subprocess.CalledProcessError:
        pass

# def get_libraries():
#     libraries = ["rocksdb", "lz4", "snappy"]
#     if IS_WIN:
#         libraries.extend(["Rpcrt4", "Shlwapi"]) # for port_win.cc
#         libraries.extend(["zlibstatic", "zstd_static"])
#         libraries.append("Cabinet") # for XPRESS
#     else:
#         libraries.extend(["bz2", "z", "zstd"])
#     return libraries

ext = Pybind11Extension(
    "rocksdb_python",
    sorted(glob("src/*.cpp")),
    include_dirs=include_dirs,
    libraries=["rocksdb"],
    library_dirs=library_dirs,
    define_macros=[("VERSION_INFO", __version__)],
    cxx_std=17,
)

setup(
    name="rocksdb-python",
    version=__version__,
    ext_modules=[ext],
)
