<sub>**[Utilities](utilities.md)**</sub>  
<sub>**Parameters**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>

# Parameters

Encapsulates the parameters which dictate `NEATNik`'s functioning.

## Properties

```C++
static unsigned int random_seed
```

A random non-negative integer used to seed `NEATnik`'s pseudo-random number generator.  
&nbsp;


```C++
static int generational_cycles
```

Sets the number of generational cycles for which an `Experiment` will run.  
&nbsp;


```C++
static int population_size
```

Sets the number of `Organism`s to be stored in an `Experiment`'s `Genus`.  
&nbsp;


```C++
static int mutation_attempts
```

Specifies the maximum number of times a `Genotype` should try to mutate itself when unsuccesfull in its previous attempts.  
&nbsp;


```C++
static int spawning_attempts
```

Specifies the maximum number of times a `Species` should try to produce an offspring `Organism` when unsuccesfull in its previous attempts.  
&nbsp;


```C++
static double weight_bound
```

Sets a bound on the value of `Link` weights. In the case of weight `REPLACEMENT` this corresponds to a hard bound, while in the case of weight `PERTURBATION` this corresponds to a soft bound.  
&nbsp;


```C++
static double perturbation_power
```

Sets the standard deviation of `Link` weight `PERTURBATION`s.  
&nbsp;


```C++
static double splitting_priority
```

The base value used to assign `Link`s a relative odd of being split during the creation of a new `Node`.  
&nbsp;


```C++
static node_activation initial_activation
```

Specifies which activation function a new `HIDDEN` `Node` is initially equipped with.  
&nbsp;


```C++
static double rejection_fraction
```

Sets the fraction of `Organism`s to be rejected at each generational cycle.  
&nbsp;


```C++
static int stagnation_threshold
```

Sets the number of generational cycles beyond which a `Species` with stagnated `rank` is discarded.  
&nbsp;


```C++
static double compatibility_threshold
```

Specifies the degree of similarity beyond which `Organism`s are separated into different `Species`.  
&nbsp;


```C++
static std::vector<double> compatibility_weights
```

The relative relevance assigned to matching, disjoint, and excess `Link`s when comparing two `Genotype`s.  
&nbsp;


```C++
static std::vector<double> enabling_link
```

The probability mass function for toggling `ENABLED` a random `DISABLED` `Link`. The first element encodes the proability of failure, while the second element encodes the probability of success.  
&nbsp;


```C++
static std::vector<double> altering_links
```

The probability mass function for altering the properties of a `Link`. The first element encodes the proability of failure, while the second element encodes the probability of success.  
&nbsp;


```C++
static std::vector<double> altering_weight
```

The probability mass function for altering a `Link`'s weight. The first element encodes the proability of failure, while the second and third elements encode the probabilities of altering the `Link`'s weight through `PERTURBATION` or `MUTATION`, respectively.  
&nbsp;


```C++
static std::vector<double> adding_link
```

The probability mass function for adding a new `Link` to a `Genotype`. The first element encodes the proability of failure, while the subsequent elements encode the probabilities of adding a `FORWARD`, `RECURRENT`, `BIASING`, or `LOOPED` `Link`, respectively.  
&nbsp;


```C++
static std::vector<double> enabling_node
```

The probability mass function for toggling `ENABLED` a random `DISABLED` `INPUT` `Node`. The first element encodes the proability of failure. The second term encodes the probability of success while connecting the `INPUT` `Node` to a `HIDDEN` `Node`. The third term encodes the probability of success while connecting the `INPUT` `Node` to an `OUTPUT` `Node`.  
&nbsp;


```C++
static std::vector<double> altering_nodes
```

The probability mass function for altering the properties of a `HIDDEN` `Node`. The first element encodes the proability of failure, while the second element encodes the probability of success.  
&nbsp;


```C++
static std::vector<double> altering_activation
```

The probability mass function for altering a `HIDDEN` `Node`'s activation. The first element encodes the proability of failure, while the subsequent elements encode the probabilities of equipping the `Node` with the `HEAVISIDE`, `RELU`, or `LOGISTIC` activation functions, respectively.  
&nbsp;


```C++
static std::vector<double> adding_node
```

The probability mass function for adding a new `HIDDEN` `Node` to a `Genotype` by splitting an existing `Link`. The first element encodes the proability of failure, while the second and third elements encode the probabilities of adding the new `HIDDEN` `Node` through the split of a `FORWARD` or `RECURRENT` `Link`, respectively.  
&nbsp;


```C++
static std::vector<double> assimilating_links
```

The probability mass function for attempting to assimilate the homologous `Link`s from another `Genotype`. The first element encodes the proability of failure, while the second element encodes the probability of success.  
&nbsp;


```C++
static std::vector<double> assimilating_nodes
```

The probability mass function for attempting to assimilate the homologous `Node`s from another `Genotype`. The first element encodes the proability of failure, while the second element encodes the probability of success.  
&nbsp;


```C++
static std::vector<double> assimilating_links
```

The probability mass function for assimilating a homologous `Link`'s weight from another `Genotype`. The first element encodes the proability of failure, while the second element encodes the probability of success.  
&nbsp;


```C++
static std::vector<double> assimilating_nodes
```

The probability mass function for assimilating each homologous `Node`'s activation from another `Genotype`. The first element encodes the proability of failure, while the second element encodes the probability of success.  
&nbsp;


```C++
static std::vector<double> spawning_organism
```

The probability mass function for a `Species` to spawn an offspring `Organism`. The first element encodes the proability of failure, while the second and third elements encode the probability of an offspring `Organism` being spawned through `MUTATION` or `ASSIMILATION`, respectively.  
&nbsp;


## Constructor

```C++
Parameters()
```

Constructs a default `Parameters` instance with essentially all parameters set to zero.  
&nbsp;


## Destructor

```C++
~Parameters()
```

Deletes the `Parameters` instance.  
&nbsp;
