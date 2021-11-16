/*
  An `Experiment` drives the evolution of a `Genus`.

  Data:
  ----
  parameters: the `Parameters*` which characterize this `Experiment`.
  vertexes: a `std::vector<Vertex>` encoding the `Vertex`es of this `Experiment`'s starting minimal `Graph`.
  edges: a `std::vector<Edge>` encoding the `Edge`s of this `Experiment`'s starting minimal `Graph`.
  genus: the `Genus*` to be evolved by this `Experiment`.
  behaviors: an `std::vector<std::vector<double>>` storing the novel behaviors displayed by the `Organism`s evolved in this `Experiment`.
  outcome: an `std::vector<Graph>` storing the `Graph`s of the fittest `Organism`s to evolve in this `Experiment`.

  Constructor:
  -----------
  initialization: initializes this `Experiment`.

  Destructor:
  ----------
  recursive: recursively deletes this `Experiment` and its associated `Parameters` and `Genus`.

  Methods:
  -------
  build: sets up this `Experiment`.
  run: runs this `Experiment`.
  display: displays any of this `Experiment`'s current data.
  drive: drives the evolution of this `Experiment`'s `Genus`.
  assess: scores and curates the input `Organism` with respect to the given performance metric(s).
  novelty: evaluates the input `Organism`'s NOVELTY score.
  fitness: evaluates the input `Organism`'s FITNESS score.
  behavior: extracts the input `Organism`'s behavior.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include <algorithm>
#include "../neatnik/neatnik.hpp"
#include "../experiment/parameters.hpp"
#include "../organism/organism.hpp"
#include "../genus/species.hpp"
#include "../genus/genus.hpp"

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

    // The novel behaviors displayed by the `Organism`s evolved in this `Experiment`.
    std::vector<std::vector<double>> behaviors;

    // This `Experiment`'s outcome.
    std::vector<Graph> outcome;


    // Constructor:

    // Constructor responsible for initializing this `Experiment`.
    Experiment();


    // Destructor:

    // Destructor responsible for recursively deleting this `Experiment` and its associated `Parameters` and `Genus`.
    virtual ~Experiment();


    // Methods:

    // Sets up this `Experiment`.
    void build();

    // Runs this `Experiment`.
    void run();

    // Displays any of this `Experiment`'s current data.
    virtual void display();

    // Drives the evolution of this `Experiment`'s `Genus`.
    void drive(driver_metric metric_);

    // Scores and curates the input `Organism` with respect to the given performance metric(s).
    void assess(Organism* thatOrganism_, const std::vector<int> metrics_);

    // Evaluates the input `Organism`'s NOVELTY score.
    double novelty(Organism* thatOrganism_);

    // Evaluates the input `Organism`'s FITNESS score.
    virtual double fitness(Organism* thatOrganism_) = 0;

    // Extracts the input `Organism`'s behavior.
    virtual std::vector<double> behavior(Organism* thatOrganism_) = 0;
};
