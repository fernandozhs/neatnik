#include "experiment.hpp"


// Constructor:

Experiment::Experiment()
{
    PRNG.seed(Parameters::random_seed);
}


// Destructor:

Experiment::~Experiment()
{
    delete genus;
}


// Methods:

void Experiment::set(std::vector<std::vector<std::vector<double>>> stimuli_)
{
    stimuli = stimuli_;

    return;
}

void Experiment::set(GenotypeData data_)
{
    delete genus;

    std::vector<GenotypeData> genotypes_data_ (Parameters::population_size, data_);

    genus = new Genus(this, genotypes_data_);

    return;
}

void Experiment::set(GenusData data_)
{
    delete genus;

    genus = new Genus(this, data_);

    return;
}

void Experiment::run()
{
    MPI_Init(nullptr, nullptr);

    MPI_Comm_size(MPI_COMM_WORLD, &MPI_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);

    MPI_counts.resize(MPI_size);
    MPI_displacements.resize(MPI_size);

    for (int cycles_ = Parameters::generational_cycles; cycles_ > 0; --cycles_)
    {
        if (MPI_rank == 0)
        {
            this->display();
        }

        genus->spawn();

        genus->speciate();

        this->score();

        genus->select();
    }

    MPI_Finalize();

    return;
}

void Experiment::score()
{
    int allocation_ = genus->offsprings.size();

    std::fill(MPI_counts.begin(), MPI_counts.end() - allocation_%MPI_size, allocation_/MPI_size);

    std::fill(MPI_counts.end() - allocation_%MPI_size, MPI_counts.end(), allocation_/MPI_size + 1);

    std::partial_sum(MPI_counts.begin(), MPI_counts.end() - 1, MPI_displacements.begin() + 1);

    for (int index_ = MPI_displacements[MPI_rank]; index_ != MPI_displacements[MPI_rank] + MPI_counts[MPI_rank]; ++index_)
    {
        Organism* offspring_ = genus->offsprings[index_];

        genus->scores[index_] = this->fitness(offspring_);
    }

    MPI_Allgatherv(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, genus->scores.data(), MPI_counts.data(), MPI_displacements.data(), MPI_DOUBLE, MPI_COMM_WORLD);

    for (int index_ = 0; index_ != allocation_; ++index_)
    {
        genus->offsprings[index_]->score = genus->scores[index_];
    }

    for (const auto& species_ : genus->retrieve({DOMINANT, CONTESTANT}))
    {
        species_->rank = species_->front(DOMINANT)->score;

        for (const auto& organism_ : species_->retrieve({CONTESTANT}))
        {
            species_->rank += organism_->score;
        }

        species_->rank /= species_->size({DOMINANT, CONTESTANT});
    }

    return;
}

void Experiment::display()
{
    return;
}
