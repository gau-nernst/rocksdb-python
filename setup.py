import os
import platform
import subprocess
from glob import glob
from pathlib import Path

from pybind11.setup_helpers import ParallelCompile, Pybind11Extension, naive_recompile
from setuptools import setup


__version__ = "0.0.2"

CURRENT_DIR = Path(__file__).parent

IS_LINUX = platform.system() == "Linux"
IS_MACOS = platform.system() == "Darwin"
IS_WIN = platform.system() == "Windows"

_default_lib_names = dict(
    rocksdb="rocksdb",
    snappy="snappy",
    lz4="lz4",
    zlib="z",
    zstd="zstd",
    bz2="bz2",
)
lib_names = {k: os.environ.get(k.upper() + "_LIB", v) for k, v in _default_lib_names.items()}

include_dirs = []
library_dirs = []


def add_path(path, include="include", lib="lib"):
    include_path = path / include
    if include_path.exists():
        include_dirs.append(str(include_path))

    lib_path = path / lib
    if lib_path.exists():
        library_dirs.append(str(lib_path))


add_path(CURRENT_DIR)

if IS_MACOS and subprocess.run(["which", "brew"]).returncode == 0:
    proc = subprocess.run(["brew", "--prefix"], check=True, capture_output=True)
    HOMEBREW_PREFIX = Path(proc.stdout.decode().strip())
    add_path(HOMEBREW_PREFIX)

if IS_WIN and "CONDA_PREFIX" in os.environ:
    add_path(Path(os.environ["CONDA_PREFIX"]) / "Library")


libraries = [lib for lib in lib_names.values() if lib]
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

ParallelCompile("NPY_NUM_BUILD_JOBS", needs_recompile=naive_recompile).install()
setup(
    name="rocksdb-python",
    version=__version__,
    ext_modules=[ext],
)
