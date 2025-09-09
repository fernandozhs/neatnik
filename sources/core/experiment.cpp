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
        throw std::invalid_argument("Cannot set stimuli: the provided object must be three-dimensional.");
    }

    pybind11::ssize_t input_counter_ = shape_[2];

    if (genus != nullptr && input_counter_ != input_counter)
    {
        throw std::invalid_argument("Cannot set stimuli: the number of stimuli does not match the number of input nodes in the population.");
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
        throw std::invalid_argument("Cannot set population: the number of input nodes does not match the number of stimuli provided.");
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
        throw std::invalid_argument("Cannot set population: the number of input nodes does not match the number of stimuli provided.");
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
    
        MPI_counts.resize(MPI_size, 0);
        MPI_displacements.resize(MPI_size, 0);
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
        throw std::runtime_error("Cannot run experiment: population has not been seeded.");
    }

    if (stimuli.size() == 0)
    {
        throw std::runtime_error("Cannot run experiment: no stimuli have been provided.");
    }

    for (int cycles_ = Parameters::generational_cycles; cycles_ > 0; --cycles_)
    {
        if (MPI_rank == 0)
        {
            this->display();
        }

        this->execute();

        genus->spawn();

        genus->speciate();

        this->score();

        genus->select();
    }

    return;
}

void Experiment::score()
{
    std::vector<Organism*> organisms_;
    std::vector<double> scores_;

    if (Parameters::statistical_scoring)
    {
        for (const auto& species_ : genus->retrieve({DOMINANT, CONTESTANT}))
        {
            Organism* organism_ = species_->front(DOMINANT);
    
            organisms_.push_back(organism_);
        }
    }
    organisms_.insert(organisms_.end(), genus->offsprings.begin(), genus->offsprings.end());

    int allocation_ = organisms_.size();
    scores_.resize(allocation_, 0.);

    std::fill(MPI_counts.begin(), MPI_counts.end() - allocation_%MPI_size, allocation_/MPI_size);
    std::fill(MPI_counts.end() - allocation_%MPI_size, MPI_counts.end(), allocation_/MPI_size + 1);
    std::partial_sum(MPI_counts.begin(), MPI_counts.end() - 1, MPI_displacements.begin() + 1);

    for (int index_ = MPI_displacements[MPI_rank]; index_ != MPI_displacements[MPI_rank] + MPI_counts[MPI_rank]; ++index_)
    {
        Organism* organism_ = organisms_[index_];

        scores_[index_] = this->fitness(organism_);
    }

    MPI_Allgatherv(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, scores_.data(), MPI_counts.data(), MPI_displacements.data(), MPI_DOUBLE, MPI_COMM_WORLD);

    for (int index_ = 0; index_ != allocation_; ++index_)
    {
        organisms_[index_]->score = scores_[index_];
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

void Experiment::execute()
{
    return;
}