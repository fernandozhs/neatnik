<sub>**Utilities**</sub>  
<sub>**[Parameters](parameters.md)**</sub>  
<sub>**[Experiment](experiment.md)** ━━ **[Genus](genus.md)** ━━ **[Species](species.md)** ━━ **[Organism](organism.md)** ━━ **[Genotype](genotype.md)** ━━ **[Chromosome](chromosome.md)** ━━ **[Node](node.md)**</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━ **[Phenotype](phenotype.md)**</sup>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<sup>┗━━━━━ **[Link](link.md)**</sup>  

# Utilities

## Probability Sampling

```C++
std::mt19937 PRNG;
```

A Mersenne Twister pseudo-random number generator which underpins all other probability sampling functions.  
&nbsp;


```C++
int P(std::vector<double> w_, int condition_ = true)
```

Samples an integer from a probability mass function defined by a collection of weights `w_` whenever the input `condition_` is `true`. If the input `condition_` is `false`, returns zero.  
&nbsp;


```C++
int U(int a_, int b_)
```

Samples a uniformly-distributed integer from the interval `[a_, b_)`.  
&nbsp;


```C++
double U(double a_, double b_)
```

Samples a uniformly-distributed double from the interval `[a_, b_)`.  
&nbsp;


```C++
double N(double u_, double s_)
```

Samples a normally-distributed double with mean `u_` and standard deviation `s_`.  
&nbsp;


```C++
Node* source
```

Points to the `Node` from which the `Link`'s input signal originates.  
&nbsp;


## Activation Functions

``` C++
double Unity(std::vector<double>& x_)
```

Unity function evaluated at the sum of all entries of `x_`.  
&nbsp;


``` C++
double Identity(std::vector<double>& x_)
```

Identity function evaluated at the sum of all entries of `x_`.  
&nbsp;


``` C++
double Heaviside(std::vector<double>& x_)
```

Heaviside function evaluated at the sum of all entries of `x_`.  
&nbsp;


``` C++
double Logistic(std::vector<double>& x_)
```

Logistic function evaluated at the sum of all entries of `x_`.  
&nbsp;


``` C++
double ReLU(std::vector<double>& x_)
```

Rectified Linear Unit function evaluated at the sum of all entries of `x_`.  
&nbsp;


## Assorted Functions

```C++
long int Key(unsigned int i_, unsigned int j_, unsigned int k_, unsigned int l_)
```

Generates a unique `key` from the inputs: `i_` (3 bits), `j_` (1 bit), `k_` (30 bits), `l_` (30 bits).  
&nbsp;
