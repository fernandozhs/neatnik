#include "neatnik.h"
#include <iostream>

// Constructor:

// Initializes `Neatnik`.
Neatnik::Neatnik(Experiment* thatExperiment_, std::vector<Archetype> thoseArchetypes_)
{
    // Sets the `Experiment` responsible for driving evolution.
    experiment = thatExperiment_;

    // Sets the `Genus` to undergo evolution.
    genus = new Genus(this, thoseArchetypes_);
}


// Methods:

// Tags a `Species` with a new identification tag.
unsigned int Neatnik::tag()
{
    // Increments the identification tag counter.
    species_counter++;

    // Returns the new tag.
    return species_counter;
}

// Tags a `Link` or `Node` with a new or existing identification tag.
std::pair<long int, unsigned int> Neatnik::tag(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_)
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
std::pair<long int, unsigned int> Neatnik::log(long int key_)
{
    // Creates a new log.
    std::pair<long int, unsigned int> log_ (key_, element_counter);

    // Increments the identification tag counter.
    element_counter++;

    // Logs the new `Link` or `Node`.
    logbook.insert(log_);

    // Returns the newly created log entry.
    return log_;
}

// Evolves the `Genus` through a single generational cycle.
void Neatnik::evolve()
{
    std::cout << "Evaluate" << std::endl;
    // Scores the `Genus` according to its performance.
    experiment->evaluate(genus);

    std::cout << "Elect" << std::endl;
    // Sifts out the rejected `Species`s.
    genus->elect_species({DOMINANT, CONTESTANT});

    std::cout << "Spawn" << std::endl;
    // Spawns new generation of `Organism`s and allocates them to new or existing `Species`.
    auto orgs = genus->spawn_organisms();

    std::cout << "Allocate" << std::endl;
    // Spawns new generation of `Organism`s and allocates them to new or existing `Species`.
    genus->allocate_organisms(orgs);

    return;
}
