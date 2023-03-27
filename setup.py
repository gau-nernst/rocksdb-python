import os
import platform
import subprocess
from glob import glob
from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

__version__ = "0.0.1"

include_dirs = []
library_dirs = []

CURRENT_DIR = Path(__file__).parent

CONDA_PREFIX = os.environ.get("CONDA_PREFIX", None)
if CONDA_PREFIX is not None:
    include_dirs.append(CONDA_PREFIX + "/include")
    library_dirs.append(CONDA_PREFIX + "/lib")

LOCAL_ROCKSDB_PATH = CURRENT_DIR / "rocksdb"
if LOCAL_ROCKSDB_PATH.exists():
    include_dirs.append(str(LOCAL_ROCKSDB_PATH / "include"))
    library_dirs.append(str(LOCAL_ROCKSDB_PATH / "build"))

if platform.system() == "Darwin":
    try:
        proc = subprocess.run(["brew", "--prefix"], check=True, capture_output=True)
        HOMEBREW_PREFIX = proc.stdout.decode().strip()
        include_dirs.append(HOMEBREW_PREFIX + "/include")
        library_dirs.append(HOMEBREW_PREFIX + "/lib")
    except FileNotFoundError:
        pass

libraries = ["rocksdb", "snappy", "z", "bz2", "lz4", "zstd"]
if platform.system() == "Windows":
    libraries.append("Shlwapi")
    libraries.append("Rpcrt4")

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
    libraries=libraries,
    library_dirs=library_dirs,
    define_macros=[("VERSION_INFO", __version__)],
    cxx_std=17,
)

setup(
    name="rocksdb-python",
    version=__version__,
    ext_modules=[ext],
)
