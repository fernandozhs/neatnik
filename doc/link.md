# Link

 A `Link` relays weighted signals between a source and a target `Node`.

## Properties

#### `key`

> **Type:** `unsigned long int`.  
>  
> **Description:** A unique number which specifies the `Link`'s position relative to its neighboring `Node`s.

#### `tag`

> **Type:** `unsigned int`.  
>  
> **Description:** A unique number which specifies the `Link`'s identity within a `Genus`.

#### `state`

> **Type:** `element_state`.  
>  
> **Description:** Specifies whether the `Link` is active.

#### `role`

> **Type:** `link_role`.  
>  
> **Description:** Labels the `Link`'s role in the artificial neural network.

#### `source`

> **Type:** `Node*`.  
>  
> **Description:** Points to the `Node` from which the `Link`'s input signal originates.

#### `target`

> **Type:** `Node*`.  
>  
> **Description:** Points to the `Node` to which the `Link`'s output signal is relayed.

#### `weight`

> **Type:** `double`.  
>  
> **Description:** The weight applied to the `Link`'s output signal.

## Constructors

#### `Link(unsigned long int key, unsigned int tag, element_state state, link_role role, Node* source, Node* target, double weight)`

> **Description:** Constructs a `Link` instance with properties given by the input arguments.  
>  
> **Returns:** `Link`.

#### `Link(Link* link)`

> **Description:** Constructs a shallow copy of the `Link` referenced by the input argument.  
>  
>  **Returns:** `Link`.

## Methods

#### `engage()`

> **Description:** Prompts the `Link` to relay a signal to and engage its target `Node`.  
>  
> **Returns:** `void`.

#### `graph()`

> **Description:** Generates an `Edge` encapsulating the `Link`'s properties.  
>  
> **Returns:** `Edge`.
