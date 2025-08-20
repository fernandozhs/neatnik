/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <cstdint>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include "neatnik.hpp"
#include "utilities.hpp"


template <class Element>
class Chromosome
{
public:

    // Properties:

    std::unordered_map<Key, Element*, Hash> logbook;

    std::unordered_map<int, std::vector<Element*>> genes;


    // Constructor:

    Chromosome();


    // Destructor:

    ~Chromosome();


    // Methods:

    unsigned int size(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    typename std::vector<Element*>::iterator begin(int locus_);

    typename std::vector<Element*>::iterator end(int locus_);

    Element* find(Key key_);

    Element* insert(Element* element_);

    Element* remove(Element* element_);

    void toggle(Element* element_, int state_);

    Element* random(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1}, const std::vector<double> weights_ = {});

    std::vector<Element*> retrieve(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    std::vector<Element*> sort(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    std::vector<double> priorities(const std::vector<unsigned int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1}, const double priority_ = 1.);

    static bool element_comparison(Element* first_element_, Element* second_element_);
};
