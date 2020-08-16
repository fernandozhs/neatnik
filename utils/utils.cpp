#include "utils.h"

/*
  Probability Sampling:
  ----------- --------
*/

// Samples an integer from a probability mass function defined by a collection of weights `w_`.
int P(std::vector<double> w_)
{
    // Seeds the default random number generator.
    std::random_device seed;
    std::mt19937 generator(seed());

    // Initializes the probability distribution.
    std::discrete_distribution<int> distribution (w_.begin(), w_.end());

    // Returns a sample integer.
    return distribution(generator);
}

// Samples a uniformly-distributed integer from the interval `[a_, b_)`.
int U(int a_, int b_)
{
    // Seeds the default random number generator.
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
    // Seeds the default random number generator.
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
    // Seeds the default random number generator.
    std::random_device seed;
    std::mt19937 generator(seed());

    // Initializes the probability distribution.
    std::normal_distribution<double> distribution(u_, s_);

    // Returns a sample double.
    return distribution(generator);
}


/*
  Activation Functions:
  ---------- ---------
*/

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
    return 1./(1. + exp(-sum_));
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


/*
  Assorted Functions:
  -------- ---------
*/

// Rounds all entries of `x_` while preserving their sum.
std::vector<double> Round(std::vector<double> x_)
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
