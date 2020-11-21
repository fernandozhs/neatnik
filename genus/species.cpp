#include "species.h"

// Constructor:

// Initializes this `Species` with `Organism`s characterized by minimal fully-connected `Genotype`s.
Species::Species(Genus* thatGenus_, std::vector<Archetype> thoseArchetypes_)
{
    // Assigns this `Species` to the pertinent `Genus`.
    genus = thatGenus_;

    // Initializes this `Species`' `Group<Organism>`.
    organisms = new Group<Organism>();

    // Assigns this `Species` to the default batch.
    batch = CONTESTANT;

    // Creates `Organism`s characterized by minimal fully-connected `Genotype`s.
    for (const auto& thatArchetype_ : thoseArchetypes_)
    {
        // Initializes a new CONTESTANT `Organism`.
        Organism* newOrganism_ = new Organism(this, thatArchetype_);

        // Adds the newly created `Organism` to this `Species`.
        organisms->insert(newOrganism_);
    }

    // Promotes a random CONTESTANT `Organism` to this `Species`' DOMINANT batch.
    Organism* thatOrganism_ = organisms->random({CONTESTANT});
    organisms->toggle(thatOrganism_, DOMINANT);
}

// Spawns this `Species` from a single `Organism`.
Species::Species(Genus* thatGenus_, Organism* thatOrganism_)
{
    // Assigns this `Species` to the pertinent `Genus`.
    genus = thatGenus_;

    // Initializes this `Species`' `Group<Organism>`.
    organisms = new Group<Organism>();

    // Assigns this `Species` to the default batch.
    batch = CONTESTANT;

    // Adds the input `Organism` to this `Species`.
    organisms->insert(thatOrganism_);

    // Promotes the input `Organism` to this `Species`' DOMINANT batch.
    organisms->toggle(thatOrganism_, DOMINANT);
}


// Destructor:

// Recursive destructor.
Species::~Species()
{
    // Deletes the `Group<Organism>` which makes up this `Species`.
    delete organisms;
}


// Methods:

// Spawns a new `Organism` within this `Species`.
Organism* Species::spawn(Organism* thatOrganism_)
{
    // Spawns a new `Organism` through mutation.
    Organism* newOrganism_ = thatOrganism_->mutate();

    // Inserts the new `Organism` into this `Species`.
    return organisms->insert(newOrganism_);
}

// Spawns a new `Organism` within this `Species`.
Organism* Species::spawn(Organism* thatOrganism_, Organism* thisOrganism_)
{
    // Spawns a new `Organism` through assimilation.
    Organism* newOrganism_ = thatOrganism_->assimilate(thisOrganism_);

    // Inserts the new `Organism` into this `Species`.
    return organisms->insert(newOrganism_);
}

// Attempts to spawn a new `Organism` within this `Species`.
Organism* Species::spawn_organism(int attempts_)
{
    // The parent `Organism`s.
    Organism* thatOrganism_;
    Organism* thisOrganism_;

    // Selects the process by which a new `Organism` will be added.
    auto process_ = P(spawning_organism, organisms->size({CONTESTANT}));

    // Attempts to produce a new `Organism` within this `Species`.
    while (attempts_--)
    {
        // Randomly chooses the parent `Organism`s.
        switch (process_)
        {
            case MUTATION:
                // MUTATION requires a single parent `Organism`.
                thatOrganism_ = organisms->random({DOMINANT, CONTESTANT});
                thisOrganism_ = nullptr;
                break;

            case ASSIMILATION:
                // ASSIMILATION requires two parent `Organism`s.
                thatOrganism_ = organisms->random({DOMINANT, CONTESTANT});
                thisOrganism_ = organisms->random({DOMINANT, CONTESTANT});
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
                return this->spawn(thatOrganism_);
                break;

            case ASSIMILATION:
                // Spawns and returns a new `Organism` through assimilation.
                return this->spawn(thatOrganism_, thisOrganism_);
                break;

            default:
                // No other spawning process has been implemented.
                break;
        }
    }

    // All attempts to spawn a new `Organism` have failed.
    return nullptr;
}


// Sifts out the rejected `Organism*`s from the matching batch(es).
void Species::elect_organisms(const std::vector<int> batches_)
{
    // The candidate DOMINANT `Organism`s.
    Organism* thisOrganism_;
    Organism* thatOrganism_;

    // Retrieves the DOMINANT and CONTESTANT `Organism`s in this `Species`.
    std::vector<Organism*> thoseOrganisms_ = organisms->retrieve({DOMINANT, CONTESTANT});

    // Partitions the collected `Organism`s according to the rejection fraction.
    auto partition_ = thoseOrganisms_.rbegin() + thoseOrganisms_.size()*rejection_fraction;

    // Rearranges the collected `Organism`s according to their comparison criterion.
    std::partial_sort(thoseOrganisms_.rbegin(), partition_, thoseOrganisms_.rend(), this->organism_comparison);

    // Updates each of the matching batch(es) to reflect the `Organism` sifting.
    for (const auto& batch_ : batches_)
    {
        switch (batch_)
        {
            case DOMINANT:
                // Retrieves candidate DOMINANT `Organism`s.
                thisOrganism_ = organisms->back(DOMINANT);
                thatOrganism_ = thoseOrganisms_.back();

                // Ensures the DOMINANT `Organism` is up to date.
                if (thatOrganism_ != thisOrganism_)
                {
                    organisms->toggle(thisOrganism_, CONTESTANT);
                    organisms->toggle(thatOrganism_, DOMINANT);
                }
                break;

            case CONTESTANT:
                // Ensures the sifted-out CONTESTANT `Organism`s are removed and deleted.
                for (auto thatOrganism_ = partition_; thatOrganism_ != thoseOrganisms_.rend(); ++thatOrganism_)
                {
                    delete organisms->remove(*thatOrganism_);
                }
                break;

            default:
                // No other batches exist.
                break;
        }
    }

    return;
}

// The compatibility criterion for `Organism*`s.
bool Species::organism_compatibility(Organism* thatOrganism_)
{
    // This `Species`' DOMINANT `Organism*`.
    Organism* thisOrganism_ = organisms->front(DOMINANT);

    // Selects compatible `Organism*`s.
    return thatOrganism_->genotype->compatibility(thisOrganism_->genotype) < compatibility_threshold;
}

// The comparison criterion for `Organism*`s.
bool Species::organism_comparison(Organism* thatOrganism_, Organism* thisOrganism_)
{
    // Checks whether the two `Organism*`s possess the same score.
    if (thatOrganism_->score == thisOrganism_->score)
    {
        // Compares the `Organism*`s' sizes through the '>' operation.
        return thatOrganism_->genotype->size() < thisOrganism_->genotype->size();
    }
    else
    {
        // Compares the `Organism*`s' scores through the '<' operation.
        return thatOrganism_->score > thatOrganism_->score;
    }
}
