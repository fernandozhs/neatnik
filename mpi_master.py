import sys
import neatnik
import parameters
from mpi4py import MPI


# MPI Experiment:
# --- ----------

# Defines an MPI-compatible `neatnik.Experiment`.
class MPI_Experiment(neatnik.Experiment):
    """ Drives the evolution of a `neatnik.Genus`. """

    # The global kill switch used to abort all worker processes.
    global kill_switch

    # Performance:
    def performance(self, organism : neatnik.Organism) -> float:
        """ Scores the performance of the input `neatnik.Organism`. """

        # Broadcasts the kill switch state to all worker processes.
        comm.bcast(kill_switch, root=MPI.ROOT)

        # Initializes the input `organism`'s score.
        score = 0.

        # Broadcasts the input `organism` to the worker processes.
        comm.bcast(organism, root=MPI.ROOT)

        # Sums the `organism`'s partial scores computed by each worker process.
        score = comm.reduce(None, op=MPI.SUM, root=MPI.ROOT)

        # Returns the `organism`'s score.
        return score


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
experiment = MPI_Experiment(genus)

# Spawns three worker processes and initializes their kill switch in a disengaged state.
comm = MPI.COMM_SELF.Spawn(sys.executable, args=["mpi_worker.py"], maxprocs=3)
kill_switch = False

# Runs the `experiment`.
experiment.evolve()

# Engages the worker processes' kill switch.
kill_switch = True
comm.bcast(kill_switch, root=MPI.ROOT)

# Finalizes MPI.
comm.Disconnect()
MPI.Finalize()
