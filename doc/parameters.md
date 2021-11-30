# Parameters

 The `Parameters` class encapsulates all the parameters which characterize an `Experiment`.

## Properties

* `evolution_driver`: an `enum` (`driver_metric`) specifying the metric responsible for driving the evolution of an `Experiment`'s `Genus`.
* `fitness_threshold`: a `double` specifying the fitness threshold for `Organism`s' `Graph`s to be stored.
* `novelty_threshold`: a `double` specifying the novelty threshold for `Organism`s' behaviors to be stored.
* `novelty_neighbors`: an `integer` specifying the number of nearest neighbors to be considered when assessing an `Organism`'s novelty.
* `novelty_threshold_modifiers`: a `std::vector<double>` specifying the factors by which the novelty threshold should decrease and increase.
* `generational_cycles`: an `integer` specifying the number of generational cycles for which an `Experiment` will run.
* `population_size`: an `integer` specifying the number of `Organism`s in an `Experiment`'s `Genus`.
* `mutation_attempts`: an `integer` specifying the number of attempts at mutating a `Genotype`.
* `spawning_attempts`: an `integer` specifying the number of attempts at producing an offspring `Organism`.
* `weight_bound`: a `double` specifying the bounding value for the generation and replacement of `Link` weights.
* `perturbation_power`: a `double` specifying the perturbation power when altering `Link` weights.
* `initial_activation`: an `enum` (`node_activation`) specifying the activation a new HIDDEN `Node` is initially equipped with.
* `rejection_fraction`: a `double` specifying the fraction of `Organism`s to be rejected at a given evolution cycle.
* `stagnation_threshold`: an `integer` specifying the number of evolution cycles beyond which a stagnated `Species` can be discarded.
* `compatibility_threshold`: a `double` specifying the degree of similarity beyond which `Organism`s group in separate `Species`.
* `compatibility_weights`: a `std::vector<double>` specifying the relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
* `enabling_link`: a `std::vector<double>` encapsulating the probability mass function for enabling of a random DISABLED `Link`.
* `altering_links`: a `std::vector<double>` encapsulating the probability mass function for altering each ENABLED `Link`.
* `altering_weight`: a `std::vector<double>` encapsulating the probability mass function for altering a `Link`'s weight.
* `adding_link`: a `std::vector<double>` encapsulating the probability mass function for adding a `Link` of a given role.
* `enabling_node`: a `std::vector<double>` encapsulating the probability mass function for enabling a DISABLED INPUT `Node` and connecting it to another `Node` of a given role.
* `altering_nodes`: a `std::vector<double>` encapsulating the probability mass function for altering each HIDDEN `Node`.
* `altering_activation`: a `std::vector<double>` encapsulating the probability mass function for altering a `Node`'s activation.
* `adding_node`: a `std::vector<double>` encapsulating the probability mass function for adding a `Node` by splitting a `Link` of a given role.
* `assimilating_links`: a `std::vector<double>` encapsulating the probability mass function for assimilating each homologous `Link`.
* `assimilating_nodes`: a `std::vector<double>` encapsulating the probability mass function for assimilating each homologous `Node`.
* `assimilating_weight`: a `std::vector<double>` encapsulating the probability mass function for assimilating a homologous `Link`'s weight.
* `assimilating_activation`: a `std::vector<double>` encapsulating the probability mass function for assimilating a homologous `Node`'s activation.
* `spawning_organism`: a `std::vector<double>` encapsulating the probability mass function for spawning a new `Organism` through a given process.



Constructor:

 default: initializes this `Parameters` instance.

 

 Destructor:

 default: deletes this `Parameters` instance.
