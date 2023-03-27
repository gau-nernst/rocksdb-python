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

IS_CONDA_AVAILABLE = subprocess.run(["conda", "info"]).returncode == 0
CONDA_PREFIX = Path(os.environ["CONDA_PREFIX"]) if IS_CONDA_AVAILABLE else None

IS_LINUX = platform.system() == "Linux"
IS_MACOS = platform.system() == "Darwin"
IS_WIN = platform.system() == "Windows"

SNAPPY_LIB = os.environ.get("SNAPPY_LIB", "snappy")
LZ4_LIB = os.environ.get("LZ4_LIB", "liblz4" if IS_WIN else "lz4")
ZLIB_LIB = os.environ.get("ZLIB_LIB", "z")
ZSTD_LIB = os.environ.get("ZSTD_LIB", "zstd")
BZ2_LIB = os.environ.get("BZ2_LIB", "bz2")

LOCAL_ROCKSDB_PATH = CURRENT_DIR / "rocksdb"
if os.path.exists(LOCAL_ROCKSDB_PATH):
    add_path(LOCAL_ROCKSDB_PATH, lib="")

if IS_MACOS:
    try:
        proc = subprocess.run(["brew", "--prefix"], check=True, capture_output=True)
        HOMEBREW_PREFIX = Path(proc.stdout.decode().strip())
        add_path(HOMEBREW_PREFIX)
    except FileNotFoundError:  # brew is not installed
        pass

if platform.system() == "Windows":
    print(CONDA_PREFIX)
    if IS_CONDA_AVAILABLE:
        add_path(CONDA_PREFIX / "Library")

    try:
        proc = subprocess.run(["where", "vcpkg"], check=True, capture_output=True)
        VCPKG_PREFIX = Path(proc.stdout.decode().strip()).parent
        add_path(VCPKG_PREFIX / "installed" / "x64-windows")
        print(list((VCPKG_PREFIX / "installed" / "x64-windows" / "include").iterdir()))
    except Exception as e:  # vcpkg is not installed
        print(e)

libraries = ["rocksdb", SNAPPY_LIB, LZ4_LIB, ZLIB_LIB, ZSTD_LIB, BZ2_LIB]
if IS_WIN:
    libraries.extend(["Rpcrt4", "Shlwapi"])  # for port_win.cc
    libraries.append("Cabinet")  # for XPRESS


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
