#include "../genus/genus.h"

// Constructor:

// Initialization constructor responsible for building a `Genus` with `Organism`s characterized by minimal `Graph`s.
Genus::Genus(std::vector<Graph> thoseGraphs_)
{
    // Initializes a new `Species` with `Organism`s characterized by minimal `Graph`s.
    Species* newSpecies_ = new Species(this, DOMINANT, thoseGraphs_);

    // Inserts the new `Species*` into this `Genus`.
    this->insert(newSpecies_);
}


// Destructor:

// Recursive destructor responsible for deleting this `Genus` and all its `Species`.
Genus::~Genus()
{
    // Deletes each `Species` stored in this `Genus`
    for (auto& theSpecies_ : this->retrieve())
    {
        delete theSpecies_;
    }
}


// Methods:

// Tags a `Link` or `Node` with a new or existing identification tag.
std::pair<unsigned long int, unsigned int> Genus::tag(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_)
{
    // Generates the search key associated with the `Link` or `Node` of interest.
    unsigned long int key_ = Key(role_, type_, in_tag_, out_tag_);

    // Searches for a log entry matching the `Link` or `Node` of interest.
    auto match_ = logbook.find(key_);

    // Checks whether a matching log has been found.
    if (match_ != logbook.end())
    {
        // Returns the matching log.
        return *match_;
    }
    else
    {
        // Returns a new log entry.
        return this->log(key_);
    }
}

// Logs a new `Link` or `Node`.
std::pair<unsigned long int, unsigned int> Genus::log(unsigned long int key_)
{
    // Creates a new log.
    std::pair<unsigned long int, unsigned int> log_ (key_, tag_counter);

    // Increments the identification tag counter.
    tag_counter++;

    // Logs the new `Link` or `Node`.
    logbook.insert(log_);

    // Returns the newly created log entry.
    return log_;
}

// Retrieves the total number of stored `Species` in the matching group(s).
int Genus::size(const std::vector<int> groups_)
{
    // Initializes the return variable.
    int size_ = 0;

    // Sums the number of `Species*` in each group.
    for (const auto& group_ : groups_)
    {
        size_ += species[group_].size();
    }

    // Returns the number of stored `Species`.
    return size_;
}

// Retrieves an iterator at the beginning of a given group.
typename std::vector<Species*>::iterator Genus::begin(int group_)
{
    // Returns the iterator at the beginning of the matching group.
    return species[group_].begin();
}

// Retrieves an iterator at the end of a given group.
typename std::vector<Species*>::iterator Genus::end(int group_)
{
    // Returns the iterator at the end of the matching group.
    return species[group_].end();
}

// Retrieves the first `Species*` of a given group.
Species* Genus::front(int group_)
{
    // Returns the first `Species*` of the matching group.
    return species[group_].front();
}

// Retrieves the last `Species*` of a given group.
Species* Genus::back(int group_)
{
    // Returns the last `Species*` of the matching group.
    return species[group_].back();
}

// Inserts a `Species*` into this `Genus`.
Species* Genus::insert(Species* thatSpecies_)
{
    // Extracts the input `Species*`' group.
    int group_ = thatSpecies_->group;

    // Assigns the input `Species*` to this `Genus`.
    thatSpecies_->genus = this;

    // Inserts the input `Species*` into this `Genus`' matching group.
    species[group_].push_back(thatSpecies_);

    return thatSpecies_;
}

// Removes a `Species*` from this `Genus`.
Species* Genus::remove(Species* thatSpecies_)
{
    // Extracts the input `Species*`'s group.
    int group_ = thatSpecies_->group;

    // Locates the input `Species*` in the matching group.
    auto location_ = std::find(this->begin(group_), this->end(group_), thatSpecies_);

    // Removes the input `Species*` from this `Genus`' matching group.
    species[group_].erase(location_);

    return thatSpecies_;
}

// Purges a `Species*` from this `Genus`.
void Genus::purge(Species* thatSpecies_)
{
    // Deletes and removes the input `Species*` from this `Genus`.
    delete this->remove(thatSpecies_);

    return;
}

// Purges all `Species*` from the matching group(s).
void Genus::purge(const std::vector<int> groups_)
{
    // Deletes all `Species*` from the matching group(s).
    for (const auto& theSpecies_ : this->retrieve(groups_))
    {
        delete theSpecies_;
    }

    // Clears the maching group(s).
    for (const auto& group_ : groups_)
    {
        species[group_].clear();
    }

    return;
}

// Toggles the group associated with the input `Species*`.
void Genus::toggle(Species* thatSpecies_, int group_)
{
    // Removes the input `Species*` from this `Genus`.
    this->remove(thatSpecies_);

    // Updates the input `Species*`' group.
    thatSpecies_->group = (taxon_group)group_;

    // Re-inserts the `Species*` into this `Genus`.
    this->insert(thatSpecies_);

    return;
}

// Selects a random `Species*` from the matching group(s).
Species* Genus::random(const std::vector<int> groups_, const std::vector<double> weights_)
{
    // Initializes auxiliary variable.
    int sample_;

    // Retrieves the number of stored `Species` in the matching group(s).
    int size_ = this->size(groups_);

    // Checks whether no matching `Species*` exist.
    if (size_ == 0)
    {
        // Returns `nullptr`.
        return nullptr;
    }

    // Decides which probability mass function to employ when sampling this `Genus`' `Species*`.
    if (weights_.size() == 0)
    {
        // Samples a `Species*` from a uniform probability mass function.
        sample_ = U(1, size_);
    }
    else
    {
        // Samples a `Species*` from the input probability mass function.
        sample_ = P(weights_) + 1;
    }

    // Searches this `Genus`' groups for the selected `Species*`.
    for (const auto& group_ : groups_)
    {
        // Gets the corresponding integer labeling the start of the current group.
        size_ -= species[group_].size();

        // Checks whether the group containing the selected `Species*` has been found.
        if (sample_ > size_)
        {
            // Returns the matching `Species*`.
            return species[group_][sample_ - size_ - 1];
        }
    }

    // This line should never be reached.
    return nullptr;
}

