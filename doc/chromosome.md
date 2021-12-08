<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **Chromosome** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Chromosome

 A `Chromosome<Element>` stores and manipulates a collection of `Element*`s, e.g., collections of `Node*`s or `Link*`s.  
 &nbsp;


## Properties

```C++
std::unordered_map<unsigned long int, Element*> logbook
```

Catalogs each `Element*` according to the `key` property of the `Element` it references.  
&nbsp;


```C++
std::unordered_map<int, std::vector<Element*>> genes
```

Catalogs each `Element*` according to the product of the `state` and `role` properties of the `Element` it references.  
&nbsp;


## Constructor

```C++
Chromosome()
```

Constructs an empty `Chromosome`.  
&nbsp;


## Destructor

```C++
~Chromosome()
```

Deletes the `Chromosome` and all the `Element*`s it currently stores.  
&nbsp;


## Methods

```C++
unsigned int size(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1})
```

Returns the number of `Element*`s catalogued under combinations of the input `roles_` and `states_`.  
&nbsp;


```C++
std::vector<Element*>::iterator begin(int locus_)
```

Returns an iterator at the beginning of the input `locus_`, i.e., the product of a given `role` and `state`.  
&nbsp;


```C++
std::vector<Element*>::iterator end(int locus_)
```

Returns an iterator at the end of the input `locus_`, i.e., the product of a given `role` and `state`.  
&nbsp;


```C++
Element* find(unsigned long int key_)
```

Returns the `Element*` catalogued under the matching input `key_`. If no match is found, `nullptr` is returned instead.  
&nbsp;


```C++
Element* insert(Element* element_)
```

Stores the input `element_` in the `Chromosome`, returning the stored `element_`.  
&nbsp;


```C++
Element* remove(Element* element_)
```

Removes the input `element_` from the `Chromosome`, returning the removed `element_`.  
&nbsp;


```C++
void toggle(Element* element_, int state_)
```

Ensures the referenced input `Element` is toggled to the input `state_`.  
&nbsp;


```C++
Element* random(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1}, const std::vector<double> weights_ = {})
```

Returns a random `Element*` catalogued under one of the input `roles_` and `states_`. The `weights_` argument sets the relative odds of each candidate `Element*` being returned. When `weights_` is empty, the same odds are assigned to all candidate `Element*`s.  
&nbsp;


```C++
std::vector<Element*> retrieve(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1})
```

Returns the `Element*`s catalogued under all combinations of the input `roles_` and `states_`.  
&nbsp;


```C++
std::vector<Element*> sort(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1})
```

Sorts and returns the `Element*`s catalogued under all combinations of the input `roles_` and `states_`. The sorting criterium is provided by the `element_comparison` method.  
&nbsp;


```C++
std::vector<double> weights(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1}, const double weight_ = 1.)
```

Returns a weight associated with each `Element*` catalogued under combinations of the input `roles_` and `states_`. The assigned weights are multiples of the input `weight_`, where the multiplying factors are given by the `Element*`s' ordering once sorted according to the `element_comparison` criterium.  
&nbsp;


```C++
static bool element_comparison(Element* first_element_, Element* second_element_)
```

Returns `true` if `first_element_` references an `Element` with a smaller `tag` than that of the `Element` referenced by `second_element_`. Returns `false` otherwise.  
&nbsp;
