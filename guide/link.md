<sub>**[Utilities](utilities.md)**</sub>  
<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **Link**</sup>  

# Link

A `Link` relays weighted signals between a source and a target `Node`.  
&nbsp;


## Properties

```C++
unsigned long int key
```

A unique number which specifies the `Link`'s position relative to its neighboring `Node`s.  
&nbsp;


```C++
unsigned int tag
```

A unique number which specifies the `Link`'s identity within a `Genus`.  
&nbsp;


```C++
element_state state
```

Specifies whether the `Link` is `ENABLED` or `DISABLED`.  
&nbsp;


```C++
link_role role
```

Labels the `Link`'s role as `FORWARD`, `BIASING`, `RECURRENT` or `LOOPED`.  
&nbsp;


```C++
Node* source
```

Points to the `Node` from which the `Link`'s input signal originates.  
&nbsp;


```C++
Node* target
```

Points to the `Node` which receives the `Link`'s output signal.  
&nbsp;


``` C++
double weight
```

The weight applied to the `Link`'s output signal.  
&nbsp;


## Constructors

```C++
Link(unsigned long int key_, unsigned int tag_, element_state state_, link_role role_, Node* source_, Node* target_, double weight_)
```

Constructs a `Link` instance with properties given by the input arguments.  
&nbsp;


```C++
Link(Link* link_)
```

Constructs a shallow copy of the `Link` referenced by the input argument.  
&nbsp;


## Methods

```C++
void engage()
```

Prompts the `Link` to relay a signal to and engage its target `Node`.  
&nbsp;


```C++
Edge graph()
```

Generates an `Edge` encapsulating the `Link`'s properties.  
&nbsp;
