#include "species.hpp"


// Constructors:

Species::Species(Genus* genus_, taxon_group group_, std::vector<Graph> graphs_)
{
    genus = genus_;

    group = group_;

    for (const auto& graph_ : graphs_)
    {
        Organism* organism_ = new Organism(this, graph_);

        this->insert(organism_);
    }

    Organism* organism_ = this->random({CONTESTANT});
    this->toggle(organism_, DOMINANT);
}

Species::Species(Genus* genus_, taxon_group group_, Organism* organism_)
{
    genus = genus_;

    group = group_;

    this->insert(organism_);

    this->toggle(organism_, DOMINANT);
}


// Destructor:

Species::~Species()
{
    for (auto& organism_ : this->retrieve({DOMINANT, CONTESTANT}))
    {
        delete organism_;
    }
}


// Methods:

unsigned int Species::size(const std::vector<int> groups_)
{
    int size_ = 0;

    for (const auto& group_ : groups_)
    {
        size_ += organisms[group_].size();
    }

    return size_;
}

typename std::vector<Organism*>::iterator Species::begin(int group_)
{
    return organisms[group_].begin();
}

typename std::vector<Organism*>::iterator Species::end(int group_)
{
    return organisms[group_].end();
}

Organism* Species::front(int group_)
{
    return organisms[group_].front();
}

Organism* Species::back(int group_)
{
    return organisms[group_].back();
}

Organism* Species::insert(Organism* organism_)
{
    int group_ = organism_->group;

    organism_->species = this;

    organisms[group_].push_back(organism_);

    return organism_;
}

Organism* Species::remove(Organism* organism_)
{
    int group_ = organism_->group;

    auto location_ = std::find(this->begin(group_), this->end(group_), organism_);

    organisms[group_].erase(location_);

    return organism_;
}

void Species::purge(Organism* organism_)
{
    delete this->remove(organism_);

    return;
}

void Species::purge(const std::vector<int> groups_)
{
    for (const auto& organism_ : this->retrieve(groups_))
    {
        delete organism_;
    }

    for (const auto& group_ : groups_)
    {
        organisms[group_].clear();
    }

    return;
}

void Species::toggle(Organism* organism_, int group_)
{
    this->remove(organism_);

    organism_->group = (taxon_group)group_;

    this->insert(organism_);

    return;
}

Organism* Species::random(const std::vector<int> groups_, const std::vector<double> weights_)
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
        size_ -= organisms[group_].size();

        if (sample_ > size_)
        {
            return organisms[group_][sample_ - size_ - 1];
        }
    }

    return nullptr;
}

std::vector<Organism*> Species::retrieve(const std::vector<int> groups_)
{
    std::vector<Organism*> organisms_;
    organisms_.reserve(this->size(groups_));

    for (const auto& group_ : groups_)
    {
        organisms_.insert(organisms_.end(), this->begin(group_), this->end(group_));
    }

    return organisms_;
}

std::vector<Organism*> Species::sort(const std::vector<int> groups_)
{
    std::vector<Organism*> organisms_ = this->retrieve(groups_);

    std::sort(organisms_.begin(), organisms_.end(), this->organism_comparison);

    return organisms_;
}

void Species::select()
{
    std::vector<Organism*> organisms_ = this->sort({DOMINANT, CONTESTANT});

    if (this->front(DOMINANT) != organisms_.front())
    {
        this->toggle(this->front(DOMINANT), CONTESTANT);
        this->toggle(organisms_.front(), DOMINANT);
    }

    auto threshold_ = ++organisms_.begin() + this->size()*(1 - Parameters::rejection_fraction);

    for (auto that_ = organisms_.begin(); that_ != organisms_.end(); ++that_)
    {
        if (that_ < threshold_)
        {
            (*that_)->age++;
        }
        else
        {
            this->purge(*that_);
        }
    }

    return;
}

Organism* Species::spawn()
{
    Organism* mother_;
    Organism* father_;

    auto process_ = P(Parameters::spawning_organism, this->size({CONTESTANT}));

    for (int attempts_ = Parameters::spawning_attempts; attempts_; --attempts_)
    {
        switch (process_)
        {
            case MUTATION:
                mother_ = this->random({DOMINANT, CONTESTANT});
                father_ = nullptr;
                break;

            case ASSIMILATION:
                mother_ = this->random({DOMINANT, CONTESTANT});
                father_ = this->random({DOMINANT, CONTESTANT});
                break;

            default:
                break;
        }

        switch (process_)
        {
            case MUTATION:
                break;

            case ASSIMILATION:
                if (mother_ == father_)
                {
                    continue;
                }
                if (this->organism_comparison(mother_, father_))
                {
                    std::swap(mother_, father_);
                }
                break;

            default:
                break;
        }

        switch (process_)
        {
            case MUTATION:
                return mother_->mutate();
                break;

            case ASSIMILATION:
                return mother_->assimilate(father_);
                break;

            default:
                break;
        }
    }

    return nullptr;
}

bool Species::organism_compatibility(Organism* organism_)
{
    Organism* dominant_ = this->front(DOMINANT);

    return organism_->genotype->compatibility(dominant_->genotype) < Parameters::compatibility_threshold;
}

bool Species::organism_comparison(Organism* first_organism_, Organism* second_organism_)
{
    if (first_organism_->score == second_organism_->score)
    {
        return first_organism_->genotype->size() < second_organism_->genotype->size();
    }
    else
    {
        return first_organism_->score > second_organism_->score;
    }
}
