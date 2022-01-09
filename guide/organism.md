<sub>**[Utilities](utilities.md)**</sub>  
<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **Organism** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Organism

An `Organism` corresponds to an individual agent whose behavior is encoded by its `Genotype`, and expressed by its `Phenotype`.  
&nbsp;


## Properties

```C++
Species* species
```

Points to the `Species` to which the `Organism` belongs.  
&nbsp;


```C++
taxon_group group
```

Specifies whether the `Organism` belongs to the `DOMINANT` or `CONTESTANT` group within its `Species`.  
&nbsp;


```C++
Genotype* genotype
```

Points to the `Organism`'s `Genotype`.  
&nbsp;


```C++
Phenotype* phenotype
```

Points to the `Organism`'s `Phenotype`.  
&nbsp;


```C++
unsigned int age
```

The `Organism`'s age measured in generational cycles.  
&nbsp;


```C++
std::vector<double> scores
```

The `Organism`'s scores. While the first entry stores the `Organism`'s `NOVELTY` score, the second element stores its `FITNESS` score.  
&nbsp;


```C++
std::vector<double> behavior
```

The `Organism`'s behavior from which its `NOVELTY` score is derived.  
&nbsp;


## Constructors

```C++
Organism(Species* species_, Graph graph_)
```

Constructs an `Organism` from a minimal input `graph_`, associating it to the referenced input `Species`.  
&nbsp;


```C++
Organism(Organism* organism_)
```

Constructs a deep copy of the referenced input `Organism`, associating it to the same `Species`.  
&nbsp;


```C++
Organism(Graph graph_)
```

Constructs a replica of an `Organism` whose `Genotype` is encoded by the input `graph_`.  
&nbsp;


## Destructor

```C++
~Organism()
```

Destructs the `Organism`, as well as its `Genotype` and `Phenotype`.  
&nbsp;


## Methods

```C++
Organism* mutate()
```

Produces an offspring `Organism` through `MUTATION`.  
&nbsp;


```C++
Organism* assimilate(Organism* organism_)
```

Produces an offspring `Organism` through `ASSIMILATION`.  
&nbsp;


```C++
std::vector<std::vector<std::vector<double>>> react()
```

Prompts the `Organism` to react to its `Experiment`'s `stimuli`.  
&nbsp;


```C++
std::vector<std::vector<std::vector<double>>> react(std::vector<std::vector<std::vector<double>>> stimuli_)
```

Prompts the `Organism` to react to the input `stimuli_`.  
&nbsp;


```C++
Graph graph() const
```

Generates a `Graph` encapsulating the `Organism`'s `Genotype` properties.  
&nbsp;
