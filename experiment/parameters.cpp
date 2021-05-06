#include "parameters.h"

// The metric responsible for driving the evolution of an `Experiment`'s `Genus`.
driver_metric Parameters::evolution_driver = FITNESS;

// Fitness threshold for `Organism`s' `Graph`s to be stored.
double Parameters::fitness_threshold = 0.;

// Novelty threshold for `Organism`s' behaviors to be stored.
double Parameters::novelty_threshold = 0.;

// Number of nearest neighbors to be considered when assessing an `Organism`'s novelty.
int Parameters::novelty_neighbors = 0;

// The factors by which the novelty threshold should increase and decrease.
std::vector<double> Parameters::novelty_threshold_modifiers = {0., 0.};

// Number of generational cycles for which an `Experiment` will run.
int Parameters::generational_cycles = 0;

// Number of `Organism`s in an `Experiment`'s `Genus`.
int Parameters::population_size = 0;

// Number of attempts at mutating a `Genotype`.
int Parameters::mutation_attempts = 0;

// Number of attempts at producing an offspring `Organism`.
int Parameters::spawning_attempts = 0;

// Bounding value for the generation and replacement of `Link` weights.
double Parameters::weight_bound = 0.;

// Perturbation power when altering `Link` weights.
double Parameters::perturbation_power = 0.;

// The activation a new HIDDEN `Node` is initially equipped with.
node_activation Parameters::initial_activation = IDENTITY;

// Fraction of rejected `Organism`s at a given evolution cycle.
double Parameters::rejection_fraction = 0.;

// Number of evolution cycles beyond which a stagnated `Species` can be discarded.
int Parameters::stagnation_threshold = 0;

// The degree of similarity beyond which `Organism`s group in separate `Species`.
double Parameters::compatibility_threshold = 0.;

// Relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
std::vector<double> Parameters::compatibility_weights = {0., 0., 0.};

// P.M.F. for enabling of a random DISABLED `Link`: {FAILURE, SUCCESS}.
std::vector<double> Parameters::enabling_link = {0., 0.};

// P.M.F. for altering each ENABLED `Link`: {FAILURE, SUCCESS}.
std::vector<double> Parameters::altering_links = {0., 0.};

// P.M.F. for altering a `Link`'s weight: {FAILURE, PERTURB, REPLACE}.
std::vector<double> Parameters::altering_weight = {0., 0., 0.};

// P.M.F. for adding a `Link` of a given role: {FAILURE, FORWARD, RECURRENT, BIASING, LOOPED}.
std::vector<double> Parameters::adding_link = {0., 0., 0., 0., 0.};

// P.M.F. for enabling a DISABLED INPUT `Node` and connecting it to another `Node` of a given role: {FAILURE, HIDDEN, OUTPUT}.
std::vector<double> Parameters::enabling_node = {0., 0., 0.};

// P.M.F. for altering each HIDDEN `Node`: {FAILURE, SUCCESS}.
std::vector<double> Parameters::altering_nodes = {0., 0.};

// P.M.F. for altering a `Node`'s activation: {FAILURE, HEAVISIDE, RELU, LOGISTIC}.
std::vector<double> Parameters::altering_activation = {0., 0., 0., 0.};

// P.M.F. for adding a `Node` by splitting a `Link` of a given role: {FAILURE, FORWARD, RECURRENT}.
std::vector<double> Parameters::adding_node = {0., 0., 0.};

// P.M.F. for assimilating each homologous `Link`: {FAILURE, SUCCESS}.
std::vector<double> Parameters::assimilating_links = {0., 0.};

// P.M.F. for assimilating each homologous `Node`: {FAILURE, SUCCESS}.
std::vector<double> Parameters::assimilating_nodes = {0., 0.};

// P.M.F. for assimilating a homologous `Link`'s weight: {FAILURE, SUCCESS}.
std::vector<double> Parameters::assimilating_weight = {0., 0.};

// P.M.F. for assimilating a homologous `Node`'s activation function: {FAILURE, SUCCESS}.
std::vector<double> Parameters::assimilating_activation = {0., 0.};

// P.M.F. for spawning a new `Organism` through a given process: {MUTATION, ASSIMILATION}.
std::vector<double> Parameters::spawning_organism = {0., 0.};


// Constructor:

// Default constructor responsible for initializing this `Parameters` instance.
Parameters::Parameters()
{
    // Constructs this `Parameters` instance.
}


// Destructor:

// Default destructor responsible for deleting this `Parameters` instance.
Parameters::~Parameters()
{
    // Deletes this `Parameters` instance.
}
