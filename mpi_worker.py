import neatnik
import numpy as np
from mpi4py import MPI


# Initializes this worker's kill switch.
kill_switch = False

# The input `stimuli` and expected `response` of a XOR operator.
stimuli = [[[1, 0, 0], [1, 1, 0]], [[1, 0, 1]], [[1, 1, 1]]]
response = [[[0], [1]], [[1]], [[0]]]

# Retrieves this worker's rank and parent communicator.
comm = MPI.Comm.Get_parent()
rank = comm.Get_rank()

while True:
    # Checks the broadcasted kill switch instruction from the master process.
    if comm.bcast(kill_switch, root=0): break

    # The input `organism` and its partial score.
    organism = None
    partial_score = 0

    # Receives the broadcasted `organism` from the master process.
    organism = comm.bcast(organism, root=0)

    # Extracts the `organism`'s reaction and computes its partial score.
    reaction = np.array(organism.react(stimuli[rank]))
    target = np.array(response[rank])
    partial_score = len(stimuli[rank]) - np.abs(reaction - target).flatten().sum()

    # Sends the `organism`'s partial score to the master process for reduction.
    comm.reduce(partial_score, op=MPI.SUM, root=0)

# Disconnects MPI.
comm.Disconnect()
