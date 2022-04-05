<sub>**[Utilities](utilities.md)**</sub>  
<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **Genotype** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Genotype

A `Genotype` stores and manipulates the genetic make-up of an `Organism`, i.e., its `Chromosome<Link>` and `Chromosome<Node>`.  
&nbsp;


## Properties

```C++
Organism* organism
```

Points to the `Genotype`'s associated `Organism`.  
&nbsp;

```C++
Chromosome<Link>* links
```

Points to the `Chromosome<Link>` encoding the `Genotype`'s `Link`s.  
&nbsp;


```C++
Chromosome<Node>* nodes
```

Points to the `Chromosome<Node>` encoding the `Genotype`'s `Node`s.  
&nbsp;


## Constructors

```C++
Genotype(Organism* organism_, Graph graph_)
```

Constructs a `Genotype` from a minimal input `graph_`, associating it to the referenced input `Organism`.    
&nbsp;


```C++
Genotype(Organism* organism_, Genotype* genotype_);
```

Constructs a deep copy of the referenced input `Genotype`, associating it to the referenced input `Organism`.  
&nbsp;


```C++
Genotype(Graph graph_)
```

Constructs a replica of the `Genotype` encoded by the input `graph_`. This `Genotype` is not associated with any `Organism`.  
&nbsp;


## Destructor

```C++
~Genotype()
```

Destructs the `Genotype`, as well as its `Chromosome<Link>` and `Chromosome<Node>`.  
&nbsp;


## Methods

```C++
int size()
```

Returns the number of `Link`s and `Node`s encoded by the `Genotype`.  
&nbsp;


```C++
bool contain(int role_, element_type type_, unsigned int source_tag_, unsigned int target_tag_)
```

Returns `true` if the `Genotype` encodes a `Node` or a `Link` with `key` characterized by the input `role_`, `type_`, `source_tag`, and `target_tag`. Returns `false` otherwise.  
&nbsp;


```C++
Link* encode(link_role role_, element_type type_, Node* source_, Node* target_, double weight_)
```

Encodes a `Link` with properties given by the input arguments into the `Genotype`, automatically assigning it a `key` and a `tag`. Returns a pointer to the newly encoded `Link`.  
&nbsp;


```C++
Node* encode(node_role role_, element_type type_, Node* source_, Node* target_, node_activation activation_)
```

Encodes a `Node` with properties given by the input arguments into the `Genotype`, automatically assigning it a `key` and a `tag`. Returns a pointer to the newly encoded `Node`.  
&nbsp;


```C++
Node* encode(element_state state_, node_role role_, element_type type_, node_activation activation_, int x_, int y_)
```

Encodes a `Node` with properties given by the input arguments into the `Genotype`, automatically assigning it a `key` and a `tag`. Returns a pointer to the newly encoded `Node`.  
&nbsp;


```C++
void mutate()
```

Mutates the `Genotype` by attempting to encode new `Link`s and `Node`s, or alter already-encoded `Link`s and `Node`s.  
&nbsp;


```C++
void enable_link()
```

Toggles `ENABLED` a random `DISABLED` `Link` encoded by the `Genotype`.  
&nbsp;


```C++
void alter_links()
```

Attempts to alter the `weight` of each `ENABLED` `Link` encoded by the `Genotype`.  
&nbsp;


```C++
void add_link(link_role role_)
```

Attempts to encode a `Link` of the input `role_` into the `Genotype`.  
&nbsp;


```C++
void enable_node(node_role role_)
```

Toggles `ENABLED` a random `DISABLED` `INPUT` `Node` encoded by the `Genotype`, connecting it to another `Node` of the input `role_` with a `FORWARD` `Link`.  
&nbsp;


```C++
void alter_nodes()
```

Attempts to alter the `activation` of each `ENABLED` `HIDDEN` `Node` encoded by the `Genotype`.  
&nbsp;


```C++
void add_node(node_role role_)
```

Attempts to encode a `Node` of the input `role_` into the `Genotype`. Returns `void`.  
&nbsp;


```C++
void assimilate(Genotype* genotype_)
```

Attempts to assimilate the homologous `Link`s and `Node`s encoded by the referenced input `Genotype`.  
&nbsp;


```C++
void assimilate_links(Chromosome<Link>* chromosome_)
```

Attempts to assimilate each homologous `Link` encoded by the referenced input `Chromosome<Link>`.  
&nbsp;


```C++
void assimilate_nodes(Chromosome<Node>* chromosome_)
```

Attempts to assimilate each homologous `Node` encoded by the referenced input `Chromosome<Node>`.  
&nbsp;


```C++
double compatibility(Genotype* genotype_)
```

Returns the degree of compatibility between the `Genotype` and the referenced input `Genotype`.  
&nbsp;


```C++
Graph graph()
```

Generates a `Graph` encapsulating the `Genotype`'s properties.  
&nbsp;
