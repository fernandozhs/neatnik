#include "species.h"

// Constructor:

// Initializes this `Species` with `Organism`s characterized by minimal fully-connected `Genotype`s.
Species::Species(Genus* thatGenus_, taxon_group group_, std::vector<Archetype> thoseArchetypes_)
{
    // Assigns this `Species` to its taxon.
    genus = thatGenus_;

    // Assigns this `Species` to a group within its taxon.
    group = group_;

    // Creates `Organism`s characterized by minimal fully-connected `Genotype`s.
    for (const auto& thatArchetype_ : thoseArchetypes_)
    {
        // Initializes a new `Organism`.
        Organism* newOrganism_ = new Organism(this, thatArchetype_);

        // Adds the newly created `Organism` to this `Species`.
        this->insert(newOrganism_);
    }

    // Promotes a random `Organism` to this `Species`' DOMINANT group.
    Organism* thatOrganism_ = this->random({CONTESTANT});
    this->toggle(thatOrganism_, DOMINANT);
}

// Originates this `Species` from its first `Organism`.
Species::Species(Genus* thatGenus_, taxon_group group_, Organism* thatOrganism_)
{
    // Assigns this `Species` to its taxon.
    genus = thatGenus_;

    // Assigns this `Species` to a group within its taxon.
    group = group_;

    // Adds the input `Organism` to this `Species`.
    this->insert(thatOrganism_);

    // Promotes the input `Organism` to this `Species`' DOMINANT group.
    this->toggle(thatOrganism_, DOMINANT);
}


// Destructor:

// Recursive destructor responsible for deleting this `Species` and all its `Organism`s.
Species::~Species()
{
    // Deletes each `Organism` stored in this `Species`
    for (auto& theOrganism_ : this->retrieve())
    {
        delete theOrganism_;
    }
}


// Methods:

// Retrieves the total number of stored `Organism`s in the matching group(s).
int Species::size(const std::vector<int> groups_)
{
    // Initializes the return variable.
    int size_ = 0;

    // Sums the number of `Organism*`s in each group.
    for (const auto& group_ : groups_)
    {
        size_ += organisms[group_].size();
    }

    // Returns the number of stored `Organism`s.
    return size_;
}

// Retrieves an iterator at the beginning of a given group.
typename std::vector<Organism*>::iterator Species::begin(int group_)
{
    // Returns the iterator at the beginning of the matching group.
    return organisms[group_].begin();
}

// Retrieves an iterator at the end of a given group.
typename std::vector<Organism*>::iterator Species::end(int group_)
{
    // Returns the iterator at the end of the matching group.
    return organisms[group_].end();
}

// Retrieves the first `Organism*` of a given group.
Organism* Species::front(int group_)
{
    // Returns the first `Organism*` of the matching group.
    return organisms[group_].front();
}

// Retrieves the last `Organism*` of a given group.
Organism* Species::back(int group_)
{
    // Returns the last `Organism*` of the matching group.
    return organisms[group_].back();
}

// Inserts an `Organism*` into this `Species`.
Organism* Species::insert(Organism* thatOrganism_)
{
    // Extracts the input `Organism*`'s group.
    int group_ = thatOrganism_->group;

    // Assigns the input `Organism*` to this `Species`.
    thatOrganism_->species = this;

    // Inserts the input `Organism*` into this `Species`' matching group.
    organisms[group_].push_back(thatOrganism_);

    return thatOrganism_;
}

// Removes an `Organism*` from this `Species`.
Organism* Species::remove(Organism* thatOrganism_)
{
    // Extracts the input `Organism*`'s group.
    int group_ = thatOrganism_->group;

    // Locates the input `Organism*` in the matching group.
    auto location_ = std::find(this->begin(group_), this->end(group_), thatOrganism_);

    // Removes the input `Organism*` from this `Species`' matching group.
    organisms[group_].erase(location_);

    return thatOrganism_;
}

