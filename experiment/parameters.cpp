#include "parameters.h"

// Constructor:

// Default constructor responsible for initializing this `Parameters` instance.
Parameters::Parameters()
{
    // Number of generational cycles for which an `Experiment` will run.
    generational_cycles = 0;

    // Number of `Organism`s in an `Experiment`'s `Genus`.
    population_size = 0;

    // Number of attempts at mutating a `Genotype`.
    mutation_attempts = 0;

    // Number of attempts at producing an offspring `Organism`.
    spawning_attempts = 0;

    // Bounding value for the generation and replacement of `Link` weights.
    weight_bound = 0.;

    // Perturbation power when altering `Link` weights.
    perturbation_power = 0.;

    // The activation a new HIDDEN `Node` is initially equipped with.
    initial_activation = IDENTITY;

    // Fraction of rejected `Organism`s at a given evolution cycle.
    rejection_fraction = 0.;

    // Number of evolution cycles beyond which a stagnated `Species` can be discarded.
    stagnation_threshold = 0;

    // The degree of similarity beyond which `Organism`s group in separate `Species`.
    compatibility_threshold = 0.;

    // Relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
    compatibility_weights = {0., 0., 0.};

    // P.M.F. for enabling of a random DISABLED `Link`: {FAILURE, SUCCESS}.
    enabling_link = {0., 0.};

    // P.M.F. for altering each ENABLED `Link`: {FAILURE, SUCCESS}.
    altering_links = {0., 0.};

    // P.M.F. for altering a `Link`'s weight: {FAILURE, PERTURB, REPLACE}.
    altering_weight = {0., 0., 0.};

    // P.M.F. for adding a `Link` of a given role: {FAILURE, FORWARD, RECURRENT, BIASING, LOOPED}.
    adding_link = {0., 0., 0., 0., 0.};

    // P.M.F. for enabling a DISABLED INPUT `Node` and connecting it to another `Node` of a given role: {FAILURE, HIDDEN, OUTPUT}.
    enabling_node = {0., 0., 0.};

    // P.M.F. for altering each HIDDEN `Node`: {FAILURE, SUCCESS}.
    altering_nodes = {0., 0.};

    // P.M.F. for altering a `Node`'s activation: {FAILURE, HEAVISIDE, RELU, LOGISTIC}.
    altering_activation = {0., 0., 0., 0.};

    // P.M.F. for adding a `Node` by splitting a `Link` of a given role: {FAILURE, FORWARD, RECURRENT}.
    adding_node = {0., 0., 0.};

    // P.M.F. for assimilating each homologous `Link`: {FAILURE, SUCCESS}.
    assimilating_links = {0., 0.};

    // P.M.F. for assimilating each homologous `Node`: {FAILURE, SUCCESS}.
    assimilating_nodes = {0., 0.};

    // P.M.F. for assimilating a homologous `Link`'s weight: {FAILURE, SUCCESS}.
    assimilating_weight = {0., 0.};

    // P.M.F. for assimilating a homologous `Node`'s activation function: {FAILURE, SUCCESS}.
    assimilating_activation = {0., 0.};

    // P.M.F. for spawning a new `Organism` through a given process: {MUTATION, ASSIMILATION}.
    spawning_organism = {0., 0.};
}


// Destructor:

// Default destructor responsible for deleting this `Parameters` instance.
Parameters::~Parameters()
{
    // Deletes this `Parameters` instance.
}
