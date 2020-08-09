#include "chromosome.h"

// Constructor:

// Initialization constructor responsible for creating an empty `Chromosome`.
template <class E>
Chromosome<E>::Chromosome()
{
    // Maps a new empty `std::vector<E*>` to each role associated with a `E` element. The following conventions are adopted in agreement with the enumerated types `link_role`, `node_role`, and `element_state`.
    // TODO: Might want to use `reserve` here for future optimization when mapping these vectors.

    // -1: `E*`s encoding either a DISABLED INPUT `Node` or a DISABLED FORWARD `Link`.
    // +1: `E*`s encoding either an ENABLED INPUT `Node` or an ENABLED FORWARD `Link`.
    genes[-1] = std::vector<E*> {};
    genes[+1] = std::vector<E*> {};

    // -2: `E*`s encoding either a DISABLED BIAS `Node` or a DISABLED BIASING `Link`.
    // +2: `E*`s encoding either an ENABLED BIAS `Node` or an ENABLED BIASING `Link`.
    genes[-2] = std::vector<E*> {};
    genes[+2] = std::vector<E*> {};

    // -3: `E*`s encoding either a DISABLED HIDDEN `Node` or a DISABLED RECURRENT `Link`.
    // +3: `E*`s encoding either an ENABLED HIDDEN `Node` or an ENABLED RECURRENT `Link`.
    genes[-3] = std::vector<E*> {};
    genes[+3] = std::vector<E*> {};

    // -4: `E*`s encoding either a DISABLED OUTPUT `Node` or a DISABLED LOOPED `Link`.
    // +4: `E*`s encoding either an ENABLED OUTPUT `Node` or an ENABLED LOOPED `Link`.
    genes[-4] = std::vector<E*> {};
    genes[+4] = std::vector<E*> {};
}

// Copy constructor responsible for making a deep copy of the input `Chromosome`.
template <class E>
Chromosome<E>::Chromosome(Chromosome<E>* thatChromosome_)
{
    // Visits each locus in the input `Chromosome`.
    for (const auto& [locus_, elements_] : thatChromosome_->genes)
    {
        // Makes a shallow copy of each `E` encoded in the current locus.
        for (const auto& element_ : elements_)
        {
            genes[locus_].push_back(new E(element_));
        }
    }
}


// Destructor:

// Recursive destructor.
template <class E>
Chromosome<E>::~Chromosome()
{
    // Visits each locus in this `Chromosome`.
    for (const auto& [locus_, elements_] : genes)
    {
        // Deletes each `E` encoded in the current locus.
        for (const auto& element_ : elements_)
        {
            delete element_;
        }
    }
}


// Methods:

// Retrieves the total number of stored `E*`s with matching role(s).
template <class E>
int Chromosome<E>::size(const std::vector<int> roles_, const std::vector<int> states_)
{
    // Initializes the return variable.
    int size_ = 0;

    // Sums the number of elements of each role, ...
    for (const auto& role_ : roles_)
    {
        // ... as well as of each state.
        for (const auto& state_ : states_)
        {
            size_ += genes[state_*role_].size();
        }
    }

    // Returns the number of encoded `E`s.
    return size_;
}

// Returns an iterator at the beginning of a given locus.
template <class E>
typename std::vector<E*>::iterator Chromosome<E>::begin(int locus_)
{
    // Returns the iterator at the beginning of the matching locus.
    return genes[locus_].begin();
}

// Returns an iterator at the end of a given locus.
template <class E>
typename std::vector<E*>::iterator Chromosome<E>::end(int locus_)
{
    // Returns the iterator at the end of the matching locus.
    return genes[locus_].end();
}

// Inserts a `E*` into this `Chromosome`.
template <class E>
void Chromosome<E>::insert(E* element_)
{
    // Extracts the locus of the input `E*`.
    int locus_ = (element_->state)*(element_->role);

    // Inserts `E*` into this `Chromosome`'s matching locus.
    genes[locus_].push_back(element_);

    return;
}

// Removes a `E*` from this `Chromosome`.
template <class E>
void Chromosome<E>::remove(E* element_)
{
    // Extracts the locus of the input `E*`.
    int locus_ = (element_->state)*(element_->role);

    // Finds the position of the input `E*` in the matching locus.
    auto position_ = std::find(this->begin(locus_), this->end(locus_), element_);

    // Removes the input `E*` from this `Chromosome`'s matching locus.
    genes[locus_].erase(position_);

    return;
}

// Toggles the state of an encoded `E` element.
template <class E>
void Chromosome<E>::toggle(E* element_)
{
    // Removes the input `E*` from this `Chromosome`.
    this->remove(element_);

    // Flips the input `E*`'s state.
    if (element_->state == ENABLED)
    {
        element_->state = DISABLED;
    }
    else if (element_->state == DISABLED)
    {
        element_->state = ENABLED;
    }

    // Re-inserts the `E*` into this `Chromosome`.
    this->insert(element_);

    return;
}

