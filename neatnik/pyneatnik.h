/*
  Python bindings for NEATnik's global variables and non-standard types.
*/

/*
  Contributors: Fernando Zago.
*/

#include "../neatnik/neatnik.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Binds all global variables and non-standard types to a Python module.
void bind_NEATnik(pybind11::module& m);
