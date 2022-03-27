#!/bin/sh
# Contributor: Fernando Zago

# Source directories.
NEATNIK_SOURCE_DIR="./"
PYBIND11_SOURCE_DIR="./external/pybind11/"

# Build directories.
NEATNIK_BUILD_DIR="./build/"
PYBIND11_BUILD_DIR="./external/pybind11/build/"

# Builds pybind11.
cmake -S "${PYBIND11_SOURCE_DIR}" -B "${PYBIND11_BUILD_DIR}"
make -C "${PYBIND11_BUILD_DIR}"

# Builds NEATnik.
cmake -S "${NEATNIK_SOURCE_DIR}" -B "${NEATNIK_BUILD_DIR}"
make -C "${NEATNIK_BUILD_DIR}"

