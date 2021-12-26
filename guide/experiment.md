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
Parameters* parameters
```

The `Parameters*` which characterize this `Experiment`.  
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


```C++
std::vector<std::vector<double>> behaviors
```

Stores the novel behaviors displayed by the `Organism`s evolved in this `Experiment`.  
&nbsp;


``` C++
std::vector<Graph> outcome
```

Stores the `Graph`s of the fittest `Organism`s to evolve in this `Experiment`.  
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
void build()
```

Populates the `Experiment`'s `Genus` with `Organism`s initialized from the `Experiment`'s starting minimal `Graph`.  
&nbsp;


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
void drive(driver_metric metric_)
```

Drives the evolution of this `Experiment`'s `Genus`.  
&nbsp;


```C++
void assess(Organism* organism_, const std::vector<int> metrics_)
```

Scores and curates the referenced input `Organism` with respect to the given driver `metrics_`.  
&nbsp;


```C++
double novelty(Organism* organism_)
```

Evaluates the referenced input `Organism`'s `NOVELTY` score.  
&nbsp;


```C++
virtual double fitness(Organism* organism_) = 0
```

Evaluates the referenced input `Organism`'s `FITNESS` score.  
&nbsp;


```C++
virtual std::vector<double> behavior(Organism* organism_) = 0
```

Extracts the referenced input `Organism`'s behavior.  
&nbsp;
