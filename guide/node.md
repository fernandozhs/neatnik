<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **Node**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Node

A `Node` is an individual processing unit which receives and broadcasts signals.  
&nbsp;


## Properties

```C++
unsigned long int key
```

A unique number which specifies the `Node`'s position relative to its neighboring `Node`s.  
&nbsp;


```C++
unsigned int tag
```

A unique number which specifies the `Node`'s identity within a `Genus`.  
&nbsp;


```C++
element_state state
```

Specifies whether the `Node` is `ENABLED` or `DISABLED`.  
&nbsp;


```C++
node_role role
```

Labels the `Node`'s role as `INPUT`, `HIDDEN`, `BIAS`, or `OUTPUT`.  
&nbsp;


```C++
std::vector<Link*> incoming
```

Stores pointers to the `Node`'s incoming `Link`s.  
&nbsp;


```C++
std::vector<Link*> outgoing
```

Stores pointers to the `Node`'s outgoing `Link`s.  
&nbsp;


```C++
std::vector<double> inputs
```

Stores the external weighted signals received by the `Node`.  
&nbsp;


```C++
double output
```

The `Node`'s last generated output signal.  
&nbsp;


```C++
node_activation activation
```

Specifies whether the `Node`'s activation corresponds to the `HEAVISIDE`, `RELU`, `LOGISTIC`, `IDENTITY`, or `UNITY` function.  
&nbsp;


```C++
double x
```

The `Node`'s horizontal coordinate.  
&nbsp;


```C++
double y
```

The `Node`'s vertical coordinate.  
&nbsp;


## Constructors

```C++
Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, node_activation activation_, double x_, double y_)
```

Constructs a `Node` instance with properties given by the input arguments.  
&nbsp;


```C++
Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, Node* source_, Node* target_, node_activation activation_)
```

Constructs a `Node` instance located half-way between two other `Node`s.  
&nbsp;


```C++
Node(Node* node_)
```

Constructs a shallow copy of the `Node` referenced by the input pointer.  
&nbsp;


## Methods

```C++
double activate()
```

Produces the `Node`'s output signal.  
&nbsp;


```C++
void engage()
```

Prompts the `Node` to produce and broadcast its output signal through its outgoing `Link`s.  
&nbsp;


```C++
void disengage()
```

Primes the `Node` for a subsequent engagement.  
&nbsp;


```C++
void clear()
```

Clears the `Node`'s output.  
&nbsp;


```C++
Vertex graph()
```

Generates a `Vertex` encapsulating the `Node`'s properties.
