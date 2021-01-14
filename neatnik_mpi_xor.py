import neatnik
import numpy as np
from mpi4py import MPI


# Initializes MPI.
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

# Defines the `XOR` `neatnik.Experiment`.
class XOR(neatnik.Experiment):
    """ Drives the evolution of an 'exclusive or' operator. """

    # Makes `XOR` MPI-aware.
    global rank
    global size

    # Constructor:
    def __init__(self) -> None:
        """ Initializes this `XOR` `neatnik.Experiment`. """

        # Initializes the base `neatnik.Experiment`.
        neatnik.Experiment.__init__(self)

        # Sets the `XOR` `neatnik.Parameters`.
        self.parameters.generational_cycles = 100
        self.parameters.population_size = 100
        self.parameters.mutation_attempts = 10
        self.parameters.spawning_attempts = 10
        self.parameters.weight_bound = 2.0
        self.parameters.perturbation_power = 2.0
        self.parameters.rejection_fraction = 0.3
        self.parameters.stagnation_threshold = 15
        self.parameters.compatibility_threshold = 3.0
        self.parameters.compatibility_weights = [0.5, 1., 1.]
        self.parameters.enabling_link = [0.5, 0.5]
        self.parameters.altering_links = [0.5, 0.5]
        self.parameters.altering_weight = [0.2, 0.7, 0.1]
        self.parameters.adding_link = [0.5, 0.25, 0., 0.25, 0.]
        self.parameters.enabling_node = [0.2, 0.4, 0.4]
        self.parameters.altering_nodes = [1., 0.]
        self.parameters.altering_activation = [1., 0., 0., 0.]
        self.parameters.adding_node = [0.98, 0.02, 0.]
        self.parameters.assimilating_links = [0., 1.]
        self.parameters.assimilating_nodes = [1., 0.]
        self.parameters.assimilating_weight = [0.5, 0.5]
        self.parameters.assimilating_activation = [1., 0.]
        self.parameters.spawning_organism = [0.4, 0.6]

        # Sets the base network graph associated with the first generation of `XOR` `neatnik.Organism`s.
        self.vertexes = [
            (0,  None, neatnik.ENABLED, neatnik.BIAS,   neatnik.IDENTITY, 0, 2),
            (1,  None, neatnik.ENABLED, neatnik.INPUT,  neatnik.IDENTITY, 0, 1),
            (2,  None, neatnik.ENABLED, neatnik.INPUT,  neatnik.IDENTITY, 0, 0),
            (3,  None, neatnik.ENABLED, neatnik.OUTPUT, neatnik.LOGISTIC, 1, 1),
            ]
        self.edges = [
            (None, None, neatnik.ENABLED, neatnik.BIASING, 0, 3, None),
            (None, None, neatnik.ENABLED, neatnik.FORWARD, 1, 3, None),
            (None, None, neatnik.ENABLED, neatnik.FORWARD, 2, 3, None),
            ]

    # Performance:
    def performance(self, organism : neatnik.Organism) -> float:
        """ Scores the performance of the input `neatnik.Organism`. """

        # Master process:
        if rank == 0:
            # Broadcasts the input `organism` to the worker processes.
            comm.bcast(kill, root=0)
            comm.bcast(organism, root=0)

        # The input `stimuli` and expected `response` of an 'exclusive or' operator.
        stimuli = np.array([[1, 0, 0], [1, 1, 0], [1, 0, 1], [1, 1, 1]])[rank::size]
        response = np.array([[0], [1], [1], [0]])[rank::size]

        # Extracts the input `organism`'s reactions to the above stimuli.
        reactions = organism.react(stimuli)

        # Computes the `organism`'s partial score by comparing its `reactions` to the expected `response`.
        score = np.shape(stimuli)[0] - np.abs(reactions - response).flatten().sum()

        # Sums the input `organism`'s scores obtained by each process.
        score = comm.reduce(score, op=MPI.SUM, root=0)

        # Returns the `organism`'s score.
        return score


# Initializes a all relevant objects.
experiment = XOR()
organism = None
kill = False

# Master process:
if rank == 0:
    # Populates and runs the `XOR` `neatnik.Experiment`.
    experiment.populate()
    experiment.run()

    # Kills all worker processes.
    kill = True
    comm.bcast(kill, root=0)

# Worker processes:
else:
    # Work until told not to.
    while not(comm.bcast(kill, root=0)):
        # Scores the broadcasted `organism`.
        organism = comm.bcast(organism, root=0)
        experiment.performance(organism)

# Finalizes MPI.
MPI.Finalize()
