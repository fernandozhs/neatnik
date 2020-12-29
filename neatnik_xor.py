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


# XOR Experiment:
# --- ----------

# Defines the XOR `neatnik.Experiment`.
class XOR(neatnik.Experiment):
    """ Drives the evolution of an 'exclusive or' operator within a `neatnik.Genus`. """

    # This experiment's target behavior.
    targets = [0, 1, 1, 0]

    # Performance:
    def performance(self, organism : neatnik.Organism) -> float:
        """ Scores the performance of the input `neatnik.Organism`. """

        # Extracts the input organism's reaction to a set of stimuli.
        reactions = organism.react([[1, 0, 0], [1, 1, 0], [1, 0, 1], [1, 1, 1]])

        # Computes the organism's reaction residuals with respect to the experiment's target behavior.
        residuals = [abs(sum(r) - t) for r, t in zip(reactions, self.targets)]

        # Returns the organism's score.
        return 4 - sum(residuals)


# NEATnik:
# -------

# Defines the `vertices` of the base minimal `graph`: 1 bias vertex, 2 input vertices, and 1 output vertex.
vertices = [(0, None, neatnik.ENABLED, neatnik.BIAS, neatnik.IDENTITY, 0, 2),
            (1, None, neatnik.ENABLED, neatnik.INPUT, neatnik.IDENTITY, 0, 1),
            (2, None, neatnik.ENABLED, neatnik.INPUT, neatnik.IDENTITY, 0, 0),
            (3, None, neatnik.ENABLED, neatnik.OUTPUT, neatnik.LOGISTIC, 1, 1)]

# Defines the `edges` of the base minimal `graph`: 1 biasing edge, and 2 forward edges.
edges = [(None, None, neatnik.ENABLED, neatnik.BIASING, 0, 3, None),
         (None, None, neatnik.ENABLED, neatnik.FORWARD, 1, 3, None),
         (None, None, neatnik.ENABLED, neatnik.FORWARD, 2, 3, None)]

# Defines the base minimal `graph`.
graph = (vertices, edges)

# Initializes the `neatnik.Genus` and the `neatnik.Experiment`.
genus = neatnik.Genus(neatnik.population_size*[graph])
experiment = XOR(genus)

# Evolves the `experiment`.
experiment.evolve()
