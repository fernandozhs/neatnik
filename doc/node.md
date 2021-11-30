# Node

A `Node` is an individual processing unit which receives and broadcasts signals.

## Properties

> **`key`:** `unsigned long int`
> A unique number which specifies the `Node`'s position relative to its neighboring `Node`s.
>
> **`tag`:** `unsigned int`
> A unique number which specifies the `Node`'s identity within a `Genus`.
>
> **`state`:** `element_state`
> Specifies whether the `Node` is active.
>
> **`role`:** `node_role`
> Labels the `Node`'s role in the artificial neural network.
>
> **`incoming`:** `std::vector<Link*>`
> Encodes pointers to the `Node`'s incoming `Link`s.
>
> **`outgoing`:** `std::vector<Link*>`
> Encodes pointers to the `Node`'s outgoing `Link`s.
>
> **`inputs`:** `std::vector<double>`
> Stores the external weighted signals sent to this `Node`.
>
> **`output`:** `double`
> The `Node`'s last generated output signal.
>
> **`activation`:** `node_activation`
> Specifies the `Node`'s activation function.
>
> **`x`:** `double`
> Specifies the `Node`'s horizontal coordinate.
>
> **`y`:** `double`
> Specifies the `Node`'s vertical coordinate.

## Constructors

> **`Node`**`(unsigned long int, unsigned int, element_state, node_role, node_activation, double, double)`
> Returns a `Node` instance with the input arguments as its properties.
>
> **`Node`**`(unsigned long int, unsigned int, element_state, node_role, Node*, Node*, node_activation)`
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