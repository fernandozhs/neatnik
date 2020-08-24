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

// Tags a `Link` or `Node` with a new or existent identification tag.
std::pair<long int, unsigned int> Population::tag(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_)
{
    // Generates the search key associated with the `Link` or `Node` of interest.
    long int key_ = Key(role_, type_, in_tag_, out_tag_);

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
std::pair<long int, unsigned int> Population::log(long int key_)
{
    // Creates a new log.
    std::pair<long int, unsigned int> log_ (key_, tag_counter);

    // Increments the identification tag counter.
    tag_counter++;

    // Logs the new `Link` or `Node`.
    logbook.insert(log_);

    // Returns the newly created log entry.
    return log_;
}
