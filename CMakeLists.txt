cmake_minimum_required(VERSION 3.10)

# Project name.
project(neatnik)

# C++ Standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# MPI.
find_package(MPI REQUIRED)

# Include Directories.
include_directories(${MPI_INCLUDE_PATH})
include_directories(${PROJECT_SOURCE_DIR}/headers/core)
include_directories(${PROJECT_SOURCE_DIR}/headers/wrapper)
include_directories(${PROJECT_SOURCE_DIR}/sources/core)
include_directories(${PROJECT_SOURCE_DIR}/sources/wrapper)

# Pybind11.
add_subdirectory(${PROJECT_SOURCE_DIR}/external/pybind11)

pybind11_add_module(neatnik ${PROJECT_SOURCE_DIR}/headers/core/utilities.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/utilities.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/elements.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/elements.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/chromosome.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/chromosome.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/genotype.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/genotype.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/phenotype.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/phenotype.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/organism.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/organism.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/species.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/species.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/genus.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/genus.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/parameters.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/parameters.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/experiment.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/experiment.cpp
                            ${PROJECT_SOURCE_DIR}/headers/core/neatnik.hpp
                            ${PROJECT_SOURCE_DIR}/sources/core/neatnik.cpp
                            ${PROJECT_SOURCE_DIR}/headers/wrapper/pygenotype.hpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pygenotype.cpp
                            ${PROJECT_SOURCE_DIR}/headers/wrapper/pyorganism.hpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pyorganism.cpp
                            ${PROJECT_SOURCE_DIR}/headers/wrapper/pyspecies.hpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pyspecies.cpp
                            ${PROJECT_SOURCE_DIR}/headers/wrapper/pygenus.hpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pygenus.cpp
                            ${PROJECT_SOURCE_DIR}/headers/wrapper/pyparameters.hpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pyparameters.cpp
                            ${PROJECT_SOURCE_DIR}/headers/wrapper/pyexperiment.hpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pyexperiment.cpp
                            ${PROJECT_SOURCE_DIR}/headers/wrapper/pyneatnik.hpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pyneatnik.cpp
                            ${PROJECT_SOURCE_DIR}/sources/wrapper/pymodule.cpp)

# Ensures MPI is properly linked.
target_link_libraries(neatnik PRIVATE ${MPI_C_LIBRARIES})

# Tweaks the name of the shared library to match what Python expects.
set_target_properties(neatnik PROPERTIES SUFFIX .so)
set_target_properties(neatnik PROPERTIES PREFIX "")