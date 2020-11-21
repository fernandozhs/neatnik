#include "neatnik.h"

// Constructor:

// Initializes `Neatnik`.
Neatnik::Neatnik(Experiment* experiment_, std::vector<Archetype> thoseArchetypes_)
{
    // Sets the `Experiment` responsible for driving evolution.
    experiment = experiment_;

    // Sets the `Genus` to undergo evolution.
    genus = new Genus(this, thoseArchetypes_);
}


// Methods:

// Tags a `Link` or `Node` with a new or existent identification tag.
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
    std::pair<long int, unsigned int> log_ (key_, tag_counter);

    // Increments the identification tag counter.
    tag_counter++;

    // Logs the new `Link` or `Node`.
    logbook.insert(log_);

    // Returns the newly created log entry.
    return log_;
}
