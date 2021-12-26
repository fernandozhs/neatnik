#include "utilities.hpp"


// Probability Sampling:

// Samples an integer from a probability mass function defined by a collection of weights `w_`.
int P(std::vector<double> w_, int condition_)
{
    // Seeds the random number generator.
    std::random_device seed;
    std::mt19937 generator(seed());

    // Initializes the probability distribution.
    std::discrete_distribution<int> distribution (w_.begin(), w_.end());

    // Returns a sample integer.
    return condition_*distribution(generator);
}

// Samples a uniformly-distributed integer from the interval `[a_, b_)`.
int U(int a_, int b_)
{
    // Seeds the random number generator.
    std::random_device seed;
    std::mt19937 generator(seed());

    // Initializes the probability distribution.
    std::uniform_int_distribution<int> distribution(a_, b_);

    // Returns a sample integer.
    return distribution(generator);
}

// Samples a uniformly-distributed double from the interval `[a_, b_)`.
double U(double a_, double b_)
{
    // Seeds the random number generator.
    std::random_device seed;
    std::mt19937 generator(seed());

    // Initializes the probability distribution.
    std::uniform_real_distribution<double> distribution(a_, b_);

    // Returns a sample double.
    return distribution(generator);
}

// Draws a normally distributed double with mean `u_` and standard deviation `s_`.
double N(double u_, double s_)
{
    // Seeds the random number generator.
    std::random_device seed;
    std::mt19937 generator(seed());

    // Initializes the probability distribution.
    std::normal_distribution<double> distribution(u_, s_);

    // Returns a sample double.
    return distribution(generator);
}


// Activation Functions:

// Unity function evaluated at the sum of all entries of `x_`.
double Unity(std::vector<double>& x_)
{
    // Returns the unit constant regardless of `x_`.
    return 1.;
}

// Identity function evaluated at the sum of all entries of `x_`.
double Identity(std::vector<double>& x_)
{
    // Returns the sum of all entries of `x_`.
    return std::accumulate(x_.begin(), x_.end(), 0.);
}

// Heaviside function evaluated at the sum of all entries of `x_`.
double Heaviside(std::vector<double>& x_)
{
    // Sums all entries of `x_`.
    double sum_ = std::accumulate(x_.begin(), x_.end(), 0.);

    // Returns the value of the Heaviside function evaluated at `sum_`.
    if (sum_ < 0.)
    {
        return 0.;
    }
    else
    {
        return 1.;
    }
}

// Logistic function evaluated at the sum of all entries of `x_`.
double Logistic(std::vector<double>& x_)
{
    // Sums all entries of `x_`.
    double sum_ = std::accumulate(x_.begin(), x_.end(), 0.);

    // Returns the value of the Sigmoid function evaluated at `sum_`.
    return 1./(1. + std::exp(sum_));
}

// Rectified Linear Unit function evaluated at the sum of all entries of `x_`.
double ReLU(std::vector<double>& x_)
{
    // Sums all entries of `x_`.
    double sum_ = std::accumulate(x_.begin(), x_.end(), 0.);

    // Returns the value of the  Rectified Linear Unit function evaluated at `sum_`.
    if (sum_ > 0.)
    {
        return sum_;
    }
    else
    {
        return 0.0;
    }
}


// Distance Metrics:

// Computes the squared Euclidean distance between the points `x_` and `y_`.
double Euclidean(std::vector<double>& x_, std::vector<double>& y_)
{
    // Initializes the return variable.
    double distance_ = 0.;

    // Extracts iterators at the first component of each input point.
    auto x_component_ = x_.begin();
    auto y_component_ = y_.begin();

    // Computes the squared Euclidean distance between the input points.
    while (x_component_ != x_.end() && y_component_ != y_.end())
    {
        distance_ += std::pow(*x_component_ - *y_component_, 2);
        ++x_component_;
        ++y_component_;
    }

    // Returns the squared Euclidean distance.
    return distance_;
}


// Assorted Functions:

// Generates a unique search key from the `unsigned integers`: `i_` (3 bits), `j_` (1 bit), `k_` (30 bits), `l_` (30 bits).
long int Key(unsigned int i_, unsigned int j_, unsigned int k_, unsigned int l_)
{
    // Returns the unique search key.
    return ((long int)i_ << 61 | (long int)j_ << 60 | (long int)k_ << 30 | (long int)l_);
}

// Rounds all entries of `x_` while preserving their sum.
std::vector<double> Round(std::vector<double>& x_)
{
    // The indices, the integer part, and the fractional part of `x_`.
    std::vector<int> indices_(x_.size());
    std::vector<double> integer_(x_.size());
    std::vector<double> fractional_(x_.size());

    // Lists the indices of `x_`.
    std::iota(indices_.begin(), indices_.end(), 0);

    // Splits `x_` into its `integer_` and `fractional_` parts.
    for (const auto& index_ : indices_)
    {
        fractional_[index_] = std::modf(x_[index_], &integer_[index_]);
    }

    // Rearranges `indices_` so as to sort `fractional_` in descending order.
    std::sort(indices_.begin(), indices_.end(), [&](int i_, int j_){return fractional_[i_] > fractional_[j_];});

    // Performs the appropriate number of rounding up operations in order to preserve the sum of `x_`.
    for (int i_ = 0; i_ < std::accumulate(fractional_.begin(), fractional_.end(), 0.); i_++)
    {
        integer_[indices_[i_]]++;
    }

    // Returns the appropriately rounded `x_`.
    return integer_;
}

// Computes the sparseness of a set `Y_` at the point `x_`.
// TODO: Reimplement this using a kD-Tree data structure.
double Sparseness(unsigned int k_, std::vector<std::vector<double>>& Y_, std::vector<double>& x_)
{
    // Initializes and reserves the appropriate amount of memory for a `std::vector<double>` which will hold the distances from `x_` to each element of `Y_`.
    std::vector<double> distances_;
    distances_.reserve(Y_.size());

    // Computes the Euclidean distances from `x_` to each element of `Y_`.
    for (auto& y_ : Y_)
    {
        distances_.push_back(Euclidean(x_, y_));
    }

    // Collects the `k_` shortest distances computed above.
    std::nth_element(distances_.begin(), distances_.begin() + k_, distances_.end());

    // Returns the sparseness of `Y_` at `x_`.
    return std::accumulate(distances_.begin(), distances_.begin() + k_, 0.)/k_;
}
