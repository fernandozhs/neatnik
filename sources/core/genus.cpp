#include "genus.hpp"


// Constructor:

Genus::Genus(Experiment* experiment_, std::vector<Graph> graphs_)
{
    experiment = experiment_;

    Species* species_ = new Species(this, DOMINANT, graphs_);

    this->insert(species_);
}


// Destructor:

Genus::~Genus()
{
    for (auto& species_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        delete species_;
    }
}


// Methods:

std::pair<unsigned long int, unsigned int> Genus::tag(unsigned int role_, element_type type_, unsigned int source_tag_, unsigned int target_tag_)
{
    unsigned long int key_ = Key(role_, type_, source_tag_, target_tag_);

    auto match_ = logbook.find(key_);

    if (match_ != logbook.end())
    {
        return *match_;
    }
    else
    {
        return this->log(key_);
    }
}

std::pair<unsigned long int, unsigned int> Genus::log(unsigned long int key_)
{
    std::pair<unsigned long int, unsigned int> log_ (key_, tag_counter);

    tag_counter++;

    logbook.insert(log_);

    return log_;
}

unsigned int Genus::size(const std::vector<int> groups_)
{
    unsigned int size_ = 0;

    for (const auto& group_ : groups_)
    {
        size_ += species[group_].size();
    }

    return size_;
}

typename std::vector<Species*>::iterator Genus::begin(int group_)
{
    return species[group_].begin();
}

typename std::vector<Species*>::iterator Genus::end(int group_)
{
    return species[group_].end();
}

Species* Genus::front(int group_)
{
    return species[group_].front();
}

Species* Genus::back(int group_)
{
    return species[group_].back();
}

Species* Genus::insert(Species* species_)
{
    int group_ = species_->group;

    species_->genus = this;

    species[group_].push_back(species_);

    return species_;
}

Species* Genus::remove(Species* species_)
{
    int group_ = species_->group;

    auto location_ = std::find(this->begin(group_), this->end(group_), species_);

    species[group_].erase(location_);

    return species_;
}

void Genus::purge(Species* species_)
{
    delete this->remove(species_);

    return;
}

void Genus::purge(const std::vector<int> groups_)
{
    for (const auto& species_ : this->retrieve(groups_))
    {
        delete species_;
    }

    for (const auto& group_ : groups_)
    {
        species[group_].clear();
    }

    return;
}

void Genus::toggle(Species* species_, int group_)
{
    this->remove(species_);

    species_->group = (taxon_group)group_;

    this->insert(species_);

    return;
}

Species* Genus::random(const std::vector<int> groups_, const std::vector<double> weights_)
{
    unsigned int sample_;

    unsigned int size_ = this->size(groups_);

    if (size_ == 0)
    {
        return nullptr;
    }

    if (weights_.size() == 0)
    {
        sample_ = U(1, size_);
    }
    else
    {
        sample_ = P(weights_) + 1;
    }

    for (const auto& group_ : groups_)
    {
        size_ -= species[group_].size();

        if (sample_ > size_)
        {
            return species[group_][sample_ - size_ - 1];
        }
    }

    return nullptr;
}

std::vector<Species*> Genus::retrieve(const std::vector<int> groups_)
{
    std::vector<Species*> species_;
    species_.reserve(this->size(groups_));

    for (const auto& group_ : groups_)
    {
        species_.insert(species_.end(), this->begin(group_), this->end(group_));
    }

    return species_;
}

std::vector<Species*> Genus::sort(const std::vector<int> groups_)
{
    std::vector<Species*> species_ = this->retrieve(groups_);

    std::sort(species_.begin(), species_.end(), this->species_comparison);

    return species_;
}

void Genus::select()
{
    for (const auto& species_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        species_->select();
    }

    std::vector<Species*> species_ = this->sort();

    if (this->front(DOMINANT) != species_.front())
    {
        this->toggle(this->front(DOMINANT), CONTESTANT);
        this->toggle(species_.front(), DOMINANT);
    }

    for (auto that_ = ++species_.begin(); that_ != species_.end(); ++that_)
    {
        if (this->species_rejection(*that_))
        {
            this->purge(*that_);
        }
    }

    return;
}

void Genus::spawn()
{
    Species* species_;
    std::vector<double> ranks_;

    int allocation_ = Parameters::population_size;

    for (const auto& species_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        ranks_.push_back(species_->rank);
        --allocation_;
    }

    while (allocation_)
    {
        species_ = this->random({DOMINANT, CONTESTANT}, ranks_);

        if (auto offspring_ = species_->spawn())
        {
            organisms.push_back(offspring_);
            --allocation_;
        }
    }

    return;
}

void Genus::speciate()
{
    Species* branch_;

    for (const auto& species_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        species_->purge({CONTESTANT});
    }

    for (const auto& organism_ : organisms)
    {
        for (const auto species_ : this->retrieve({CONTESTANT, DOMINANT}))
        {
            if (species_->organism_compatibility(organism_))
            {
                species_->insert(organism_);
                break;
            }
            else if (this->front(DOMINANT) == species_)
            {
                branch_ = new Species(this, CONTESTANT, organism_);
                this->insert(branch_);
            }
        }
    }

    organisms.clear();

    return;
}

bool Genus::species_rejection(Species* species_)
{
    Species* dominant_ = this->front(DOMINANT);

    Organism* organism_ = species_->front(DOMINANT);

    return organism_->age > Parameters::stagnation_threshold && species_ != dominant_;
}

bool Genus::species_comparison(Species* first_species_, Species* second_species_)
{
    Organism* first_organism_ = first_species_->front(DOMINANT);
    Organism* second_organism_ = second_species_->front(DOMINANT);

    if (first_organism_->scores[Parameters::evolution_driver] == second_organism_->scores[Parameters::evolution_driver])
    {
        return first_organism_->genotype->size() < second_organism_->genotype->size();
    }
    else
    {
        return first_organism_->scores[Parameters::evolution_driver] > second_organism_->scores[Parameters::evolution_driver];
    }
}
