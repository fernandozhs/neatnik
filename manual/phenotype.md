<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **Phenotype**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Phenotype

A `Phenotype` embodies the artificial neural network encoded by an `Organism`'s `Genotype`.  
&nbsp;


## Properties

```C++
Organism* organism
```

Points to the `Phenotype`'s associated `Organism`.  
&nbsp;


```C++
std::vector<double> output
```

The `Phenotype`'s latest output.  
&nbsp;


## Constructor

```C++
Phenotype(Organism* organism_)
```

Constructs a `Phenotype`, associating it to the referenced input `Organism`.  
&nbsp;


## Methods

```C++
void assemble()
```

Assembles the `Phenotype` by ensuring all `Link`s and `Node`s are properly connected. The `disassemble()` method is always called prior to assemblage in order to ensure that the artificial neural network's topology is correctly represented.  
&nbsp;


```C++
void disassemble()
```

Disassembles the `Phenotype` by undoing all existing connections between `Link`s and `Node`s. The `deactivate()` method is always called prior to disassemblage so as to guarantee that the artificial neural network can be promptly activated once re-assembled.   
&nbsp;


```C++
void activate(std::vector<double> inputs_)
```

Propagates the `input_` signal through the artificial neural network, storing its outcome in the `Phenotype`'s `output`.  
&nbsp;


```C++
void deactivate();
```

Disengages all `ENABLED` `Node`s and clears the `Phenotype`'s `output`, allowing the artificial neural network to be activated once again.  
&nbsp;


```C++
void discontinue()
```

Clears the `output` of each `HIDDEN` and `OUTPUT` `Node`, effectively erasing the artificial neural network's memory of past activations.   
&nbsp;
