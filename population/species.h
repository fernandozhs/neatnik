/*
  A `Species` ...

  Data:
  ----
  organisms: a `std::vector<Organism*>` listing all `Organism`s belonging to this `Species`.
  ...

  Constructors:
  ------------
  ...

  Methods:
  -------
  ...
*/

#pragma once

#include <vector>
#include "../neatnik/neatnik.h"
#include "../organism/organism.h"

class Species
{
private:

    // Data:

    // The `Population` to which this `Species` belongs.
    Population* population;

    // The best scoring `Organism*` to ever arise in this `Species`.
    Organism* paragon;

    // The collection of `Organism*`s belonging to this `Species`.
    std::vector<Organism*> organisms;

    // A measure of this `Species`' average performance with respect to a given metric.
    double score = 0.;


public:

    // Constructor:

    // Initialization constructor.
    Species()
    {
        
    }


    // Methods:

    // Ranks this `Species`' performance with respect to a given metric.
    void rank()
    {
        // Resets this `Species`' score.
        score = 0.;

        // Ranks each `Organism` in this `Species`.
        for (const auto& theOrganism_ : organisms)
        {
            // Scores the current `Organism`.
            theOrganism_->rank();

            // Computes this `Species`' aggregate score.
            score += theOrganism_->score;
        }

        // Scores this `Species` with the average of its `Organism`'s scores.
        score /= organisms.size();

        return;
    }


    // Sorts this `Species`' `Organism*`s according to their scores.
    void sort()
    {
        // Rearranges all `Organism*`s so as to sort their scores in descending order.
        std::sort(organisms.begin(), organisms.end(), [](const Organism* this_, const Organism* that_){return *this_ > *that_;});

        return;
    }

    // Randomly shuffles this `Species`' `Organism*`s.
    void shuffle()
    {
        // Seeds the random number generator.
        std::random_device seed;

        // Randomly shuffles this `Species`' `Organism*`s.
        std::shuffle(organisms.begin(), organisms.end(), std::mt19937(seed()));

        return;
    }

    // Partitions this `Species`' `Organism*`s according to a given threshold.
    int partition(int threshold_ = threshold)
    {
        // The bound within which the `Organism`s with threshold-clearing scores are confined.
        auto bound_ = std::partition(organisms.begin(), organisms.end(), [&](const Organism* this_){return this_->score > threshold_*score;});

        // Returns the number of `Organism`s with threshold-clearing scores.
        return std::distance(organisms.begin(), bound_);
    }

    // Enlarges the number of `Organism`s allocated to this `Species`.
    void enlarge(int allocation_)
    {
        // Copies this `Species`' `Organism`s in their current order until the new allocation is reached.
        for (auto this_ = organisms.begin(); organisms.size() != allocation_; this_++)
        {
            organisms.push_back(new Organism(*this_));
        }

        return;
    }

    // Shortens the number of `Organism`s allocated to this `Species`.
    void shorten(int allocation_)
    {
        // Discards this `Species`' `Organism`s in reverse order until the new allocation is reached.
        for (auto this_ = organisms.rend(); organisms.size() != allocation_; this_++)
        {
            delete *this_;
            organisms.pop_back();
        }

        return;
    }

    // Retains the `Organism`s with threshold-clearing scores.
    void retain()
    {
        // Groups the `Organism`s with threshold-clearing scores.
        int allocation_ = this->partition(int threshold_);

        // Discards the `Organism`s with sub-threshold scores.
        this->shorten(allocation_);

        return;
    }

    // Ensures the
    void allocate(int allocation_)
    {
        // Retains the `Organism`s with threshold-clearing scores.
        this->retain();

        // Adjusts this `Species`' allocation.
        if (organisms.size() < allocation_)
        {
            // Shuffles.
            this->shuffle();

            this->enlarge(allocation_);
        }
        else
        {
            // Sorts.
            this->sort();

            this->shorten(allocation_);
        }

        return;
    }

    //
    void breed(int allocation_)
    {
        //
    }

    // Retains the `Organism`s with threshold-clearing scores.
    void retain()
    {
        // Separates the `Organism`s with threshold-clearing scores.
        std::partition(organisms.begin(), organisms.end(), [&](const Organism* this_){return this_->score > threshold*score;})

        // The separation point.
        auto point_ = std::partition_point(organisms.begin(), organisms.end(), [&](const Organism* this_){return this_->score > threshold*score;})

        // Discards the `Organism`s with sub-threshold scores.
        while (point_ != organisms.end())
        {
            delete *organisms.end();
            organisms.pop_back();
        }

        return;
    }
};
