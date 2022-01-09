/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <mpi.h>
#include <vector>
#include <algorithm>
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

    std::vector<Vertex> vertexes;
    std::vector<Edge> edges;

    std::vector<std::vector<std::vector<double>>> stimuli;

    Genus* genus;


    // Constructor:

    Experiment();


    // Destructor:

    virtual ~Experiment();


    // Methods:

    void run();

    void score();

    virtual void display();

    virtual double fitness(Organism* organism_) = 0;
};
