# Link

 A `Link` relays weighted signals between a source and a target `Node`.




## Properties

```C++
unsigned long int key
```

A unique number which specifies the `Link`'s position relative to its neighboring `Node`s.  
&nbsp


```C++
unsigned int tag
```

A unique number which specifies the `Link`'s identity within a `Genus`.




```C++
int state
```

Specifies whether the `Link` is active.




```C++
unsigned int role
```

Labels the `Link`'s role in the artificial neural network.




```C++
Node* source
```

Points to the `Node` from which the `Link`'s input signal originates.




```C++
Node* target
```

Points to the `Node` which receives the `Link`'s output signal.




``` C++
double weight
```

The weight applied to the `Link`'s output signal.




## Constructors

```C++
Link Link(unsigned long int key, unsigned int tag, int state, unsigned int role, Node* source, Node* target, double weight)
```

Constructs a `Link` instance with properties given by the input arguments.  


```C++
Link Link(Link* link)
```

Constructs a shallow copy of the `Link` referenced by the input argument.  


## Methods

```C++
void engage()
```

Prompts the `Link` to relay a signal to and engage its target `Node`.




```C++
Edge graph()
```

Generates an `Edge` encapsulating the `Link`'s properties.
