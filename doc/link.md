# Link

 A `Link` relays weighted signals between a source and a target `Node`.

## Properties

> **`key`:** `unsigned long int`  
>  A unique number which specifies the `Link`'s position relative to its neighboring `Node`s.
>
> **`tag`:** `unsigned int`  
>  A unique number which specifies the `Link`'s identity within a `Genus`.
>
> **`state`:** `element_state`  
>  Specifies whether the `Link` is active.
>
> **`role`:** `link_role`  
>  Labels the `Link`'s role in the artificial neural network.
>
> **`source`:** `Node*`  
>  Points to the `Node` from which the `Link`'s input signal originates.
>
> **`target`:** `Node*`  
>  Points to the `Node` to which the `Link`'s output signal is relayed.
>
> **`weight`:** `double`  
> The weight applied to the `Link`'s output signal.

## Constructors

> **`Link`**`(unsigned long int, unsigned int, element_state, link_role, Node*, Node*, double)`
>  Returns a `Link` instance with the input arguments as its properties.
>
> **`Link`**`(Link*)`
>  Returns a shallow copy of the `Link` referenced by the input pointer.

## Methods

> **`engage`**`()` 
>  Prompts the `Link` to relay a signal to and engage its target `Node`. Returns `void`.
>
> **`graph`**`()` 
>  Returns an `Edge` encapsulating the `Link`'s properties.
