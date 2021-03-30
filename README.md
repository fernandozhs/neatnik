# NEATnik

[`NEATnik`](https://github.com/fernandozhs/neatnik) is a Python-wrapped C++ implementation of the [`NEAT`](https://ieeexplore.ieee.org/document/6790655) (Neuro-Evolution of Augmenting Topologies) algorithm originally developed by Kenneth Stanley.


## Dependencies

* [`pybind11`](http://github.com/pybind/pybind11): a lightweight header-only library that exposes C++ types in Python and vice versa.


## Installation

Recursively clone this repository within the directory of your choice.

```
git clone --recursive https://github.com/fernandozhs/neatnik.git
```

Build and compile [`pybind11`](http://github.com/pybind/pybind11) by executing the following list of commands within `../neatnik/extern/pybind11`.

```
mkdir build
cd build
cmake ..
make
```

Build and compile [`NEATnik`](https://github.com/fernandozhs/neatnik) by executing the following list of commands within `../neatnik`.

```
mkdir build
cd build
cmake ..
make
```

If successful, the above instructions will have produced a file named `neatnik.so` within `../neatnik/build`. In order to conclude the installation, ensure your `PYTHONPATH` environment variable points to the location of this shared library object.


## Scripts

Sample Python scripts employing [`NEATnik`](https://github.com/fernandozhs/neatnik) can be found at the [`NEATnik Scripts`](http://github.com/fernandozhs/neatnik_scripts) sister repository.
