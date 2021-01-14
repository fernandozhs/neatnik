/*
  Python bindings for the `Parameters` class.
*/

/*
  Contributors: Fernando Zago.
*/

#include "../experiment/parameters.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


// Binds the `Parameters` class to a Python module.
void bind_Parameters(pybind11::module& m);
