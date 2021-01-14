cmake_minimum_required(VERSION 3.10)

# Project name.
project(neatnik)

# C++ Standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Pybind11.
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/pybind11)

pybind11_add_module(neatnik ${PROJECT_SOURCE_DIR}/utils/utils.h
                            ${PROJECT_SOURCE_DIR}/utils/utils.cpp
                            ${PROJECT_SOURCE_DIR}/elements/elements.h
                            ${PROJECT_SOURCE_DIR}/elements/elements.cpp
                            ${PROJECT_SOURCE_DIR}/genotype/chromosome.h
                            ${PROJECT_SOURCE_DIR}/genotype/chromosome.cpp
                            ${PROJECT_SOURCE_DIR}/genotype/genotype.h
                            ${PROJECT_SOURCE_DIR}/genotype/genotype.cpp
                            ${PROJECT_SOURCE_DIR}/phenotype/phenotype.h
                            ${PROJECT_SOURCE_DIR}/phenotype/phenotype.cpp
                            ${PROJECT_SOURCE_DIR}/organism/organism.h
                            ${PROJECT_SOURCE_DIR}/organism/organism.cpp
                            ${PROJECT_SOURCE_DIR}/genus/species.h
                            ${PROJECT_SOURCE_DIR}/genus/species.cpp
                            ${PROJECT_SOURCE_DIR}/genus/genus.h
                            ${PROJECT_SOURCE_DIR}/genus/genus.cpp
                            ${PROJECT_SOURCE_DIR}/experiment/parameters.h
                            ${PROJECT_SOURCE_DIR}/experiment/parameters.cpp
                            ${PROJECT_SOURCE_DIR}/experiment/experiment.h
                            ${PROJECT_SOURCE_DIR}/experiment/experiment.cpp
                            ${PROJECT_SOURCE_DIR}/neatnik/neatnik.h
                            ${PROJECT_SOURCE_DIR}/neatnik/neatnik.cpp
                            ${PROJECT_SOURCE_DIR}/organism/pyorganism.h
                            ${PROJECT_SOURCE_DIR}/organism/pyorganism.cpp
                            ${PROJECT_SOURCE_DIR}/genus/pyspecies.h
                            ${PROJECT_SOURCE_DIR}/genus/pyspecies.cpp
                            ${PROJECT_SOURCE_DIR}/genus/pygenus.h
                            ${PROJECT_SOURCE_DIR}/genus/pygenus.cpp
                            ${PROJECT_SOURCE_DIR}/experiment/pyparameters.h
                            ${PROJECT_SOURCE_DIR}/experiment/pyparameters.cpp
                            ${PROJECT_SOURCE_DIR}/experiment/pyexperiment.h
                            ${PROJECT_SOURCE_DIR}/experiment/pyexperiment.cpp
                            ${PROJECT_SOURCE_DIR}/neatnik/pyneatnik.h
                            ${PROJECT_SOURCE_DIR}/neatnik/pyneatnik.cpp
                            ${PROJECT_SOURCE_DIR}/python/pymodule.cpp)


# Tweaks the name of the shared library to match what Python expects.
set_target_properties(neatnik PROPERTIES SUFFIX .so)
set_target_properties(neatnik PROPERTIES PREFIX "")