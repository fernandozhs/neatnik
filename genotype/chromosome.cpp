#include "../genotype/chromosome.h"

// Constructor:

// Initialization constructor responsible for creating an empty `Chromosome`.
template <class E>
Chromosome<E>::Chromosome()
{
    // Initializes this `Chromosome` without any encoded `E` elements.
}


// Destructor:

// Recursive destructor responsible for deleting this `Chromosome` and all the `E` elements it encodes.
template <class E>
Chromosome<E>::~Chromosome()
{
    // Deletes each `E` encoded in this `Chromosome`
    for (auto& theElement_ : this->retrieve())
    {
        delete theElement_;
    }
}


// Methods:

// Retrieves the total number of encoded `E`s with matching role(s).
template <class E>
int Chromosome<E>::size(const std::vector<int> roles_, const std::vector<int> states_)
{
    // Initializes the return variable.
    int size_ = 0;

    // Sums the number of `E*`s of each role, ...
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

// Retrieves an iterator at the beginning of a given locus.
template <class E>
typename std::vector<E*>::iterator Chromosome<E>::begin(int locus_)
{
    // Returns the iterator at the beginning of the matching locus.
    return genes[locus_].begin();
}

// Retrieves an iterator at the end of a given locus.
template <class E>
typename std::vector<E*>::iterator Chromosome<E>::end(int locus_)
{
    // Returns the iterator at the end of the matching locus.
    return genes[locus_].end();
}

// Retrieves the `E*` with a matching key.
template <class E>
E* Chromosome<E>::find(unsigned long int key_)
{
    // Searches for a log entry with a matching key.
    auto match_ = logbook.find(key_);

    // Checks whether a matching log has been found.
    if (match_ != logbook.end())
    {
        // Returns the `E*` associated with the matching log.
        return (*match_).second;
    }
    else
    {
        // No match has been found.
        return nullptr;
    }
}

// Inserts an `E*` into this `Chromosome`.
template <class E>
E* Chromosome<E>::insert(E* thatElement_)
{
    // Creates a new log for the input `E*`.
    std::pair<unsigned long int, E*> log_ (thatElement_->key, thatElement_);

    // Logs the input `E*`.
    logbook.insert(log_);

    // Extracts the locus of the input `E*`.
    int locus_ = (thatElement_->state)*(thatElement_->role);

    // Inserts the input `E*` into this `Chromosome`'s matching locus.
    genes[locus_].push_back(thatElement_);

    return thatElement_;
}

// Removes an `E*` from this `Chromosome`.
template <class E>
E* Chromosome<E>::remove(E* thatElement_)
{
    // Extracts the locus of the input `E*`.
    int locus_ = (thatElement_->state)*(thatElement_->role);

    // Locates the input `E*` in the matching locus.
    auto location_ = std::find(this->begin(locus_), this->end(locus_), thatElement_);

    // Removes the input `E*` from this `Chromosome`'s matching locus.
    genes[locus_].erase(location_);

    return thatElement_;
}

// Toggles the state of an encoded `E` element.
template <class E>
void Chromosome<E>::toggle(E* thatElement_, int state_)
{
    // Removes the input `E*` from this `Chromosome`.
    this->remove(thatElement_);

    // Updates the input `E*`'s state.
    thatElement_->state = (element_state)state_;

    // Re-inserts the `E*` into this `Chromosome`.
    this->insert(thatElement_);

    return;
}

// Selects a random `E*` with matching role(s) and state(s).
template <class E>
E* Chromosome<E>::random(const std::vector<int> roles_, const std::vector<int> states_, const std::vector<double> weights_)
{
    // Initializes auxiliary variable.
    int sample_;

    // Retrieves the number of encoded `E`s with matching role(s) and state(s).
    int size_ = this->size(roles_, states_);

    // Checks whether no matching `E*`s exist.
    if (size_ == 0)
    {
        // Returns `nullptr`.
        return nullptr;
    }

    // Decides which probability mass function to employ when sampling this `Chromosome`'s `E*`s.
    if (weights_.size() == 0)
    {
        // Samples an `E*` from a uniform probability mass function.
        sample_ = U(1, size_);
    }
    else
    {
        // Samples an `E*` from the input probability mass function.
        sample_ = P(weights_) + 1;
    }

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

    // This line should never be reached.
    return nullptr;
}

// Retrieves all `E*`s with matching role(s) and state(s).
template <class E>
std::vector<E*> Chromosome<E>::retrieve(const std::vector<int> roles_, const std::vector<int> states_)
{
    // Initializes and reserves the appropriate amount of memory for a `std::vector<E*>` which will store all the `E*`s with matching role(s) and state(s).
    std::vector<E*> thoseElements_;
    thoseElements_.reserve(this->size(roles_, states_));

    // Concatenates all the relevant `E*`s.
    for (const auto& role_ : roles_)
    {
        for (const auto& state_ : states_)
        {
            thoseElements_.insert(thoseElements_.end(), this->begin(state_*role_), this->end(state_*role_));
        }
    }

    // Returns the concatenated `E*`s.
    return thoseElements_;
}

// Sorts all `E*`s with matching role(s) and state(s) according the criterion for comparing two `E*`s.
template <class E>
std::vector<E*> Chromosome<E>::sort(const std::vector<int> roles_, const std::vector<int> states_)
{
    // Retrieves all `E*`s with matching role(s) and state(s).
    std::vector<E*> thoseElements_ = this->retrieve(roles_, states_);

    // Rearranges the collected `E*`s according to their comparison criterion.
    std::sort(thoseElements_.begin(), thoseElements_.end(), this->element_comparison);

    // Returns the sorted `E*`s.
    return thoseElements_;
}

// The criterion for comparing two `E*`s.
template <class E>
bool Chromosome<E>::element_comparison(E* thatElement_, E* thisElement_)
{
    // Compares the input `E*`s' identification tags through the '<' operation.
    return thatElement_->tag < thisElement_->tag;
}
