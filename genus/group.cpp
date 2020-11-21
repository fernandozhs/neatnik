#include "group.h"

// Constructor:

// Initialization constructor responsible for creating an empty `Group`.
template <class O>
Group<O>::Group()
{
    // Initializes this `Group` without any `O*`s.
}


// Destructor:

// Recursive destructor responsible for deleting this `Group` and all its `O*`s.
template <class O>
Group<O>::~Group()
{
    // Deletes each `O` stored in this `Group`
    for (auto& theObject_ : this->retrieve())
    {
        delete theObject_;
    }
}


// Methods:

// Retrieves the total number of stored `O`s in the matching batch(es).
template <class O>
int Group<O>::size(const std::vector<int> batches_)
{
    // Initializes the return variable.
    int size_ = 0;

    // Sums the number of objects in each batch.
    for (const auto& batch_ : batches_)
    {
        size_ += objects[batch_].size();
    }

    // Returns the number of stored `O`s.
    return size_;
}

// Retrieves an iterator at the beginning of a given batch.
template <class O>
typename std::vector<O*>::iterator Group<O>::begin(int batch_)
{
    // Returns the iterator at the beginning of the matching batch.
    return objects[batch_].begin();
}

// Retrieves an iterator at the end of a given batch.
template <class O>
typename std::vector<O*>::iterator Group<O>::end(int batch_)
{
    // Returns the iterator at the end of the matching batch.
    return objects[batch_].end();
}

// Retrieves the first `O*` of a given batch.
template <class O>
O* Group<O>::front(int batch_)
{
    // Returns the first `O*` of the matching batch.
    return objects[batch_].front();
}

// Retrieves the last `O*` of a given batch.
template <class O>
O* Group<O>::back(int batch_)
{
    // Returns the last `O*` of the matching batch.
    return objects[batch_].back();
}

// Inserts an `O*` into this `Group`.
template <class O>
O* Group<O>::insert(O* thatObject_)
{
    // Extracts the input `O*`'s batch.
    int batch_ = thatObject_->batch;

    // Inserts the input `O*` into this `Group`'s matching batch.
    objects[batch_].push_back(thatObject_);

    return thatObject_;
}

// Removes an `O*` from this `Group`.
template <class O>
O* Group<O>::remove(O* thatObject_)
{
    // Extracts the input `O*`'s batch.
    int batch_ = thatObject_->batch;

    // Locates the input `O*` in the matching batch.
    auto location_ = std::find(this->begin(batch_), this->end(batch_), thatObject_);

    // Removes the input `O*` from this `Group`'s matching batch.
    objects[batch_].erase(location_);

    return thatObject_;
}

// Toggles the batch associated with the input `O*`.
template <class O>
void Group<O>::toggle(O* thatObject_, int batch_)
{
    // Removes the input `O*` from this `Group`.
    this->remove(thatObject_);

    // Updates the input `O*`'s batch.
    thatObject_->batch = (object_batch)batch_;

    // Re-inserts the `O*` into this `Group`.
    this->insert(thatObject_);

    return;
}

// Selects a random `O*` from the matching batch(es).
template <class O>
O* Group<O>::random(const std::vector<int> batches_, const std::vector<double> weights_)
{
    // Initializes auxiliary variable.
    int sample_;

    // Retrieves the number of stored `O`s in the matching batch(es).
    int size_ = this->size(batches_);

    // Checks whether no matching `O*`s exist.
    if (size_ == 0)
    {
        // Returns `nullptr`.
        return nullptr;
    }

    // Decides which probability mass function to employ when sampling this `Group`'s `O*`s.
    if (weights_.size() == 0)
    {
        // Samples an `O*` from a uniform probability mass function.
        sample_ = U(1, size_);
    }
    else
    {
        // Samples an `O*` from the input probability mass function.
        sample_ = P(weights_) + 1;
    }

    // Searches this `Group`'s batches for the selected `O*`.
    for (const auto& batch_ : batches_)
    {
        // Gets the corresponding integer labeling the start of the current batch.
        size_ -= objects[batch_].size();

        // Checks whether the batch containing the selected `O*` has been found.
        if (sample_ > size_)
        {
            // Returns the matching `O*`.
            return objects[batch_][sample_ - size_ - 1];
        }
    }

    // This line should never be reached.
    return nullptr;
}

// Retrieves all `O*`s from the matching batch(es).
template <class O>
std::vector<O*> Group<O>::retrieve(const std::vector<int> batches_)
{
    // Initializes and reserves the appropriate amount of memory for a `std::vector<O*>` which will store all the `O*`s from the matching batch(es).
    std::vector<O*> thoseObjects_;
    thoseObjects_.reserve(this->size(batches_));

    // Concatenates all the relevant `O*`s.
    for (const auto& batch_ : batches_)
    {
        thoseObjects_.insert(thoseObjects_.end(), this->begin(batch_), this->end(batch_));
    }

    // Returns the concatenated `O*`s.
    return thoseObjects_;
}
