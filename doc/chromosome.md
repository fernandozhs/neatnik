# Chromosome

 A `Chromosome` stores and manipulates a collection of `Element*`s.

## Properties

> **`logbook`:** `std::unordered_map<unsigned long int, Element*>`
> Catalogs all `Element*`s by their `key` value.
>
> **`genes`:** `std::unordered_map<int, std::vector<Element*>>`
> Catalogs all `Element*`s by the their `locus`, i.e., by the product of their `state` and `role`.

## Constructor

> **`Chromosome`**`()`
> Returns an empty `Chromosome`.

## Destructor

> **`~Chromosome`**`()`
> Deletes the `Chromosome` and all the `Element*`s it encodes.

## Methods

> **`size`**`(const std::vector<int> roles, const std::vector<int> states)` 
> Returns the `int` number of encoded `Element*`s with a matching `role` and `state`.
>
> **`begin`**`(int locus)` 
> Returns a `std::vector<Element*>::iterator` at the beginning of a given `locus`.
>
> **`end`**`(int locus)` 
> Returns a `std::vector<Element*>::iterator` at the end of a given `locus`.
>
> **`find`**`(unsigned long int key)` 
> Returns the `Element*` with the matching `key`. If the no match is found, returns `nullptr`.
>
> **`insert`**`(Element* element)` 
> Inserts an `Element*` into the `Chromosome`. Returns the inserted `Element*`.
>
> **`remove`**`(Element* element)` 
> Removes an `Element*` from the `Chromosome`. Returns the removed `Element*`.
>
> **`toggle`**`(Element* element, int state)` 
> Toggles the `state` of an an `Element*`. Returns `void`.
>
> **`random`**`(const std::vector<int> roles, const std::vector<int> states, const std::vector<double> weights)` 
> Returns a random `Element*` with a matching `role` and `state`. The `weights` argument modifies the odds that the matching `Element*`s being returned.
>
> **`retrieve`**`(const std::vector<int> roles, const std::vector<int> states)` 
> Returns a `std::vector<Element*>` containing all `Element*`s with a matching `role` and `state`.
>
> **`sort`**`(const std::vector<int> roles, const std::vector<int> states)` 
> Returns a sorted `std::vector<Element*>` containing all `Element*`s with a matching `role` and `state`. The sorting criterium is provided by the `element_comparison` method.
>
> **`element_comparison`**`(Element* element, Element* element)` 
> Returns a `bool` value obtained from the comparison between the two input `Element*`s' `tag`s.
