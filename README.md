# NEATnik

[`NEATnik`](https://github.com/fernandozhs/neatnik) is a Python-wrapped C++ implementation of the [`NEAT`](https://ieeexplore.ieee.org/document/6790655) (Neuro-Evolution of Augmenting Topologies) algorithm originally developed by Kenneth Stanley.

## Requirements

* [GCC](http://gcc.gnu.org/) compiler compatible with C++17.
* [CMake](http://cmake.org/) version 3.10 or more recent.
* [Python](http://www.python.org/) release 3.5 or higher.

## Dependencies

* [`pybind11`](http://github.com/pybind/pybind11): a lightweight header-only library that exposes C++ types in Python and vice versa.


## Installation

### Linux

Recursively clone this repository within the directory of your choice.

```
git clone --recursive https://github.com/fernandozhs/neatnik.git
```

Within `../neatnik`, run the following shell script to build both `pybind11` and `NEATnik`.

```
sudo ./install.sh
```

If successful, this will have produced a file named `neatnik.so` within `../neatnik/build`. In order to conclude the installation, ensure your `PYTHONPATH` environment variable points to the location of this shared library object.

### OSX

Recursively clone this repository within the directory of your choice.

```
git clone --recursive https://github.com/fernandozhs/neatnik.git
```

Within `../neatnik`, run the following shell script to build both `pybind11` and `NEATnik`.

```
sudo sh ./install.sh
```

If successful, the above instructions will have produced a file named `neatnik.so` within `../neatnik/build`. In order to conclude the installation, ensure your `PYTHONPATH` environment variable points to the location of this shared library object.


## Scripts

Sample Python scripts employing [`NEATnik`](https://github.com/fernandozhs/neatnik) can be found at the [`NEATnik Scripts`](http://github.com/fernandozhs/neatnik-scripts) sister repository.
