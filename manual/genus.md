<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **Genus** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Genus

A `Genus` stores and manages a collection of `Species`.


## Properties

```C++
Experiment* experiment
```

Points to the `Experiment` to which the `Genus` belongs.  
&nbsp;


```C++
std::unordered_map<unsigned long int, unsigned int> logbook
```

Catalogs all `tag`s by the `key` property of the `Link` or `Node` they label.  
&nbsp;


```C++
unsigned int tag_counter
```

Counts the total number of catalogued `Link` and `Node` `tag`s.  
&nbsp;


```C++
std::unordered_map<int, Species*> species
```

Catalogs all `Species*`s by the `group` property of the `Species`s they reference.  
&nbsp;


```C++
std::vector<Organism*> organisms
```

Stores pointers to the `Genus`' next generation of `Organism`s.
&nbsp;


## Constructor

```C++
Genus(Experiment* experiment_, std::vector<Graph> graphs_);
```

Constructs a `Genus` by populating a single `DOMINANT` `Species` with `Organism`s generated from a set of minimal input `graphs_`. The `Genus` is associated to the referenced input `Experiment`.  
&nbsp;


## Destructor

```C++
~Genus()
```

Destructs the `Genus`, as well as all of its `Species`.  
&nbsp;


## Methods

```C++
std::pair<unsigned long int, unsigned int> tag(unsigned int role_, element_type type_, unsigned int source_tag_, unsigned int target_tag_)
```

Returns the `key` and `tag` associated with a `Link` or `Node` uniquely identified by the input arguments.  
&nbsp;


```C++
std::pair<unsigned long int, unsigned int> log(unsigned long int key_)
```

Creates a new `tag`, cataloguing it under the input `key_`.  
&nbsp;


```C++
unsigned int size(const std::vector<int> groups_ = {0, 1})
```

Returns the number of `Species*`s catalogued under the input `groups_`.  
&nbsp;


```C++
std::vector<Species*>::iterator begin(int group_)
```

Returns an iterator at the beginning of the input `group_`.  
&nbsp;


```C++
std::vector<Species*>::iterator end(int group_)
```

Returns an iterator at the end of the input `group_`.  
&nbsp;


```C++
Species* front(int group_)
```

Returns the first `Species*` catalogued under the input `group_`.  
&nbsp;


```C++
Species* back(int group_)
```

Returns the last `Orgainsm*` catalogued under the input `group_`.  
&nbsp;


```C++
Species* insert(Species* spcecies_)
```

Stores the input `species_` in the `Genus`, returning the stored `species_`.  
&nbsp;


```C++
Species* remove(Species* species_)
```

Removes the input `species_` from the `Genus`, returning the removed `species_`.  
&nbsp;


```C++
void purge(Species* species_)
```

Removes the input `Species*` from the `Genus`, subsequently deleting the referenced `Species`.  
&nbsp;


```C++
void purge(const std::vector<int> groups_ = {0, 1})
```

Removes every `Species*` catalogued under the input `groups_`, subsequently deleting each referenced `Species`.  
&nbsp;


```C++
void toggle(Species* species_, int group_)
```

Ensures the referenced input `Species` is toggled to the input `group_`.  
&nbsp;


```C++
Species* random(const std::vector<int> groups_ = {0, 1}, const std::vector<double> weights_ = {})
```

Returns a random `Species*` catalogued under one of the input `groups_`. The `weights_` argument sets the relative odds of each candidate `Species*` being returned. When `weights_` is empty, the same odds are assigned to all candidate `Species*`.  
&nbsp;


```C++
std::vector<Species*> retrieve(const std::vector<int> groups_ = {0, 1})
```

Returns all `Species*` catalogued under the input `groups_`.  
&nbsp;


```C++
std::vector<Species*> sort(const std::vector<int> groups_ = {0, 1})
```

Sorts and returns the `Species*` catalogued under the input `groups_`. The sorting criterium is provided by the `species_comparison` method.  
&nbsp;


```C++
void select()
```

Purges all stagnated `Species`. The criterium for stagnation is provided by the `species_rejection` method.  
&nbsp;


```C++
void spawn()
```

Spawns a new generation of `Organism`s.  
&nbsp;


```C++
void speciate()
```

Assigns the `Organism`s of a new generation to a new or existing `Species`.  
&nbsp;


```C++
bool species_rejection(Species* species_)
```

Returns `true` if the referenced input `CONTESTANT` `Species`' rank has been stagnated for several generational cycles. Returns `false` otherwise.  
&nbsp;


```C++
static bool organism_comparison(Species* first_species_, Species* second_species_)
```

Compares the `DOMINANT` `Organism`s of each referenced input `Species` through the `organism_comparison` method.  
&nbsp;
