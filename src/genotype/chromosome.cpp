#include "../genotype/chromosome.hpp"

// Constructor:

template <class Element>
Chromosome<Element>::Chromosome()
{

}


// Destructor:

template <class Element>
Chromosome<Element>::~Chromosome()
{
    for (auto& element_ : this->retrieve())
    {
        delete element_;
    }
}


// Methods:

template <class Element>
unsigned int Chromosome<Element>::size(const std::vector<unsigned int> roles_, const std::vector<int> states_)
{
    int size_ = 0;

    for (const auto& role_ : roles_)
    {
        for (const auto& state_ : states_)
        {
            size_ += genes[state_*role_].size();
        }
    }

    return size_;
}

template <class Element>
typename std::vector<Element*>::iterator Chromosome<Element>::begin(int locus_)
{
    return genes[locus_].begin();
}

template <class Element>
typename std::vector<Element*>::iterator Chromosome<Element>::end(int locus_)
{
    return genes[locus_].end();
}

template <class Element>
Element* Chromosome<Element>::find(unsigned long int key_)
{
    auto match_ = logbook.find(key_);

    if (match_ != logbook.end())
    {
        return (*match_).second;
    }
    else
    {
        return nullptr;
    }
}

template <class Element>
Element* Chromosome<Element>::insert(Element* element_)
{
    std::pair<unsigned long int, Element*> log_ (element_->key, element_);

    logbook.insert(log_);

    int locus_ = (element_->state)*(element_->role);

    genes[locus_].push_back(element_);

    return element_;
}

template <class Element>
Element* Chromosome<Element>::remove(Element* element_)
{
    int locus_ = (element_->state)*(element_->role);

    auto location_ = std::find(this->begin(locus_), this->end(locus_), element_);

    genes[locus_].erase(location_);

    return element_;
}

template <class Element>
void Chromosome<Element>::toggle(Element* element_, int state_)
{
    this->remove(element_);

    element_->state = (element_state)state_;

    this->insert(element_);

    return;
}

template <class Element>
Element* Chromosome<Element>::random(const std::vector<unsigned int> roles_, const std::vector<int> states_, const std::vector<double> weights_)
{
    unsigned int sample_;

    unsigned int size_ = this->size(roles_, states_);

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

    for (const auto& role_ : roles_)
    {
        for (const auto& state_ : states_)
        {
            size_ -= genes[state_*role_].size();

            if (sample_ > size_)
            {
                return genes[state_*role_][sample_ - size_ - 1];
            }
        }
    }

    return nullptr;
}

template <class Element>
std::vector<Element*> Chromosome<Element>::retrieve(const std::vector<unsigned int> roles_, const std::vector<int> states_)
{
    std::vector<Element*> elements_;
    elements_.reserve(this->size(roles_, states_));

    for (const auto& role_ : roles_)
    {
        for (const auto& state_ : states_)
        {
            elements_.insert(elements_.end(), this->begin(state_*role_), this->end(state_*role_));
        }
    }

    return elements_;
}

template <class Element>
std::vector<Element*> Chromosome<Element>::sort(const std::vector<unsigned int> roles_, const std::vector<int> states_)
{
    std::vector<Element*> elements_ = this->retrieve(roles_, states_);

    std::sort(elements_.begin(), elements_.end(), this->element_comparison);

    return elements_;
}

template <class Element>
std::vector<double> Chromosome<Element>::priorities(const std::vector<unsigned int> roles_, const std::vector<int> states_, const double priority_)
{
    std::vector<Element*> elements_ = this->retrieve(roles_, states_);
    unsigned int size_ = elements_.size();

    std::vector<double> priorities_ (size_);
    std::vector<unsigned int> indices_ (size_);

    std::iota(indices_.begin(), indices_.end(), 0.);
    std::sort(indices_.begin(), indices_.end(), [&](unsigned int i_, unsigned int j_){return elements_[i_]->tag > elements_[j_]->tag;});

    for (unsigned int position_ = 0; position_ < size_; ++position_)
    {
        unsigned int index_ = indices_[position_];

        unsigned int multiplier_ = position_ + 1;

        priorities_[index_] = priority_*multiplier_;
    }

    return priorities_;
}

template <class Element>
bool Chromosome<Element>::element_comparison(Element* first_element_, Element* second_element_)
{
    return first_element_->tag < second_element_->tag;
}