// Retrieves all `Species*` from the matching group(s).
std::vector<Species*> Genus::retrieve(const std::vector<int> groups_)
{
    // Initializes and reserves the appropriate amount of memory for a `std::vector<Species*>` which will store all the `Species*` from the matching group(s).
    std::vector<Species*> thoseSpecies_;
    thoseSpecies_.reserve(this->size(groups_));

    // Concatenates all the relevant `Species*`.
    for (const auto& group_ : groups_)
    {
        thoseSpecies_.insert(thoseSpecies_.end(), this->begin(group_), this->end(group_));
    }

    // Returns the concatenated `Species*`.
    return thoseSpecies_;
}

// Sorts all `Species*` from the matching group(s) according to their performance.
std::vector<Species*> Genus::sort(const std::vector<int> groups_)
{
    // Retrieves all `Species*` from the matching group(s).
    std::vector<Species*> thoseSpecies_ = this->retrieve(groups_);

    // Rearranges the collected `Species*` according to their comparison criterion.
    std::sort(thoseSpecies_.begin(), thoseSpecies_.end(), this->species_comparison);

    // Returns the sorted `Species*`.
    return thoseSpecies_;
}

// Finds the best performing `Organism`s and purges stagnated `Species`.
void Genus::select()
{
    // Finds each `Species`' best performing `Organism` and purges a fraction of the remainder.
    for (const auto& theSpecies_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        theSpecies_->select();
    }

    // Sorts all `Species` stored in this `Genus`.
    std::vector<Species*> thoseSpecies_ = this->sort();

    // Ensures the best performing `Species` is up to date.
    if (this->front(DOMINANT) != thoseSpecies_.front())
    {
        this->toggle(this->front(DOMINANT), CONTESTANT);
        this->toggle(thoseSpecies_.front(), DOMINANT);
    }

    // Purges stagnated `Species`.
    for (auto that_ = ++thoseSpecies_.begin(); that_ != thoseSpecies_.end(); ++that_)
    {
        if (this->species_rejection(*that_))
        {
            this->purge(*that_);
        }
    }

    return;
}

// Spawns a new generation of `Organism`s.
void Genus::spawn(int allocation_)
{
    // A parent `Species*` and a `std::vector<double>` containing each parent `Species` rank.
    Species* theSpecies_;
    std::vector<double> ranks_;

    // Extracts the ranks of all parent `Species` and adjusts the input allocation.
    for (const auto& theSpecies_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        ranks_.push_back(theSpecies_->rank);
        --allocation_;
    }

    // Spawns a new generation of `Organism`s.
    while (allocation_)
    {
        // Randomly selects a DOMINANT or CONTESTANT `Species`.
        theSpecies_ = this->random({DOMINANT, CONTESTANT}, ranks_);

        // Prompts the selected `Species` to spawn a new `Organism`.
        if (auto newOrganism_ = theSpecies_->spawn())
        {
            organisms.push_back(newOrganism_);
            --allocation_;
        }
    }

    return;
}

// Assigns spawned `Organism`s to new or existing `Species`.
void Genus::speciate()
{
    // A new `Species*`.
    Species* newSpecies_;

    // Purges all CONTESTANT parent `Organism`s.
    for (const auto& theSpecies_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        theSpecies_->purge({CONTESTANT});
    }

    // Assigns each spawned `Organism` to a new or existing `Species`.
    for (const auto& theOrganism_ : organisms)
    {
        for (const auto theSpecies_ : this->retrieve({CONTESTANT, DOMINANT}))
        {
            // Inserts the current `Organism` into a new or existing `Species*`.
            if (theSpecies_->organism_compatibility(theOrganism_))
            {
                theSpecies_->insert(theOrganism_);
                break;
            }
            else if (this->front(DOMINANT) == theSpecies_)
            {
                newSpecies_ = new Species(this, CONTESTANT, theOrganism_);
                this->insert(newSpecies_);
            }
        }
    }

    // Primes this `Genus` for a subsequent spawning round.
    organisms.clear();

    return;
}

// The criterion for rejecting a `Species*`.
bool Genus::species_rejection(Species* thatSpecies_)
{
    // This `Genus`' DOMINANT `Species*`.
    Species* thisSpecies_ = this->front(DOMINANT);

    // The input `Species*`' DOMINANT `Organism*`.
    Organism* thatOrganism_ = thatSpecies_->front(DOMINANT);

    // Rejects `Species*` which are stagnated.
    return thatOrganism_->age > stagnation_threshold && thatSpecies_ != thisSpecies_;
}

// The criterion for comparing two `Species*`.
bool Genus::species_comparison(Species* thatSpecies_, Species* thisSpecies_)
{
    // The input `Species*`' benchmark `Organism*`s.
    Organism* thatOrganism_ = thatSpecies_->front(DOMINANT);
    Organism* thisOrganism_ = thisSpecies_->front(DOMINANT);

    // Checks whether the two `Species*`' DOMINANT `Organism*`s possess the same score.
    if (thatOrganism_->score == thisOrganism_->score)
    {
        // Compares the DOMINANT `Organism*`s' sizes through the '<' operation.
        return thatOrganism_->genotype->size() < thisOrganism_->genotype->size();
    }
    else
    {
        // Compares the DOMINANT `Organism*`s' scores through the '>' operation.
        return thatOrganism_->score > thisOrganism_->score;
    }
}
