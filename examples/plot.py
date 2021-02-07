import neatnik
import pickle
import numpy as np
import matplotlib.pyplot as plt


# Loads the an `Organism`'s `Graph`.
graph = pickle.load(open("organism.p", "rb"))

# Plots the Neural Network encoded by the loaded `Graph`.
for edge in graph[1]:
    x_values = [0., 0.]
    y_values = [0., 0.]

    source = edge[4]
    target = edge[5]

    for vertex in graph[0]:
        if vertex[0] == source:
            x_values[0] = vertex[5]
            y_values[0] = vertex[6]
        if vertex[0] == target:
            x_values[1] = vertex[5]
            y_values[1] = vertex[6]

    plt.plot(x_values, y_values, color="black", linewidth=1, alpha=0.2, zorder=0)


for vertex in graph[0]:
    if vertex[3] == neatnik.BIAS:
        plt.scatter(vertex[5], vertex[6], s=60., linewidths=0.5, c="#61D836", edgecolors="black", zorder=1)
    if vertex[3] == neatnik.INPUT:
        plt.scatter(vertex[5], vertex[6], s=60., linewidths=0.5, c="#00A2FF", edgecolors="black", zorder=1)
    #if vertex[3] == neatnik.HIDDEN:
        #plt.scatter(vertex[5], vertex[6], s=60., linewidths=0.5, c="#FF88FF", edgecolors="black", zorder=1)
    if vertex[3] == neatnik.OUTPUT:
        plt.scatter(vertex[5], vertex[6], s=60., linewidths=0.5, c="#FF9300", edgecolors="black", zorder=1)

plt.show()
