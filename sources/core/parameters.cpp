#include "parameters.hpp"

unsigned int Parameters::random_seed = 0;

int Parameters::generational_cycles = 0;

int Parameters::population_size = 0;

int Parameters::mutation_attempts = 0;

int Parameters::spawning_attempts = 0;

double Parameters::weight_bound = 0.;

double Parameters::perturbation_power = 0.;

double Parameters::splitting_priority = 0.;

node_activation Parameters::initial_activation = IDENTITY;

double Parameters::rejection_fraction = 0.;

int Parameters::stagnation_threshold = 0;

double Parameters::compatibility_threshold = 0.;

std::vector<double> Parameters::compatibility_weights = {0., 0., 0.};

std::vector<double> Parameters::enabling_link = {0., 0.};

std::vector<double> Parameters::altering_links = {0., 0.};

std::vector<double> Parameters::altering_weight = {0., 0., 0.};

std::vector<double> Parameters::adding_link = {0., 0., 0., 0., 0.};

std::vector<double> Parameters::enabling_node = {0., 0., 0.};

std::vector<double> Parameters::altering_nodes = {0., 0.};

std::vector<double> Parameters::altering_activation = {0., 0., 0., 0.};

std::vector<double> Parameters::adding_node = {0., 0., 0.};

std::vector<double> Parameters::assimilating_links = {0., 0.};

std::vector<double> Parameters::assimilating_nodes = {0., 0.};

std::vector<double> Parameters::assimilating_weight = {0., 0.};

std::vector<double> Parameters::assimilating_activation = {0., 0.};

std::vector<double> Parameters::spawning_organism = {0., 0.};

bool Parameters::statistical_scoring = false;


// Constructor:

Parameters::Parameters()
{

}


// Destructor:

Parameters::~Parameters()
{

}
