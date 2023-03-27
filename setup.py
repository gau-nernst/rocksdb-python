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


def add_path(path, include="include", lib="lib"):
    include_dirs.append(str(path / include))
    library_dirs.append(str(path / lib))


CURRENT_DIR = Path(__file__).parent

CONDA_PREFIX = os.environ.get("CONDA_PREFIX", None)
if CONDA_PREFIX is not None:
    CONDA_PREFIX = Path(CONDA_PREFIX)
    add_path(CONDA_PREFIX)

LOCAL_ROCKSDB_PATH = CURRENT_DIR / "rocksdb"
if os.path.exists(LOCAL_ROCKSDB_PATH):
    add_path(LOCAL_ROCKSDB_PATH, lib="")

if platform.system() == "Darwin":
    try:
        proc = subprocess.run(["brew", "--prefix"], check=True, capture_output=True)
        HOMEBREW_PREFIX = Path(proc.stdout.decode().strip())
        add_path(HOMEBREW_PREFIX)
    except FileNotFoundError:
        pass

if platform.system() == "Windows":
    try:
        proc = subprocess.run(["where", "vcpkg"], check=True, capture_output=True)
        VCPKG_PREFIX = Path(proc.stdout.decode().strip()).parent
        add_path(VCPKG_PREFIX / "installed" / "x64-windows")
    except Exception as e:
        print(e)

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
