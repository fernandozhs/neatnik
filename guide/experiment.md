<sub>**[Utilities](utilities.md)**</sub>  
<sub>**[Parameters](parameters.md)**</sub>  
<sub>**Experiment** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Experiment

An `Experiment` drives the evolution of a `Genus`.  
&nbsp;


## Properties

```C++
int MPI_rank
```

This `Experiment`'s MPI rank returned by `MPI_Comm_size`.  
&nbsp;


```C++
int MPI_size
```

The total number of MPI processes returned by `MPI_Comm_rank`.  
&nbsp;


```C++
std::vector<int> MPI_counts
std::vector<int> MPI_displacements
```

The counts and displacements required by `MPI_Allgatherv`.  
&nbsp;


```C++
std::vector<Vertex> vertexes
```

Stores the `Vertex`es which define this `Experiment`'s starting minimal `Graph`.  
&nbsp;


```C++
std::vector<Edge> edges
```

Stores the `Edge`s which define this `Experiment`'s starting minimal `Graph`.  
&nbsp;


```C++
static std::vector<std::vector<std::vector<double>>> stimuli
```

Contains the stimuli presented to the `Organism`s throughout the evolutionary process.  
&nbsp;


```C++
Genus* genus
```

Points to the `Genus` to be evolved by this `Experiment`.  
&nbsp;


## Constructor

```C++
Experiment()
```

Constructs an empty `Experiment`.  
&nbsp;


## Destructor

```C++
~Experiment()
```

Destructs the `Experiment`, as well as its `Genus`.  
&nbsp;


## Methods

```C++
void run()
```

Runs this `Experiment`.  
&nbsp;


```C++
virtual void display()
```

Displays any of this `Experiment`'s properties.  
&nbsp;


```C++
void score()
```

Uses MPI to score all `Organism`s in parallel.  
&nbsp;


```C++
virtual double fitness(Organism* organism_) = 0
```

Evaluates the referenced input `Organism`'s fitness score.  
&nbsp;
