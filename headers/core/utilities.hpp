/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <cstdint>
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


// Hash Map:

struct Hash
{
    std::uint64_t operator()(const std::tuple<std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t>& t_) const noexcept
    {
        std::uint64_t role_ = std::get<0>(t_) & 0x7u;
        std::uint64_t state_ = std::get<1>(t_) & 0x1u;
        std::uint64_t source_tag_ = std::get<2>(t_) & 0x3FFFFFFFu;
        std::uint64_t target_tag_ = std::get<3>(t_) & 0x3FFFFFFFu;

        return (role_ << 61) | (state_ << 60) | (source_tag_ << 30) | target_tag_;
    }
};
