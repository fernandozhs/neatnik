#include "utilities.hpp"


// Probability Sampling:

std::mt19937 PRNG;

int P(std::vector<double> w_, int condition_)
{
    std::discrete_distribution<int> distribution (w_.begin(), w_.end());

    return condition_*distribution(PRNG);
}

int U(int a_, int b_)
{
    std::uniform_int_distribution<int> distribution(a_, b_);

    return distribution(PRNG);
}

double U(double a_, double b_)
{
    std::uniform_real_distribution<double> distribution(a_, b_);

    return distribution(PRNG);
}

double N(double u_, double s_)
{
    std::normal_distribution<double> distribution(u_, s_);

    return distribution(PRNG);
}


// Activation Functions:

double Unity(std::vector<double>& x_)
{
    return 1.;
}

double Identity(std::vector<double>& x_)
{
    return std::accumulate(x_.begin(), x_.end(), 0.);
}

double Heaviside(std::vector<double>& x_)
{
    double sum_ = std::accumulate(x_.begin(), x_.end(), 0.);

    if (sum_ < 0.)
    {
        return 0.;
    }
    else
    {
        return 1.;
    }
}

double Logistic(std::vector<double>& x_)
{
    double sum_ = std::accumulate(x_.begin(), x_.end(), 0.);

    return 1./(1. + std::exp(sum_));
}

double ReLU(std::vector<double>& x_)
{
    double sum_ = std::accumulate(x_.begin(), x_.end(), 0.);

    if (sum_ > 0.)
    {
        return sum_;
    }
    else
    {
        return 0.0;
    }
}


// Assorted Functions:

long int Key(unsigned int i_, unsigned int j_, unsigned int k_, unsigned int l_)
{
    return ((long int)i_ << 61 | (long int)j_ << 60 | (long int)k_ << 30 | (long int)l_);
}
