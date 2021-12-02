<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **Chromosome** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Link](link.md)**</sup>  
&nbsp;  

# Chromosome

 A `Chromosome` stores and manipulates a collection of `Element*`s.  
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
int size(const std::vector<int> roles, const std::vector<int> states)
```

Returns the number of stored `Element*`s with a matching `role` and `state`.  
&nbsp;


```C++
std::vector<Element*>::iterator begin(int locus)
```

Returns an iterator at the beginning of the input `locus`.  
&nbsp;


```C++
std::vector<Element*>::iterator end(int locus)
```

Returns an iterator at the end of the input `locus`.  
&nbsp;


```C++
Element* find(unsigned long int key)
```

Returns the `Element*` with the matching `key`. If no match is found, `nullptr` is returned instead.  
&nbsp;


```C++
Element* insert(Element* element)
```

Stores the input `Element*` in the `Chromosome`, and returns the stored `Element*`.  
&nbsp;


```C++
Element* remove(Element* element)
```

Removes an `Element*` from the `Chromosome`, and returns the removed `Element*`.  
&nbsp;


```C++
void toggle(Element* element, int state)
```

Toggles the `state` of an `Element*`.  
&nbsp;


```C++
Element* random(const std::vector<int> roles, const std::vector<int> states, const std::vector<double> weights)
```

Returns a random `Element*` with `role` and `state` matching one of the entries in the input `roles` and `states`, respectively. The `weights` argument sets the relative odds of each matching `Element*` being returned. When `weights` is empty, the same odds are assigned to all matching `Element*`s.  
&nbsp;


```C++
std::vector<Element*> retrieve(const std::vector<int> roles, const std::vector<int> states)
```

Returns all `Element*`s with `role` and `state` matching one of the entries in the input `roles` and `states`, respectively.  
&nbsp;


```C++
std::vector<Element*> sort(const std::vector<int> roles, const std::vector<int> states)
```

Sorts and returns all `Element*`s with `role` and `state` matching one of the entries in the input `roles` and `states`, respectively. The sorting criterium is provided by the `element_comparison` method.  
&nbsp;


```C++
static bool element_comparison(Element* element_, Element* element__)
```

Returns a `bool` value obtained from the `<`-comparison between the two input `Element*`s' `tag`s.  
&nbsp;