// Selects a random `E*` with matching role(s) and state(s).
template <class E>
E* Chromosome<E>::random(const std::vector<int> roles_, const std::vector<int> states_)
{
    // Retrieves the total number of `E*`s with matching role(s) and state(s).
    int size_ = this->size(roles_, states_);

    // Samples a uniform probability mass function, effectively selecting one of the matching `E*`s.
    int sample_ = U(1, size_);

    // Searches this `Chromosome`'s loci for the selected `E*`.
    for (const auto& role_ : roles_)
    {
        for (const auto& state_ : states_)
        {
            // Gets the corresponding integer labeling the start of the current locus.
            size_ -= genes[state_*role_].size();

            // Checks whether the locus containing the selected `E*` has been found.
            if (sample_ > size_)
            {
                // Returns the matching `E*`.
                return genes[state_*role_][sample_ - size_ - 1];
            }
        }
    }

    // This is reached when no matching `E*`s exist. Returns `NULL`.
    return NULL;
}

// Retrieves all `E*`s with matching role(s) and state(s).
template <class E>
std::vector<E*> Chromosome<E>::retrieve(const std::vector<int> roles_, const std::vector<int> states_)
{
    // Initializes and reserves the appropriate amount of memory for a `std::vector<E*>` which will store all the `E*`s with matching role(s) and state(s).
    std::vector<E*> elements_;
    elements_.reserve(this->size(roles_, states_));

    // Concatenates all the relevant `E*`s.
    for (const auto& role_ : roles_)
    {
        for (const auto& state_ : states_)
        {
            elements_.insert(elements_.end(), this->begin(state_*role_), this->end(state_*role_));
        }
    }

    // Returns the concatenated `E*`s.
    return elements_;
}

// Sorts all `E*`s with matching role(s) and state(s) according to their identification tag.
template <class E>
std::vector<E*> Chromosome<E>::sort(const std::vector<int> roles_, const std::vector<int> states_)
{
    // Retrieves all `E*`s with matching role(s) and state(s).
    std::vector<E*> elements_ = this->retrieve(roles_, states_);

    // Sorts the collected `E*`s by their identification tag.
    std::sort(elements_.begin(), elements_.end(), [](const E* e_, const E* c_){return *e_ < *c_;});

    // Returns the sorted `E*`s.
    return elements_;
}

// Assimilates another `Chromosome` through a crossover operation.
template <class E>
void Chromosome<E>::crossover(Chromosome<E>* thatChromosome_)
{
    // Sorts all `E*`s stored in each `Chromosome`.
    std::vector<E*> these_ = this->sort();
    std::vector<E*> those_ = thatChromosome_->sort();

    // Extracts iterators at the beginning of each sorted sequence of `E*`s.
    auto this_ = these_.begin();
    auto that_ = those_.begin();

    // Performs the crossover between the two `Chromosome`s.
    while (this_ != these_.end() && that_ != those_.end())
    {
        // Keeps disjoint `E`s from this `Chromosome` unaltered.
        if (**this_ < **that_)
        {
            ++this_;
        }
        // Neglects disjoint `E`s not provenient from this `Chromosome`.
        else if (**that_ < **this_)
        {
            ++that_;
        }
        // Assimilates matching `E`s.
        else
        {
            // Samples the probability mass function for assimilating a `E`.
            if (P(assimilating_element))
            {
                // Assimilates the `E`'s properties.
                (*this_)->assimilate(*that_);
            }
            ++this_;
            ++that_;
        }
    }

    return;
}

/*
// Computes the compatibility between two `Chromosome`s.
template <class E>
double Chromosome<E>::compatibility(Chromosome<E>* thatChromosome_)
{
    // The number or matching, disjoint, and excess genes.
    int matching = 0;
    int disjoint = 0;
    int excess = 0;

    // Sorts all `E*`s stored in each `Chromosome`.
    std::vector<E*> these_ = this->sort();
    std::vector<E*> those_ = thatChromosome_->sort();

    // Extracts iterators at the beginning of each sorted sequence of `E*`s.
    auto this_ = these_.begin();
    auto that_ = those_.begin();

    while (this_ != these_.end() && that_ != those_.end())
    {
        // Counts an excess `E`.
        if (this_ == these.end())
        {
            ++excess;
            ++that_;
        }
        // Counts an excess `E`.
        else if (that_ == those.end())
        {
            ++excess;
            ++this_;
        }
        // Counts a disjoint `E`.
        else if (**this_ < **that_)
        {
            ++disjoint;
            ++this_;
        }
        // Counts a disjoint `E`.
        else if (**that_ < **this_)
        {
            ++disjoint;
            ++that_;
        }
        // Counts a matching `E`.
        else
        {
            ++matching;
            ++this_;
            ++that_;
        }
    }

    // Computes the compatibility metric.
    

    return;
}
*/
