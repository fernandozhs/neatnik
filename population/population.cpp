#include "population.h"

// Constructor:

// Initializates this `Population` with `Organism`s characterized by minimal fully-connected `Genotype`s.
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
Innovation* Population::tag(element_type type_, unsigned int in_tag_, unsigned int out_tag_)
{
    // Searches for a matching `Innovation` in this `Population`'s genetic history.
    auto match_ = history.find(this->key(type_, in_tag_, out_tag_));

    // Checks whether a match has been found.
    if (match_ != history.end())
    {
        // Returns the matching `Innovation*`.
        return match_->second;
    }

    // In case no match has been found, a new `Innovation` entry is logged.
    Innovation* innovation_ = this->log(type_, in_tag_, out_tag_);

    // The newly created `Innovation*` is returned.
    return innovation_;
}

// Logs a new `Innovation`.
Innovation* Population::log(element_type type_, unsigned int in_tag_, unsigned int out_tag_)
{
    // Creates a new `Innovation` of the input type.
    Innovation* innovation_ = new Innovation(type_, in_tag_, out_tag_, innovation_counter);

    // Increments the innovation counter.
    innovation_counter++;

    // Logs the newly created `Innovation`.
    history[this->key(type_, in_tag_, out_tag_)] = innovation_;

    return innovation_;
}

// Generates an `Innovation`'s unique identification key.
long int Population::key(element_type type_, unsigned int in_tag_, unsigned int out_tag_)
{
    // Returns the unique key.
    return ((long int)type_ << 63 | (long int)in_tag_ << 31 | (long int)out_tag_);
}
