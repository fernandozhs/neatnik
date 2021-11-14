#include "stimuli.h"

// Constructor:

// ...
Stimuli::Stimuli(std::tuple<unsigned int, unsigned int> dimensions_)
{
    // ...
    dimensions = dimensions_;
}


// Destructor:

// ...
Stimuli::~Stimuli()
{
    // ...
}


// Methods:

// ...
void Stimuli::include(std::vector<std::vector<double>> feature_, std::vector<unsigned int> pattern_)
{
    // ...
    features.push_back(feature_);

    // ...
    patterns.push_back(pattern_);

    return;
}

// ...
bool Stimuli::next()
{
    // ...
    
}
