# NEATnik

[`NEATnik`](https://github.com/fernandozhs/neatnik) is a Python-wrapped C++ implementation of the [NEAT](https://direct.mit.edu/evco/article-abstract/10/2/99/1123/Evolving-Neural-Networks-through-Augmenting) (Neuro-Evolution of Augmenting Topologies) algorithm originally developed by Kenneth Stanley.

## Requirements

* [GCC](http://gcc.gnu.org/) compiler compatible with C++17.
* [CMake](http://cmake.org/) version 3.10 or superior.
* [Python](http://www.python.org/) release 3.5 or higher.

## Dependencies

* [`pybind11`](http://github.com/pybind/pybind11): a lightweight header-only library that exposes C++ types in Python and vice versa.


## Installation

Recursively clone this repository within the directory of your choice.

```bash
git clone --recursive https://github.com/fernandozhs/neatnik.git
```

Within `../neatnik`, run the following commands to build both `pybind11` and `NEATnik`.

```bash
chmod +x install.sh
./install.sh
```

If successful, this will have produced a file named `neatnik.so` within `../neatnik/build`. In order to conclude the installation, ensure your `PYTHONPATH` environment variable points to the location of this shared library object.

## Documentation

**[Parameters](manual/parameters.md)**  
&nbsp;  
**[Experiment](manual/experiment.md)**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
┗━━ **[Genus](manual/genus.md)** ━━━ **[Species](manual/species.md)**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
┗━━ **[Organism](manual/organism.md)**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
**[Phenotype](manual/phenotype.md)** ━━┻━━ **[Genotype](manual/genotype.md)**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
┗━━ **[Chromosome](manual/chromosome.md)**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
**[Node](manual/node.md)** ━━┻━━ **[Link](manual/link.md)**

## Scripts

Sample Python scripts employing [`NEATnik`](https://github.com/fernandozhs/neatnik) can be found in the [`NEATnik Scripts`](http://github.com/fernandozhs/neatnik-scripts) repository.
