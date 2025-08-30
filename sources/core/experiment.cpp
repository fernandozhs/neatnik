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

void Experiment::set(pybind11::array_t<double> stimuli_)
{
    const pybind11::ssize_t* shape_ = stimuli_.shape();
    pybind11::ssize_t dimensions_ = stimuli_.ndim();

    if (dimensions_ != 3)
    {
        std::cout << "Cannot set stimuli: the provided object must be three-dimensional." << std::endl << std::flush;
        return;
    }

    pybind11::ssize_t input_counter_ = shape_[2];

    if (genus != nullptr && input_counter_ != input_counter)
    {
        std::cout << "Cannot set stimuli: the number of stimuli does not match the number of input nodes in the population." << std::endl << std::flush;
        return;
    }
    else
    {
        input_counter = input_counter_;
        stimuli = stimuli_;
    }

    return;
}

void Experiment::set(GenotypeData data_)
{
    pybind11::ssize_t input_counter_ = 0;
    pybind11::ssize_t output_counter_ = 0;

    auto nodes_data_ = std::get<0>(data_);

    for (const auto& [tag_, state_, role_, activation_, source_tag_, target_tag_] : nodes_data_)
    {
        switch (role_)
        {
            case INPUT:
                input_counter_++;
                break;

            case OUTPUT:
                output_counter_++;
                break;

            default:
                break;
        }
    }

    if (stimuli.size() != 0 && input_counter_ != input_counter)
    {
        std::cout << "Cannot set population: the number of input nodes does not match the number of stimuli provided." << std::endl << std::flush;
        return;
    }
    else
    {
        input_counter = input_counter_;
        output_counter = output_counter_;
    }

    delete genus;

    std::vector<GenotypeData> genotypes_data_ (Parameters::population_size, data_);

    genus = new Genus(this, genotypes_data_);

    return;
}

void Experiment::set(GenusData data_)
{
    pybind11::ssize_t input_counter_ = 0;
    pybind11::ssize_t output_counter_ = 0;

    auto species_data_ = data_[0];
    auto organisms_data_ = std::get<2>(species_data_);
    auto genotype_data_ = std::get<3>(organisms_data_[0]);
    auto nodes_data_ = std::get<0>(genotype_data_);

    for (const auto& [tag_, state_, role_, activation_, source_tag_, target_tag_] : nodes_data_)
    {
        switch (role_)
        {
            case INPUT:
                input_counter_++;
                break;

            case OUTPUT:
                output_counter_++;
                break;

            default:
                break;
        }
    }

    if (stimuli.size() != 0 && input_counter_ != input_counter)
    {
        std::cout << "Cannot set population: the number of input nodes does not match the number of stimuli provided." << std::endl << std::flush;
        return;
    }
    else
    {
        input_counter = input_counter_;
        output_counter = output_counter_;
    }

    delete genus;

    genus = new Genus(this, data_);

    return;
}

void Experiment::initialize()
{
    int initialized_;

    MPI_Initialized(&initialized_);

    if (!initialized_)
    {
        MPI_Init(nullptr, nullptr);
    
        MPI_Comm_size(MPI_COMM_WORLD, &MPI_size);
        MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
    
        MPI_counts.resize(MPI_size);
        MPI_displacements.resize(MPI_size);
    }

    return;
}

void Experiment::finalize()
{
    int finalized_;

    MPI_Finalized(&finalized_);

    if (!finalized_)
    {
        MPI_Finalize();
    }

    return;
}

void Experiment::run()
{
    if (genus == nullptr)
    {
        std::cout << "Cannot run experiment: population has not been seeded." << std::endl << std::flush;
        return;
    }

    if (stimuli.size() == 0)
    {
        std::cout << "Cannot run experiment: no stimuli have been provided." << std::endl << std::flush;
        return;
    }

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
