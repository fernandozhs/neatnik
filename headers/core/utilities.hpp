/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <vector>
#include <random>
#include <cmath>
#include <numeric>
#include <algorithm>


// Probability Sampling:

extern std::mt19937 PRNG;

int P(std::vector<double> w_, int condition_ = true);

int U(int a_, int b_);

double U(double a_, double b_);

double N(double u_, double s_);


// Activation Functions:

double Unity(std::vector<double>& x_);

double Identity(std::vector<double>& x_);

double Heaviside(std::vector<double>& x_);

double Logistic(std::vector<double>& x_);

double ReLU(std::vector<double>& x_);


// Assorted Functions:

long int Key(unsigned int i_, unsigned int j_, unsigned int k_, unsigned int l_);
