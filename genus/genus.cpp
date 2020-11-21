#include "genus.h"

// Constructor:

// Initializes this `Genus` with a batch containing a single `Species`.
Genus::Genus(Neatnik* thatNeatnik_, std::vector<Archetype> thoseArchetypes_)
{
    // Assigns this `Genus` to the pertinent `Neatnik`.
    neatnik = thatNeatnik_;

    // Initializes this `Genus`' `Group<Species>`.
    //species = new Group<Species>();

    // Initializes this `Genus`' starting `Species`.
    Species* newSpecies_ = new Species(this, thoseArchetypes_);

    // Inserts the starting `Species` into this `Genus`.
    Genus::species->insert(newSpecies_);

    // Promotes the starting `Species` to this `Genus`' DOMINANT batch.
    Genus::species->toggle(newSpecies_, DOMINANT);
}


// Destructor:

// Recursive destructor.
Genus::~Genus()
{
    // Deletes the `Group<Species>` which makes up this `Genus`.
    delete species;
}


// Methods:

// Spawns a new `Species` within this `Genus`.
Species* Genus::spawn(Organism* thatOrganism_)
{
    // Spawns a new CONTESTANT `Species` containing the input `Organism` alone.
    Species* newSpecies_ = new Species(this, thatOrganism_);

    // Inserts the new CONTESTANT `Species` into this `Genus`.
    return species->insert(newSpecies_);
}

// Spawns a new generation of `Organism`s within this `Genus`.
std::vector<Organism*> Genus::spawn_organisms()
{
    // Initializes the return `std::vector<Organism*>` and an auxiliary `std::vector<double>`.
    std::vector<Organism*> thoseOrganisms_;
    std::vector<double> weights_;

    // Extracts the weight of each `Species`.
    for (const auto& theSpecies_ : species->retrieve({DOMINANT, CONTESTANT}))
    {
        weights_.push_back(theSpecies_->score);
    }

    // Spawns a new generation of `Organism`s.
    while (thoseOrganisms_.size() != population_size)
    {
        // Randomly selects a DOMINANT or CONTESTANT `Species`.
        Species* theSpecies_ = species->random({DOMINANT, CONTESTANT}, weights_);

        // Prompts the selected `Species` to spawn a new CONTESTANT `Organism`.
        if (auto newOrganism_ = theSpecies_->spawn_organism())
        {
            thoseOrganisms_.push_back(newOrganism_);
        }
    }

    // Returns this `Genus`' new generation of `Organism`s.
    return thoseOrganisms_;
}

// Allocates a new generation of `Organism`s to new or existing `Species`.
void Genus::allocate_organisms()
{
    // Spawns a new generation of `Organism`'s.
    std::vector<Organism*> thoseOrganisms_ = this->spawn_organisms();

    // Removes and deletes all CONTESTANT `Organism`s belonging to this `Genus`' `Species`.
    for (const auto& theSpecies_ : species->retrieve({DOMINANT, CONTESTANT}))
    {
        for (const auto& theOrganism_ : theSpecies_->organisms->retrieve({CONTESTANT}))
        {
            delete theSpecies_->organisms->remove(theOrganism_);
        }
    }

    // Allocates each newly spawned `Organism` to a new or existing `Species`.
    for (const auto& theOrganism_ : thoseOrganisms_)
    {
        for (const auto& theSpecies_ : species->retrieve({DOMINANT, CONTESTANT}))
        {
            // Checks the current `Organism`'s compatibility to an existing `Species`.
            if (theSpecies_->organism_compatibility(theOrganism_))
            {
                // Allocates the current `Organism` to an existing `Species`.
                theSpecies_->organisms->insert(theOrganism_);
                break;
            }
            else if (theSpecies_ == species->back(CONTESTANT))
            {
                // Allocates the current `Organism` to a new `Species`.
                this->spawn(theOrganism_);
            }
        }
    }

    return;
}

// Sifts out the rejected `Species*`s from the matching batch(es).
void Genus::elect_species(const std::vector<int> batches_)
{
    // The candidate DOMINANT `Species`.
    Species* thisSpecies_;
    Species* thatSpecies_;

    // Retrieves the DOMINANT and CONTESTANT `Species`.
    std::vector<Species*> thoseSpecies_ = species->retrieve({DOMINANT, CONTESTANT});

    // Sifts out the rejected `Organism`s from each `Species`.
    for (const auto& theSpecies_ : thoseSpecies_)
    {
        theSpecies_->elect_organisms({DOMINANT, CONTESTANT});
    }

    // Partitions the collected `Species` according to their rejection criterion.
    auto partition_ = std::partition(thoseSpecies_.begin(), thoseSpecies_.end(), this->species_rejection);

    // Rearranges the collected `Species` according to their comparison criterion.
    std::partial_sort(thoseSpecies_.rbegin(), std::make_reverse_iterator(partition_), thoseSpecies_.rend(), this->species_comparison);

    // Updates each of the matching batch(es) to reflect the `Species` sifting.
    for (const auto& batch_ : batches_)
    {
        switch (batch_)
        {
            case DOMINANT:
                // Retrieves the candidate DOMINANT `Species`.
                thisSpecies_ = species->back(DOMINANT);
                thatSpecies_ = thoseSpecies_.back();

                // Ensures the DOMINANT `Species` is up to date.
                if (thatSpecies_ != thisSpecies_)
                {
                    species->toggle(thisSpecies_, CONTESTANT);
                    species->toggle(thatSpecies_, DOMINANT);
                }
                break;

            case CONTESTANT:
                // Ensures the sifted-out CONTESTANT `Species` are removed and deleted.
                for (auto thatSpecies_ = thoseSpecies_.begin(); thatSpecies_ != partition_; ++thatSpecies_)
                {
                    delete species->remove(*thatSpecies_);
                }
                break;

            default:
                // No other batches exist.
                break;
        }
    }

    return;
}

// The criterion for rejecting a `Species*`.
bool Genus::species_rejection(Species* thatSpecies_)
{
    // This `Genus`' DOMINANT `Species*`.
    Species* thisSpecies_ = species->front(DOMINANT);

    // The input `Species*`' DOMINANT `Organism*`.
    Organism* thatOrganism_ = thatSpecies_->organisms->front(DOMINANT);

    // Rejects `Species*` which are stagnated.
    return thatOrganism_->age > stagnation_threshold && thatSpecies_ != thisSpecies_;
}

// The criterion for comparing two `Species*`s.
bool Genus::species_comparison(Species* thatSpecies_, Species* thisSpecies_)
{
    // The input `Species*`s' benchmark `Organism*`s.
    Organism* thatOrganism_ = thatSpecies_->organisms->front(DOMINANT);
    Organism* thisOrganism_ = thisSpecies_->organisms->front(DOMINANT);

    // Checks whether the two `Species*`' DOMINANT `Organism*`s possess the same score.
    if (thatOrganism_->score == thisOrganism_->score)
    {
        // Compares the DOMINANT `Organism*`s' sizes through the '>' operation.
        return thatOrganism_->genotype->size() < thisOrganism_->genotype->size();
    }
    else
    {
        // Compares the DOMINANT `Organism*`s' scores through the '<' operation.
        return thatOrganism_->score > thisOrganism_->score;
    }
}
