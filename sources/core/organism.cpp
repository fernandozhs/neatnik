#include "organism.hpp"


// Constructors:

Organism::Organism(Species* species_, GenotypeData genotype_data_)
{
    species = species_;

    group = CONTESTANT;

    phenotype = new Phenotype(this);

    genotype = new Genotype(this, genotype_data_);

    age = 0.;

    score = 0.;
}

Organism::Organism(Species* species_, OrganismData data_)
{
    species = species_;

    auto [group_, age_, score_, genotype_data_] = data_;

    group = group_;

    phenotype = new Phenotype(this);

    genotype = new Genotype(this, genotype_data_);

    age = age_;

    score = score_;
}

Organism::Organism(Organism* organism_)
{
    species = organism_->species;

    group = organism_->group;

    genotype = new Genotype(this, organism_->genotype);

    phenotype = new Phenotype(this);

    age = organism_->age;

    score = organism_->score;
}

Organism::Organism(OrganismData data_)
{
    species = nullptr;

    auto [group_, age_, score_, genotype_data_] = data_;

    group = group_;

    phenotype = new Phenotype(this);

    genotype = new Genotype(nullptr, genotype_data_);

    age = age_;

    score = score_;
}


// Destructor:

Organism::~Organism()
{
    delete genotype;

    delete phenotype;
}


// Methods:

Organism* Organism::mutate()
{
    Organism* offspring_ = new Organism(this);

    offspring_->genotype->mutate();

    offspring_->group = CONTESTANT;

    offspring_->age = 0;

    return offspring_;
}

Organism* Organism::assimilate(Organism* organism_)
{
    Organism* offspring_ = new Organism(this);

    offspring_->genotype->assimilate(organism_->genotype);

    offspring_->group = CONTESTANT;

    offspring_->age = 0;

    return offspring_;
}

pybind11::array_t<double> Organism::react()
{
    pybind11::array_t<double> stimuli_ = species->genus->experiment->stimuli;

    pybind11::buffer_info stimuli_buffer_ = stimuli_.request();

    pybind11::ssize_t N = stimuli_buffer_.shape[0];
    pybind11::ssize_t M = stimuli_buffer_.shape[1];
    pybind11::ssize_t K = stimuli_buffer_.shape[2];
    pybind11::ssize_t L = species->genus->experiment->output_counter;

    double* stimuli_data_ = static_cast<double*> (stimuli_buffer_.ptr);

    pybind11::array_t<double> reactions_ = pybind11::array_t<double> ({N, M, L});
    pybind11::buffer_info reactions_buffer_ = reactions_.request();
    double* reactions_data_ = static_cast<double*>(reactions_buffer_.ptr);

    phenotype->assemble();

    for (pybind11::ssize_t i = 0; i < N; i++)
    {
        for (pybind11::ssize_t j = 0; j < M; j++)
        {
            double* stimulus_begin_  = stimuli_data_  + (i * M * K + j * K);
            double* reactions_begin_ = reactions_data_ + (i * M * L + j * L);

            phenotype->activate(stimulus_begin_, reactions_begin_);

            phenotype->deactivate();
        }

        phenotype->discontinue();
    }

    return reactions_;
}

pybind11::array_t<double> Organism::react(pybind11::array_t<double> stimuli_)
{
    pybind11::ssize_t dimensions_ = stimuli_.ndim();

    if (dimensions_ != 3)
    {
        throw std::invalid_argument("Cannot set stimuli: the provided object must be three-dimensional.");
    }

    unsigned int input_counter_ = genotype->nodes->size({INPUT});
    unsigned int output_counter_ = genotype->nodes->size({OUTPUT});

    pybind11::buffer_info stimuli_buffer_ = stimuli_.request();

    pybind11::ssize_t N = stimuli_buffer_.shape[0];
    pybind11::ssize_t M = stimuli_buffer_.shape[1];
    pybind11::ssize_t K = stimuli_buffer_.shape[2];
    pybind11::ssize_t L = static_cast<pybind11::ssize_t>(output_counter_);

    double* stimuli_data_ = static_cast<double*> (stimuli_buffer_.ptr);

    pybind11::array_t<double> reactions_ = pybind11::array_t<double> ({N, M, L});
    pybind11::buffer_info reactions_buffer_ = reactions_.request();
    double* reactions_data_ = static_cast<double*>(reactions_buffer_.ptr);

    if (K != static_cast<pybind11::ssize_t>(input_counter_))
    {
        throw std::invalid_argument("Cannot react to stimuli: the number of stimuli does not match the number of input nodes.");
    }

    phenotype->assemble();

    for (pybind11::ssize_t i = 0; i < N; i++)
    {
        for (pybind11::ssize_t j = 0; j < M; j++)
        {
            double* stimulus_begin_  = stimuli_data_  + (i * M * K + j * K);
            double* reactions_begin_ = reactions_data_ + (i * M * L + j * L);

            phenotype->activate(stimulus_begin_, reactions_begin_);

            phenotype->deactivate();
        }

        phenotype->discontinue();
    }

    return reactions_;
}


OrganismData Organism::data() const
{
    OrganismData data_ (group, age, score, genotype->data());

    return data_;
}
