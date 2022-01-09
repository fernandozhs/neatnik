<sub>**[Utilities](utilities.md)**</sub>  
<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **Species** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Species

A `Species` stores and manages a collection of compatible `Organism`s.  
&nbsp;


## Properties

```C++
Genus* genus
```

Points to the `Genus` to which the `Species` belongs.  
&nbsp;


```C++
taxon_group group
```

Specifies whether the `Species` belongs to the `DOMINANT` or `CONTESTANT` group within its `Genus`.  
&nbsp;


```C++
std::unordered_map<int, std::vector<Organism*>> organisms
```

Catalogs all `Organism*`s by the `group` property of the `Organism`s they reference.  
&nbsp;


```C++
double rank
```

The `Species`'s rank.  
&nbsp;


## Constructors

```C++
Species(Genus* genus_, taxon_group group_, std::vector<Graph> graphs_)
```

Constructs a `Species` by populating it with `Organism`s generated from a set of minimal input `graphs_`. The `Species` is assigned to the input `group_` and associated to the referenced input `Genus`.  
&nbsp;


```C++
Species(Genus* genus_, taxon_group group_, Organism* organism_)
```

Constructs a `Species` from a single representative `Organism`. The `Species` is assigned to the input `group_` and associated to the referenced input `Genus`.  
&nbsp;


## Destructor

```C++
~Species()
```

Destructs the `Species`, as well as all of its `Organism`s.  
&nbsp;


## Methods

```C++
unsigned int size(const std::vector<int> groups_ = {0, 1})
```

Returns the number of `Organism*`s catalogued under the input `groups_`.  
&nbsp;


```C++
std::vector<Organism*>::iterator begin(int group_)
```

Returns an iterator at the beginning of the input `group_`.  
&nbsp;


```C++
std::vector<Organism*>::iterator end(int group_)
```

Returns an iterator at the end of the input `group_`.  
&nbsp;


```C++
Organism* front(int group_)
```

Returns the first `Orgainsm*` catalogued under the input `group_`.  
&nbsp;


```C++
Organism* back(int group_)
```

Returns the last `Orgainsm*` catalogued under the input `group_`.  
&nbsp;


```C++
Organism* insert(Organism* organism_)
```

Stores the input `organism_` in the `Species`, returning the stored `organism_`.  
&nbsp;


```C++
Organism* remove(Organism* organism_)
```

Removes the input `organism_` from the `Species`, returning the removed `organism_`.  
&nbsp;


```C++
void purge(Organism* organism_)
```

Removes the input `Organism*` from the `Species`, subsequently deleting the referenced `Organism`.  
&nbsp;


```C++
void purge(const std::vector<int> groups_ = {0, 1})
```

Removes every `Organism*` catalogued under the input `groups_`, subsequently deleting each referenced `Organism`.  
&nbsp;


```C++
void toggle(Organism* organism_, int group_)
```

Ensures the referenced input `Organism` is toggled to the input `group_`.  
&nbsp;


```C++
Organism* random(const std::vector<int> groups_ = {0, 1}, const std::vector<double> weights_ = {})
```

Returns a random `Organism*` catalogued under one of the input `groups_`. The `weights_` argument sets the relative odds of each candidate `Organism*` being returned. When `weights_` is empty, the same odds are assigned to all candidate `Organism*`s.  
&nbsp;


```C++
std::vector<Organism*> retrieve(const std::vector<int> groups_ = {0, 1})
```

Returns all `Organism*`s catalogued under the input `groups_`.  
&nbsp;


```C++
std::vector<Organism*> sort(const std::vector<int> groups_ = {0, 1})
```

Sorts and returns the `Organism*`s catalogued under the input `groups_`. The sorting criterium is provided by the `organism_comparison` method.  
&nbsp;


```C++
void select()
```

Purges a fraction of the `CONTESTANT` `Organism`s belonging to the `Species`.  
&nbsp;


```C++
Organism* spawn()
```

Attempts to spawn an offspring `Organism` through either `MUTATION` or `ASSIMILATION`.  
&nbsp;


```C++
bool organism_compatibility(Organism* organism_)
```

Returns `true` if the referenced input `Organism`'s `Genotype` is compatible with the `Genotype` of the `Species`' `DOMINANT` `Organism`. Returns `false` otherwise.  
&nbsp;


```C++
static bool organism_comparison(Organism* first_organism_, Organism* second_organism_)
```

If the referenced input `Organism`s possess the same `score`: returns `true` if `first_organism_` references an `Organism` with a smaller `Genotype` than that of the `Organism` referenced by `second_organism_`; returns `false` otherwise.  
If the referened input `Organism`s do not possess the same `score`: returns `true` if `first_organism_` references an `Organism` with a smaller `score` than that of the `Organism` referenced by `second_organism_`; returns `false` otherwise.  
&nbsp;
