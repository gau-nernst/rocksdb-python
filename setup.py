import platform
import subprocess
from glob import glob

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

IS_WIN = platform.system() == "Windows"
__version__ = "0.0.1"


def get_libraries():
    libraries = ["rocksdb"]
    if IS_WIN:
        # for port_win.cc
        libraries.extend(["Rpcrt4", "Shlwapi"])
    else:
        # build_detect_platform determines which 3rd-party libraries to use
        # librocksdb.a should be built in the same environment as this script
        cmd = "cd rocksdb && build_tools/build_detect_platform make_config.mk"
        subprocess.run(cmd, shell=True)
        with open("rocksdb/make_config.mk") as f:
            for line in f:
                if line.startswith("PLATFORM_LDFLAGS"):
                    flags = line.split("=", 1)[1].strip().split()
                    libraries.extend(x[2:] for x in flags)
                    break
    return libraries


ext_m = Pybind11Extension(
    "rocksdb_python",
    sorted(glob("src/*.cpp")),
    include_dirs=["rocksdb/include"],
    libraries=get_libraries(),
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