// Purges an `Organism*` from this `Species`.
void Species::purge(Organism* thatOrganism_)
{
    // Deletes and removes the input `Organism*` from this `Species`.
    delete this->remove(thatOrganism_);

    return;
}

// Purges all `Organism*`s from the matching group(s).
void Species::purge(const std::vector<int> groups_)
{
    // Deletes and removes all `Organism*`s from the matching group(s).
    for (const auto& theOrganism_ : this->retrieve(groups_))
    {
        delete theOrganism_;
    }

    // Clears the maching group(s).
    for (const auto& group_ : groups_)
    {
        organisms[group_].clear();
    }

    return;
}

// Toggles the group associated with the input `Organism*`.
void Species::toggle(Organism* thatOrganism_, int group_)
{
    // Removes the input `Organism*` from this `Species`.
    this->remove(thatOrganism_);

    // Updates the input `Organism*`'s group.
    thatOrganism_->group = (taxon_group)group_;

    // Re-inserts the `Organism*` into this `Species`.
    this->insert(thatOrganism_);

    return;
}

// Selects a random `Organism*` from the matching group(s).
Organism* Species::random(const std::vector<int> groups_, const std::vector<double> weights_)
{
    // Initializes auxiliary variable.
    int sample_;

    // Retrieves the number of stored `Organism`s in the matching group(s).
    int size_ = this->size(groups_);

    // Checks whether no matching `Organism*`s exist.
    if (size_ == 0)
    {
        // Returns `nullptr`.
        return nullptr;
    }

    // Decides which probability mass function to employ when sampling this `Species`' `Organism*`s.
    if (weights_.size() == 0)
    {
        // Samples an `Organism*` from a uniform probability mass function.
        sample_ = U(1, size_);
    }
    else
    {
        // Samples an `Organism*` from the input probability mass function.
        sample_ = P(weights_) + 1;
    }

    // Searches this `Species`' groups for the selected `Organism*`.
    for (const auto& group_ : groups_)
    {
        // Gets the corresponding integer labeling the start of the current group.
        size_ -= organisms[group_].size();

        // Checks whether the group containing the selected `Organism*` has been found.
        if (sample_ > size_)
        {
            // Returns the matching `Organism*`.
            return organisms[group_][sample_ - size_ - 1];
        }
    }

    // This line should never be reached.
    return nullptr;
}

// Retrieves all `Organism*`s from the matching group(s).
std::vector<Organism*> Species::retrieve(const std::vector<int> groups_)
{
    // Initializes and reserves the appropriate amount of memory for a `std::vector<Organism*>` which will store all the `Organism*`s from the matching group(s).
    std::vector<Organism*> thoseOrganisms_;
    thoseOrganisms_.reserve(this->size(groups_));

    // Concatenates all the relevant `Organism*`s.
    for (const auto& group_ : groups_)
    {
        thoseOrganisms_.insert(thoseOrganisms_.end(), this->begin(group_), this->end(group_));
    }

    // Returns the concatenated `Organism*`s.
    return thoseOrganisms_;
}

// Sorts all `Organism*`s from the matching group(s) according to their performance.
std::vector<Organism*> Species::sort(const std::vector<int> groups_)
{
    // Retrieves all `Organism*`s from the matching group(s).
    std::vector<Organism*> thoseOrganisms_ = this->retrieve(groups_);

    // Rearranges the collected `Organism*`s according to their comparison criterion.
    std::sort(thoseOrganisms_.begin(), thoseOrganisms_.end(), this->organism_comparison);

    // Returns the sorted `Organism*`s.
    return thoseOrganisms_;
}

