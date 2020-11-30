#include "xor.h"

// Methods:

// Scores the performance of the input `Phenotype`.
double XOR::performance(Phenotype* thatPhenotype_)
{
    // Initializes the return variables.
    double score_ = 4.;

    // Assembles the input `Organism`'s `Phenotype`.
    thatPhenotype->assemble();

    // Defines the target behavior to be evolved by this `Experiment`.
    std::vector<std::tuple<std::vector<double>, double>> target_ {{{1., 0., 0.}, 0.}, {{1., 1., 0.}, 1.}, {{1., 0., 1.}, 1.}, {{1., 1., 1.}, 0.}};

    // Assesses the behavior of the input `Organism`'s `Phenotype`.
    for (const auto& [input_, output_] : target_)
    {
        // Activates the input `Phenotype`.
        thatPhenotype->activate(input_);

        // Evaluates the input `Phenotype`'s performance.
        score_ -= std::abs(thatPhenotype->output.back() - output_);
    }

    // Scores the input `Phenotype`'s performance.
    //score_ = std::pow(4. - score_, 2);

    // Returns the input `Phenotype`'s performance score.
    return score_;
}
