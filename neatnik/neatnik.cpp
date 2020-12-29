#include "../utils/utils.h"
#include "../elements/elements.h"
#include "../genotype/chromosome.h"
#include "../genotype/genotype.h"
#include "../phenotype/phenotype.h"
#include "../organism/organism.h"
#include "../genus/species.h"
#include "../experiment/experiment.h"
#include "../genus/genus.h"

/*
  General Parameters:
  ------- ----------
*/

// Number of generational cycles for which an `Experiment` will run.
int generational_cycles = 300;

// Number of `Organism`s in an `Experiment`'s `Genus`.
int population_size = 100;

// Number of attempts at mutating a `Genotype`.
int mutation_attempts = 10;

// Number of attempts at producing an offspring `Organism`.
int spawning_attempts = 10;

// Bounding value for `Link` weights.
double weight_bound = 2.0;

// Perturbation power when altering `Link` weights.
double perturbation_power = 2.0;

// Relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
std::vector<double> compatibility_weights = {0.5, 1., 1.};

// Fraction of rejected `Organism`s at a given evolution cycle.
double rejection_fraction = 0.3;

// Number of evolution cycles beyond which a stagnated `Species` can be discarded.
int stagnation_threshold = 15;

// The degree of similarity beyond which `Organism`s group in separate `Species`.
double compatibility_threshold = 3.0;


/*
  Probability Mass Functions:
  ----------- ---- ---------
*/

// P.M.F. for enabling of a random DISABLED `Link`: {FAILURE, SUCCESS}.
std::vector<double> enabling_link = {0.5, 0.5};

// P.M.F. for altering each ENABLED `Link`: {FAILURE, SUCCESS}.
std::vector<double> altering_links = {0.5, 0.5};

// P.M.F. for altering a `Link`'s weight: {FAILURE, PERTURB, REPLACE}.
std::vector<double> altering_weight = {0.2, 0.7, 0.1};

// P.M.F. for adding a `Link` of a given role: {FAILURE, FORWARD, RECURRENT, BIASING, LOOPED}.
std::vector<double> adding_link = {0.5, 0.25, 0., 0.25, 0.};

// P.M.F. for enabling a DISABLED INPUT `Node`: {FAILURE, SUCCESS}.
std::vector<double> enabling_node = {1., 0.};

// P.M.F. for altering each HIDDEN `Node`: {FAILURE, SUCCESS}.
std::vector<double> altering_nodes = {1., 0.};

// P.M.F. for altering a `Node`'s activation: {FAILURE, HEAVISIDE, RELU, LOGISTIC}.
std::vector<double> altering_activation = {1., 0., 0., 0.};

// P.M.F. for adding a `Node` by splitting a `Link` of a given role: {FAILURE, FORWARD, RECURRENT}.
std::vector<double> adding_node = {0.98, 0.02, 0.};

// P.M.F. for assimilating each homologous `Link`: {FAILURE, SUCCESS}.
std::vector<double> assimilating_links = {0., 1.};

// P.M.F. for assimilating each homologous `Node`: {FAILURE, SUCCESS}.
std::vector<double> assimilating_nodes = {1., 0.};

// P.M.F. for assimilating a homologous `Link`'s weight: {FAILURE, SUCCESS}.
std::vector<double> assimilating_weight = {0.5, 0.5};

// P.M.F. for assimilating a homologous `Node`'s activation function: {FAILURE, SUCCESS}.
std::vector<double> assimilating_function = {1., 0.};;

// P.M.F. for spawning a new `Organism` through a given process: {MUTATION, ASSIMILATION}.
std::vector<double> spawning_organism = {0.4, 0.6};


/*
  Main:
  ----
*/

int main()
{
    return 0;
}
