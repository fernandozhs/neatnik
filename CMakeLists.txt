cmake_minimum_required(VERSION 3.10)

# Project name.
project(neatnik)

# C++ Standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Pybind11.
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/pybind11)

pybind11_add_module(neatnik ${PROJECT_SOURCE_DIR}/src/utils/utils.hpp
                            ${PROJECT_SOURCE_DIR}/src/utils/utils.cpp
                            ${PROJECT_SOURCE_DIR}/src/elements/elements.hpp
                            ${PROJECT_SOURCE_DIR}/src/elements/elements.cpp
                            ${PROJECT_SOURCE_DIR}/src/genotype/chromosome.hpp
                            ${PROJECT_SOURCE_DIR}/src/genotype/chromosome.cpp
                            ${PROJECT_SOURCE_DIR}/src/genotype/genotype.hpp
                            ${PROJECT_SOURCE_DIR}/src/genotype/genotype.cpp
                            ${PROJECT_SOURCE_DIR}/src/phenotype/phenotype.hpp
                            ${PROJECT_SOURCE_DIR}/src/phenotype/phenotype.cpp
                            ${PROJECT_SOURCE_DIR}/src/organism/organism.hpp
                            ${PROJECT_SOURCE_DIR}/src/organism/organism.cpp
                            ${PROJECT_SOURCE_DIR}/src/genus/species.hpp
                            ${PROJECT_SOURCE_DIR}/src/genus/species.cpp
                            ${PROJECT_SOURCE_DIR}/src/genus/genus.hpp
                            ${PROJECT_SOURCE_DIR}/src/genus/genus.cpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/parameters.hpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/parameters.cpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/experiment.hpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/experiment.cpp
                            ${PROJECT_SOURCE_DIR}/src/neatnik/neatnik.hpp
                            ${PROJECT_SOURCE_DIR}/src/neatnik/neatnik.cpp
                            ${PROJECT_SOURCE_DIR}/src/organism/pyorganism.hpp
                            ${PROJECT_SOURCE_DIR}/src/organism/pyorganism.cpp
                            ${PROJECT_SOURCE_DIR}/src/genus/pyspecies.hpp
                            ${PROJECT_SOURCE_DIR}/src/genus/pyspecies.cpp
                            ${PROJECT_SOURCE_DIR}/src/genus/pygenus.hpp
                            ${PROJECT_SOURCE_DIR}/src/genus/pygenus.cpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/pyparameters.hpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/pyparameters.cpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/pyexperiment.hpp
                            ${PROJECT_SOURCE_DIR}/src/experiment/pyexperiment.cpp
                            ${PROJECT_SOURCE_DIR}/src/neatnik/pyneatnik.hpp
                            ${PROJECT_SOURCE_DIR}/src/neatnik/pyneatnik.cpp
                            ${PROJECT_SOURCE_DIR}/src/python/pymodule.cpp)


# Tweaks the name of the shared library to match what Python expects.
set_target_properties(neatnik PROPERTIES SUFFIX .so)
set_target_properties(neatnik PROPERTIES PREFIX "")