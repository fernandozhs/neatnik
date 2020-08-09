#include <iostream>
#include "../neatnik/neatnik.h"
#include "../utils/utils.h"
#include "../elements/elements.h"
#include "../innovation/innovation.h"
#include "../genotype/chromosome.h"
#include "../genotype/genotype.h"
#include "../phenotype/phenotype.h"
#include "../organism/organism.h"
#include "../population/population.h"


/*
  Parameters:
  ----------
*/

// Number of attempts at mutating a `Genotype`.
int attempts = 10;

// Bounding value for `Link` weights.
double bound = 8;

// Perturbation power when altering `Link` weights.
double power = 1;


/*
  Probability Mass Functions:
  ----------- ---- ---------
*/

// P.M.F. for enabling of a random DISABLED `Link`: {FAILURE, SUCCESS}.
std::vector<double> enabling_link = {0, 0};

// P.M.F. for altering each ENABLED `Link`: {FAILURE, SUCCESS}.
std::vector<double> altering_links = {0, 0};

// P.M.F. for altering a `Link`'s weight: {FAILURE, PERTURB, REPLACE}.
std::vector<double> altering_weight = {0, 0, 0};

// P.M.F. for adding a `Link` of a given role: {FAILURE, FORWARD, BIASING, RECURRENT, LOOPED}.
std::vector<double> adding_link = {0, 0, 0, 0, 0};

// P.M.F. for enabling a DISABLED INPUT `Node`: {FAILURE, SUCCESS}.
std::vector<double> enabling_node = {0, 0};

// P.M.F. for altering each HIDDEN `Node`: {FAILURE, SUCCESS}.
std::vector<double> altering_nodes = {0, 0};

// P.M.F. for altering a `Node`'s activation function: {FAILURE, HEAVISIDE, RELU, LOGISTIC}.
std::vector<double> altering_function = {0, 0, 0, 0};

// P.M.F. for adding a `Node` by splitting a `Link` of given role: {FAILURE, FORWARD, RECURRENT}.
std::vector<double> adding_node = {0, 0, 0};

// P.M.F. for assimilating a `Link` or `Node` during crossover: {FAILURE, SUCCESS}
std::vector<double> assimilating_element = {0, 0};


/*
  Main:
  ----
*/

int main()
{
    std::cout << "Test successful." << std::endl;

    return 0;
}
