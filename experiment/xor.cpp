#include "xor.h"

// Constructor:

// Initializes this `XOR` `Experiment`.
XOR::XOR(Genus* thatGenus_) : Experiment(thatGenus_)
{

}


// Methods:

// Scores the performance of the input `Phenotype`.
double XOR::performance(Phenotype* thatPhenotype_)
{
    // Initializes the return variables.
    double score_ = 4.;

    // Assembles the input `Phenotype`.
    thatPhenotype_->assemble();

    // Defines the target behavior to be evolved by this `Experiment`.
    std::vector<std::tuple<std::vector<double>, double>> target_ {{{1., 0., 0.}, 0.}, {{1., 1., 0.}, 1.}, {{1., 0., 1.}, 1.}, {{1., 1., 1.}, 0.}};

    // Assesses the behavior of the input `Phenotype`.
    for (const auto& [input_, output_] : target_)
    {
        // Activates the input `Phenotype`.
        thatPhenotype_->activate(input_);

        // Evaluates the input `Phenotype`'s performance.
        score_ -= std::fabs(thatPhenotype_->output.back() - output_);

        // Deactivates the input `Phenotype`.
        thatPhenotype_->deactivate();
    }

    // Returns the input `Phenotype`'s performance score.
    return score_;
}
