#include "experiment.hpp"


// Constructor:

Experiment::Experiment()
{

}


// Destructor:

Experiment::~Experiment()
{
    delete genus;
}


// Methods:

void Experiment::run()
{
    PRNG.seed(Parameters::random_seed);

    MPI_Init(nullptr, nullptr);

    MPI_Comm_size(MPI_COMM_WORLD, &MPI_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);

    MPI_counts.resize(MPI_size);
    MPI_displacements.resize(MPI_size);

    std::vector<Graph> graphs_ (Parameters::population_size, Graph(vertexes, edges));

    genus = new Genus(this, graphs_);

    for (int cycles_ = Parameters::generational_cycles; cycles_ >= 0; --cycles_)
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
