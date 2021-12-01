# Node

A `Node` is an individual processing unit which receives and broadcasts signals.

## Properties

#### `key`

> **Type:** `unsigned long int`.  
>  
> **Description:** A unique number which specifies the `Node`'s position relative to its neighboring `Node`s.

#### `tag`

> **Type:** `unsigned int`.  
>  
> **Description:** A unique number which specifies the `Node`'s identity within a `Genus`.

#### `state`

> **Type:** `element_state`.  
>  
> **Description:** Specifies whether the `Node` is active.

#### `role`

> **Type:** `node_role`.  
>  
> **Description:** Labels the `Node`'s role in the artificial neural network.

#### `incoming`

> **Type:** `std::vector<Link*>`.  
>  
> **Description:** Stores pointers to the `Node`'s incoming `Link`s.

#### `outgoing`

> **Type:** `std::vector<Link*>`.  
>  
> **Description:** Stores pointers to the `Node`'s outgoing `Link`s.

#### `inputs`

> **Type:** `std::vector<double>`.  
>  
> **Description:** Stores the external weighted signals received by the `Node`.

#### `output`

> **Type:** `double`.  
>  
> **Description:** The `Node`'s last generated output signal.

#### `activation`

> **Type:** `node_activation`.  
>  
> **Description:** Specifies the `Node`'s activation function.

#### `x`

> **Type:** `double`.  
>  
> **Description:** Specifies the `Node`'s horizontal coordinate.

#### `y`

> **Type:** `double`.  
>  
> **Description:** Specifies the `Node`'s vertical coordinate.

## Constructors

#### `Node(unsigned long int key, unsigned int tag, element_state state, node_role role, node_activation activation, double x, double y)`

> **Description:** Constructs a `Node` instance with properties given by the input arguments.  
>  
> **Returns:** `Node`.

#### `Node(unsigned long int, unsigned int, element_state, node_role, Node*, Node*, node_activation)`
> Returns a `Node` instance located half-way between two other `Node`s.
>
> **`Node`**`(Node*)`
> Returns a shallow copy of the `Node` referenced by the input pointer.

## Methods

> **`activate`**`()` 
> Returns a `double` containing the `Node`'s output signal.
>
> **`engage`**`()` 
> Prompts the `Node` to produce and broadcast an output signal. Returns `void`.
>
> **`disengage`**`()` 
> Primes the `Node` for a subsequent engagement. Returns `void`.
>
> **`clear`**`()` 
> Clears the `Node`'s output. Returns `void`.
>
> **`graph`**`()` 
> Returns a `Vertex` encapsulating the `Node`'s properties.