import neatnik


# General Parameters:
# ------- ----------

# Number of generational cycles for which an `Experiment` will run.
neatnik.generational_cycles = 300

# Number of `Organism`s in an `Experiment`'s `Genus`.
neatnik.population_size = 100

# Number of attempts at mutating a `Genotype`.
neatnik.mutation_attempts = 10

# Number of attempts at producing an offspring `Organism`.
neatnik.spawning_attempts = 10

# Bounding value for the generation and replacement of `Link` weights.
neatnik.weight_bound = 2.0

# Perturbation power when altering `Link` weights.
neatnik.perturbation_power = 2.0

# Relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
neatnik.compatibility_weights = [0.5, 1., 1.]

# Fraction of rejected `Organism`s at a given evolution cycle.
neatnik.rejection_fraction = 0.3

# Number of evolution cycles beyond which a stagnated `Species` can be discarded.
neatnik.stagnation_threshold = 15

# The degree of similarity beyond which `Organism`s group in separate `Species`.
neatnik.compatibility_threshold = 3.0


# Probability Mass Functions:
# ----------- ---- ---------

# P.M.F. for enabling of a random DISABLED `Link`: [FAILURE, SUCCESS].
neatnik.enabling_link = [0.5, 0.5]

# P.M.F. for altering each ENABLED `Link`: [FAILURE, SUCCESS].
neatnik.altering_links = [0.5, 0.5]

# P.M.F. for altering a `Link`'s weight: [FAILURE, PERTURB, REPLACE].
neatnik.altering_weight = [0.2, 0.7, 0.1]

# P.M.F. for adding a `Link` of a given role: [FAILURE, FORWARD, RECURRENT, BIASING, LOOPED].
neatnik.adding_link = [0.5, 0.25, 0., 0.25, 0.]

# P.M.F. for enabling a DISABLED INPUT `Node`: [FAILURE, SUCCESS].
neatnik.enabling_node = [1., 0.]

# P.M.F. for altering each HIDDEN `Node`: [FAILURE, SUCCESS].
neatnik.altering_nodes = [1., 0.];

# P.M.F. for altering a `Node`'s activation: [FAILURE, HEAVISIDE, RELU, LOGISTIC].
neatnik.altering_activation = [1., 0., 0., 0.]

# P.M.F. for adding a `Node` by splitting a `Link` of a given role: [FAILURE, FORWARD, RECURRENT].
neatnik.adding_node = [0.98, 0.02, 0.]

# P.M.F. for assimilating each homologous `Link`: [FAILURE, SUCCESS].
neatnik.assimilating_links = [0., 1.]

# P.M.F. for assimilating each homologous `Node`: [FAILURE, SUCCESS].
neatnik.assimilating_nodes = [1., 0.]

# P.M.F. for assimilating a homologous `Link`'s weight: [FAILURE, SUCCESS].
neatnik.assimilating_weight = [0.5, 0.5]

# P.M.F. for assimilating a homologous `Node`'s activation function: [FAILURE, SUCCESS].
neatnik.assimilating_function = [1., 0.]

# P.M.F. for spawning a new `Organism` through a given process: [MUTATION, ASSIMILATION].
neatnik.spawning_organism = [0.4, 0.6]