// Finds the best performing `Organism` and purges a fraction of the remainder.
void Species::select()
{
    // Sorts all `Organism*`s stored in this `Species`.
    std::vector<Organism*> thoseOrganisms_ = this->sort();

    // Ensures the best performing `Organism` is up to date.
    if (this->front(DOMINANT) != thoseOrganisms_.front())
    {
        this->toggle(this->front(DOMINANT), CONTESTANT);
        this->toggle(thoseOrganisms_.front(), DOMINANT);
    }

    // The threshold beyond which `Organism`s are purged.
    auto threshold_ = ++thoseOrganisms_.begin() + this->size()*(1 - rejection_fraction);

    // Ages the threshold-clearing `Organism`s and purges the remainder.
    for (auto that_ = thoseOrganisms_.begin(); that_ != thoseOrganisms_.end(); ++that_)
    {
        if (that_ < threshold_)
        {
            (*that_)->age++;
        }
        else
        {
            this->purge(*that_);
        }
    }

    return;
}

// Attempts to issue a new `Organism`.
Organism* Species::spawn(int attempts_)
{
    // The parent `Organism*`s.
    Organism* thatOrganism_;
    Organism* thisOrganism_;

    // Selects the process by which a new `Organism` will be issued.
    auto process_ = P(spawning_organism, this->size({CONTESTANT}));

    // Attempts to issue a new `Organism` from this `Species`.
    while (attempts_--)
    {
        // Randomly chooses the parent `Organism`s.
        switch (process_)
        {
            case MUTATION:
                // MUTATION requires a single parent `Organism`.
                thatOrganism_ = this->random({DOMINANT, CONTESTANT});
                thisOrganism_ = nullptr;
                break;

            case ASSIMILATION:
                // ASSIMILATION requires two parent `Organism`s.
                thatOrganism_ = this->random({DOMINANT, CONTESTANT});
                thisOrganism_ = this->random({DOMINANT, CONTESTANT});
                break;

            default:
                // No other spawning process has been implemented.
                break;
        }

        // Makes sure the randomly selected `Organism`s satisfy certain consistency requirements.
        switch (process_)
        {
            case MUTATION:
                // No additional checks needed for reproduction through MUTATION.
                break;

            case ASSIMILATION:
                // Ensures the parent `Organism`s are not the same.
                if (thatOrganism_ == thisOrganism_)
                {
                    continue;
                }
                // Ensures the parent `Organism`s are correctly labeled for ASSIMILATION.
                if (this->organism_comparison(thatOrganism_, thisOrganism_))
                {
                    std::swap(thatOrganism_, thisOrganism_);
                }
                break;

            default:
                // No other spawning process has been implemented.
                break;
        }

        // Spawns a new `Organism` within this `Species`.
        switch (process_)
        {
            case MUTATION:
                // Spawns and returns a new `Organism` through mutation.
                return thatOrganism_->mutate();
                break;

            case ASSIMILATION:
                // Spawns and returns a new `Organism` through assimilation.
                return thatOrganism_->assimilate(thisOrganism_);
                break;

            default:
                // No other spawning process has been implemented.
                break;
        }
    }

    // All attempts to spawn a new `Organism` have failed.
    return nullptr;
}

// The compatibility criterion for `Organism*`s.
bool Species::organism_compatibility(Organism* thatOrganism_)
{
    // This `Species`' DOMINANT `Organism*`.
    Organism* thisOrganism_ = this->front(DOMINANT);

    // Selects compatible `Organism*`s.
    return thatOrganism_->genotype->compatibility(thisOrganism_->genotype) < compatibility_threshold;
}

// The comparison criterion for `Organism*`s.
bool Species::organism_comparison(Organism* thatOrganism_, Organism* thisOrganism_)
{
    // Checks whether the two `Organism*`s possess the same score.
    if (thatOrganism_->score == thisOrganism_->score)
    {
        // Compares the `Organism*`s' sizes through the '<' operation.
        return thatOrganism_->genotype->size() < thisOrganism_->genotype->size();
    }
    else
    {
        // Compares the `Organism*`s' scores through the '>' operation.
        return thatOrganism_->score > thisOrganism_->score;
    }
}
