#!/bin/sh
# Author: Fernando Zago

# Source directories.
NEATNIK_SOURCE_DIR="./"
PYBIND11_SOURCE_DIR="./extern/pybind11/"

# Build directories.
NEATNIK_BUILD_DIR="./build/"
PYBIND11_BUILD_DIR="./extern/pybind11/build/"

# Checks whether PYBIND11_BUILD_DIR exists.
if [ -d "${PYBIND11_BUILD_DIR}" ]; then
	# Cleans the build directory.
	sudo rm -rf "${PYBIND11_BUILD_DIR}/*"
else
	# Creates the build directory.
	mkdir "${PYBIND11_BUILD_DIR}"
fi

# Compiles pybind11.
cmake -S "${PYBIND11_SOURCE_DIR}" -B "${PYBIND11_BUILD_DIR}"
make -C "${PYBIND11_BUILD_DIR}"

# Checks whether NEATNIK_BUILD_DIR exists.
if [ -d "${NEATNIK_BUILD_DIR}" ]; then
	# Cleans the build directory.
	sudo rm -rf "${NEATNIK_BUILD_DIR}/*"
else
	# Creates the build directory.
	mkdir "${NEATNIK_BUILD_DIR}"
fi

# Compiles NEATnik.
cmake -S "${NEATNIK_SOURCE_DIR}" -B "${NEATNIK_BUILD_DIR}"
make -C "${NEATNIK_BUILD_DIR}"

