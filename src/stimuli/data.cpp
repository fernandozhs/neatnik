#include "data.hpp"

// Constructor:

// ...
Feature::Data(std::vector<std::vector<double>>::iterator series_, std::vector<unsigned int> lags_)
{
    // ...
    series = series_;

    // ...
    lags = lags_;

    // ...
    indicator = series_->begin();
}


// Destructor:

// ...
Data::~Data()
{
    // ...
}


// Methods:

// ...


// ...
std::vector<double> Data::feature()
{
    // ...
    std::vector<double> feature_;
    feature_.reserve(lags->size());

    // ...
    for (const auto& lag_ : lags)
    {
        // ...
        sample_ = *std::next(indicator, lag_);

        // ...
        feature_.push_back(sample_);
    }

    // ...
    return feature_;
}
