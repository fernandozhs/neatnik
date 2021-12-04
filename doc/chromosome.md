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

Catalogs all `Element*`s by their `key`.  
&nbsp;


```C++
std::unordered_map<int, std::vector<Element*>> genes
```

Catalogs all `Element*`s by the their `locus`, i.e., the product of their `state` and `role`.  
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
int size(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1})
```

Returns the number of stored `Element*`s with `role` and `state` matching one of the entries in the input `roles_` and `states_`, respectively.  
&nbsp;


```C++
std::vector<Element*>::iterator begin(int locus_)
```

Returns an iterator at the beginning of the input `locus_`.  
&nbsp;


```C++
std::vector<Element*>::iterator end(int locus_)
```

Returns an iterator at the end of the input `locus_`.  
&nbsp;


```C++
Element* find(unsigned long int key_)
```

Returns the `Element*` with `key` matching the input `key_`. If no match is found, `nullptr` is returned instead.  
&nbsp;


```C++
Element* insert(Element* element_)
```

Stores the input `element_` in the `Chromosome`, and returns `element_`.  
&nbsp;


```C++
Element* remove(Element* element_)
```

Removes the input `element_` from the `Chromosome`, and returns `element_`.  
&nbsp;


```C++
void toggle(Element* element_, int state_)
```

Ensures the `Element` referenced by `element_` is toggled to the input `state_`.  
&nbsp;


```C++
Element* random(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1}, const std::vector<double> weights_ = {})
```

Returns a pointer to a random `Element` with `role` and `state` matching one of the entries in the input `roles_` and `states_`, respectively. The `weights_` argument sets the relative odds of each matching `Element*` being returned. When `weights_` is empty, the same odds are assigned to all matching `Element*`s.  
&nbsp;


```C++
std::vector<Element*> retrieve(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1})
```

Returns pointers to all `Element`s with `role` and `state` matching one of the entries in the input `roles_` and `states_`, respectively.  
&nbsp;


```C++
std::vector<Element*> sort(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1})
```

Sorts and returns pointers to all `Element*`s with `role` and `state` matching one of the entries in the input `roles_` and `states_`, respectively. The sorting criterium is provided by the `element_comparison` method.  
&nbsp;


```C++
static bool element_comparison(Element* first_element_, Element* second_element_)
```

Returns `true` if `first_element_` references an `Element` with a smaller `tag` than that of the `Element` referenced by `second_element_`. Returns `false` otherwise.  
&nbsp;
