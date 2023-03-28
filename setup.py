import os
import platform
import subprocess
from glob import glob
from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup


__version__ = "0.0.1"

CURRENT_DIR = Path(__file__).parent

CONDA_PREFIX = Path(os.environ["CONDA_PREFIX"]) if "CONDA_PREFIX" in os.environ else None

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
extra_objects = []  # for static linking


def add_path(path, include="include", lib="lib"):
    include_path = path / include
    if include_path.exists():
        include_dirs.append(str(include_path))

    lib_path = path / lib
    if lib_path.exists():
        library_dirs.append(str(lib_path))


add_path(CURRENT_DIR / "rocksdb", lib="")

if IS_MACOS:
    try:
        proc = subprocess.run(["brew", "--prefix"], check=True, capture_output=True)
        HOMEBREW_PREFIX = Path(proc.stdout.decode().strip())
        add_path(HOMEBREW_PREFIX)

        # prefer static libs from Homebrew
        for k, v in lib_names.items():
            static_lib_path = HOMEBREW_PREFIX / "lib" / f"lib{v}.a"
            if static_lib_path.exists():
                extra_objects.append(str(static_lib_path))
                lib_names[k] = None

    except FileNotFoundError:  # brew is not installed
        pass

if IS_WIN:
    if CONDA_PREFIX is not None:
        add_path(CONDA_PREFIX / "Library")

    proc = subprocess.run(["where", "vcpkg"], capture_output=True)
    if proc.returncode == 0:
        VCPKG_PREFIX = Path(proc.stdout.decode().strip()).parent
        add_path(VCPKG_PREFIX / "installed" / "x64-windows-static-md")


libraries = [lib for lib in lib_names.values() if lib is not None]
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
    extra_objects=extra_objects,
)

setup(
    name="rocksdb-python",
    version=__version__,
    ext_modules=[ext],
)
