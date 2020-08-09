#pragma once

#include <random>
#include <cmath>
#include <numeric>

/*
  Probability Sampling:
  ----------- --------
*/

// Samples an integer from a probability mass function defined by a collection of weights `w_`.
int P(std::vector<double> w_);

// Samples a uniformly-distributed integer from the interval `[a_, b_)`.
int U(int a_, int b_);

// Samples a uniformly-distributed double from the interval `[a_, b_)`.
double U(double a_, double b_);

// Samples a normally-distributed double with mean `u_` and standard deviation `s_`.
double N(double u_, double s_);


/*
  Activation Functions:
  ---------- ---------
*/

// Identity function evaluated at the sum of all entries of `x_`.
double Identity(std::vector<double>& x_);

// Heaviside function evaluated at the sum of all entries of `x_`.
double Heaviside(std::vector<double>& x_);

// Logistic function evaluated at the sum of all entries of `x_`.
double Logistic(std::vector<double>& x_);

// Rectified Linear Unit function evaluated at the sum of all entries of `x_`.
double ReLU(std::vector<double>& x_);
