/*
  An `Experiment` drives the evolution of a `Genus`.

  Data:
  ----
  parameters: the `Parameters*` which characterize this `Experiment`.
  vertexes: a `std::vector<Vertex>` encoding the `Vertex`es of this `Experiment`'s starting minimal `Graph`.
  edges: a `std::vector<Edge>` encoding the `Edge`s of this `Experiment`'s starting minimal `Graph`.
  genus: the `Genus*` to be evolved by this `Experiment`.

  Constructor:
  -----------
  initialization: initializes this `Experiment`.

  Destructor:
  ----------
  recursive: recursively deletes this `Experiment` and its associated `Parameters` and `Genus`.

  Methods:
  -------
  populate: populates this `Experiment`'s `Genus`.
  run: runs this `Experiment`.
  evaluate: evaluates the performance of the this `Experiment`'s `Genus`.
  graph: produces the `Graph` associated with this `Experiment`'s DOMINANT `Organism`'s `Genotype`.
  performance: scores the performance of the input `Organism`.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "../neatnik/neatnik.h"
#include "../experiment/parameters.h"
#include "../organism/organism.h"
#include "../genus/species.h"
#include "../genus/genus.h"

class Experiment
{
public:

    // Data:

    // This `Experiment`'s `Parameters*`.
    Parameters* parameters;

    // A `std::vector<Vertex>` and `std::vector<Edge>` encoding this `Experiment`'s starting minimal `Graph`.
    std::vector<Vertex> vertexes;
    std::vector<Edge> edges;

    // The `Genus*` to be evolved by this `Experiment`.
    Genus* genus;


    // Constructor:

    // Constructor responsible for initializing this `Experiment`.
    Experiment();


    // Destructor:

    // Destructor responsible for recursively deleting this `Experiment` and its associated `Parameters` and `Genus`.
    virtual ~Experiment();


    // Methods:

    // Populates this `Experiment`'s `Genus`.
    void populate();

    // Runs this `Experiment`.
    void run(bool verbose_ = true);

    // Evaluates the performance of this `Experiment`'s `Genus`.
    void evaluate();

    // Produces the `Graph` associated with this `Experiment`'s DOMINANT `Organism`'s `Genotype`.
    Graph graph();

    // Scores the performance of the input `Organism`.
    virtual double performance(Organism* thatOrganism_) = 0;
};
