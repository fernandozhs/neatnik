/*
  Contributors: Fernando Zago.
*/

#pragma once

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

    std::vector<Vertex> vertexes;
    std::vector<Edge> edges;

    static std::vector<std::vector<std::vector<double>>> stimuli;

    Genus* genus;

    std::vector<std::vector<double>> behaviors;

    std::vector<Graph> outcome;


    // Constructor:

    Experiment();


    // Destructor:

    virtual ~Experiment();


    // Methods:

    void build();

    void run();

    virtual void display();

    void drive(driver_metric metric_);

    void assess(Organism* organism_, const std::vector<int> metrics_);

    double novelty(Organism* organism_);

    virtual double fitness(Organism* organism_) = 0;

    virtual std::vector<double> behavior(Organism* organism_) = 0;
};
