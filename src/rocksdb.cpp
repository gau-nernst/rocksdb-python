#include <pybind11/pybind11.h>
namespace py = pybind11;

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

void init_db(py::module_ &);
void init_options(py::module_ &);

PYBIND11_MODULE(rocksdb_python, m)
{
    init_db(m);
    init_options(m);
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
}
