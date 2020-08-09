#include "population.h"

// Constructor:

// Initialization from an `archetype`.
Population::Population(std::vector<Archetype> thoseArchetypes_)
{
    // Creates `Organism`s characterized by minimal fully-connected `Genotype`s.
    for (const auto& thatArchetype_ : thoseArchetypes_)
    {
        // Initializes a new `Organism`.
        Organism* newOrganism_ = new Organism(this, thatArchetype_);

        // Adds the newly created `Organism` to this `Population`.
        organisms.push_back(newOrganism_);
    }
}


// Methods:

// Tags a `Link` or `Node` with a new or existent `Innovation`.
Innovation* Population::tag(element_type type_, int in_tag_, int out_tag_)
{
    // Searches for a matching `Innovation` in this `Population`'s genetic history.
    for (const auto& innovation_ : history)
    {
        // Checks whether a match has been found.
        if (innovation_->in_tag == in_tag_ && innovation_->out_tag == out_tag_ && innovation_->type == type_)
        {
            // Returns the matching `Innovation`.
            return innovation_;
        }
    }

    // In case no match is found, a new `Innovation` entry is logged.
    Innovation* innovation_ = this->log(type_, in_tag_, out_tag_);

    // The newly created `Innovation` is returned.
    return innovation_;
}

// Logs a new `Innovation`.
Innovation* Population::log(element_type type_, int in_tag_, int out_tag_)
{
    // Creates a new `Innovation` of the input type.
    Innovation* innovation_ = new Innovation(type_, in_tag_, out_tag_, innovation_counter);

    // Increments the innovation counter.
    innovation_counter++;

    // Logs the newly created `Innovation`.
    history.push_back(innovation_);

    return innovation_;
}
