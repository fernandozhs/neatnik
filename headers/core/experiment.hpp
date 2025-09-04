/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <stdexcept>
#include <vector>
#include <tuple>
#include <algorithm>
#include <mpi.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "neatnik.hpp"
#include "parameters.hpp"
#include "organism.hpp"
#include "species.hpp"
#include "genus.hpp"


class Experiment
{
public:

    // Properties:

    int MPI_rank;
    int MPI_size;

    std::vector<int> MPI_counts;
    std::vector<int> MPI_displacements;

    pybind11::ssize_t input_counter = 0;
    pybind11::ssize_t output_counter = 0;

    pybind11::array_t<double> stimuli;

    Genus* genus = nullptr;


    // Constructor:

    Experiment();


    // Destructor:

    virtual ~Experiment();


    // Methods:

    void set(pybind11::array_t<double> stimuli_);

    void set(GenotypeData data_);

    void set(GenusData data_);

    void initialize();

    void finalize();

    void run();

    void score();

    virtual void display();

    virtual void execute();

    virtual double fitness(Organism* organism_) = 0;
};
