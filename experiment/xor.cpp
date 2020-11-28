#include "xor.h"

// Methods:

// Evaluates the performance of the input `Organism`.
double XOR::evaluate(Organism* thatOrganism_)
{
    // Initializes the return variables.
    double score_ = 4.;

    // Assembles the input `Organism`'s `Phenotype`.
    thatOrganism_->phenotype->assemble();

    // Defines the target behavior to be evolved by this `Experiment`.
    std::vector<std::tuple<std::vector<double>, double>> target_ {{{1., 0., 0.}, 0.}, {{1., 1., 0.}, 1.}, {{1., 0., 1.}, 1.}, {{1., 1., 1.}, 0.}};

    // Assesses the behavior of the input `Organism`'s `Phenotype`.
    for (const auto& [input_, output_] : target_)
    {
        // Activates the `Phenotype`.
        thatOrganism_->phenotype->activate(input_);

        // Evaluates the `Phenotype`'s performance.
        score_ -= std::abs(thatOrganism_->phenotype->output.back() - output_);
    }

    // Computes the input `Organism`'s score based on its `Phenotype` performance.
    //score_ = std::pow(4. - score_, 2);

    // Returns the input `Organism`'s score.
    return score_;
}
