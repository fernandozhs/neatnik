#include "genotype.hpp"


// Constructors:

Genotype::Genotype(Organism* organism_, GenotypeData data_)
{
    organism = organism_;

    links = new Chromosome<Link>();
    nodes = new Chromosome<Node>();

    std::unordered_map<std::uint32_t, Node*> record_;
    std::unordered_map<std::uint32_t, Node*>::iterator first_match_;
    std::unordered_map<std::uint32_t, Node*>::iterator second_match_;
    Node* node_;
    Link* link_;

    auto [node_data_, link_data_] = data_;

    auto this_ = node_data_.begin();
    while (!node_data_.empty())
    {
        auto [tag_, state_, role_, activation_, source_tag_, target_tag_] = *this_;

        switch(role_)
        {
            case BIAS:
            case INPUT:
            case OUTPUT:
                if (organism_ == nullptr)
                {
                    Key key_ (role_, NODE, source_tag_, target_tag_);
                    node_ = new Node(key_, tag_, state_, role_, activation_, source_tag_, target_tag_);
                    nodes->insert(node_);
                }
                else
                {
                    node_ = this->encode(state_, role_, NODE, activation_, source_tag_, target_tag_);
                }
                record_.insert(std::make_pair(tag_, node_));
                this_ = node_data_.erase(this_);
                break;

            case HIDDEN:
                first_match_ = record_.find(source_tag_);
                second_match_ = record_.find(target_tag_);
                if (first_match_ != record_.end() && second_match_ != record_.end())
                {
                    Node* source_ = first_match_->second;
                    Node* target_ = second_match_->second;
                    if (organism == nullptr)
                    {
                        Key key_ (role_, NODE, source_tag_, target_tag_);
                        node_ = new Node(key_, tag_, state_, role_, source_, target_, activation_);
                        nodes->insert(node_);
                    }
                    else
                    {
                        node_ = this->encode(role_, NODE, source_, target_, activation_);
                    }
                    record_.insert(std::make_pair(tag_, node_));
                    this_ = node_data_.erase(this_);
                }
                else
                {
                    if (++this_ != node_data_.end())
                    {
                        continue;
                    }
                }
                break;

            default:
                break;
        }

        if (this_ == node_data_.end())
        {
            this_ = node_data_.begin();
        }
    }

    for (const auto& [tag_, state_, role_, weight_, source_tag_, target_tag_] : link_data_)
    {
        Node* source_ = record_[source_tag_];
        Node* target_ = record_[target_tag_];

        if (organism_ == nullptr)
        {
            Key key_ (role_, LINK, source_tag_, target_tag_);
            link_ = new Link(key_, tag_.value(), state_, role_, source_, target_, weight_.value());
            links->insert(link_);
        }
        else
        {
            this->encode(role_, LINK, source_, target_, weight_.value_or(U(-Parameters::weight_bound, Parameters::weight_bound)));
        }
    }
}

Genotype::Genotype(Organism* organism_, Genotype* genotype_)
{
    organism = organism_;

    links = new Chromosome<Link>();
    nodes = new Chromosome<Node>();

    for (const auto& node_ : genotype_->nodes->retrieve({INPUT, HIDDEN, BIAS, OUTPUT}, {ENABLED, DISABLED}))
    {
        nodes->insert(new Node(node_));
    }

    for (const auto& link_ : genotype_->links->retrieve({FORWARD, BIASING, RECURRENT, LOOPED}, {ENABLED, DISABLED}))
    {
        Link* copy_ = links->insert(new Link(link_));

        copy_->source = nodes->find(link_->source->key);
        copy_->target = nodes->find(link_->target->key);
    }
}


// Destructor:

Genotype::~Genotype()
{
    delete links;
    delete nodes;
}


// Methods:

int Genotype::size()
{
    return links->size() + nodes->size();
}

bool Genotype::contain(int role_, element_type type_, std::uint32_t source_tag_, std::uint32_t target_tag_)
{
    Key key_ (role_, type_, source_tag_, target_tag_);

    if (type_ == LINK)
    {
        return (bool)links->find(key_);
    }
    else if (type_ == NODE)
    {
        return (bool)nodes->find(key_);
    }
}

Link* Genotype::encode(link_role role_, element_type type_, Node* source_, Node* target_, double weight_)
{
    std::pair<Key, std::uint32_t> log_ = organism->species->genus->tag(role_, type_, source_->tag, target_->tag);

    Link* link_ = new Link(log_.first, log_.second, ENABLED, role_, source_, target_, weight_);

    return links->insert(link_);
}

Node* Genotype::encode(node_role role_, element_type type_, Node* source_, Node* target_, node_activation activation_)
{
    std::pair<Key, std::uint32_t> log_ = organism->species->genus->tag(role_, type_, source_->tag, target_->tag);

    Node* node_ = new Node(log_.first, log_.second, ENABLED, role_, source_, target_, activation_);

    return nodes->insert(node_);
}

Node* Genotype::encode(element_state state_, node_role role_, element_type type_, node_activation activation_, std::uint32_t x_, std::uint32_t y_)
{
    std::pair<Key, std::uint32_t> log_ = organism->species->genus->tag(role_, type_, x_, y_);

    Node* node_ = new Node(log_.first, log_.second, state_, role_, activation_, x_, y_);

    return nodes->insert(node_);
}

// TODO: Make it possible to set the rate at which structural and parameter mutations occur.
void Genotype::mutate()
{
    // `Link` mutations.
    if (P(Parameters::enabling_link))
    {
        this->enable_link();
    }

    if (P(Parameters::altering_links))
    {
        this->alter_links();
    }

    if (int sample_ = P(Parameters::adding_link))
    {
        this->add_link((link_role)sample_);
    }

    // `Node` mutations.
    if (int sample_ = P(Parameters::enabling_node))
    {
        this->enable_node((node_role)sample_);
    }

    if (P(Parameters::altering_nodes))
    {
        this->alter_nodes();
    }

    if (int sample_ = P(Parameters::adding_node))
    {
        this->add_node((link_role)sample_);
    }

    return;
}

void Genotype::enable_link()
{
    Link* link_ = links->random({FORWARD, BIASING, RECURRENT, LOOPED}, {DISABLED});

    if (link_ != nullptr)
    {
        links->toggle(link_, ENABLED);
    }

    return;
}

// TODO: Make the alterations more likely for newer `Link`s, leaving the older and more time-tested ones relatively unaltered.
void Genotype::alter_links()
{
    for (const auto& link_ : links->retrieve({FORWARD, BIASING, RECURRENT, LOOPED}, {ENABLED}))
    {
        switch (P(Parameters::altering_weight))
        {
            case PERTURBATION:
                link_->weight += N(0., Parameters::perturbation_power);
                break;

            case REPLACEMENT:
                link_->weight = U(-Parameters::weight_bound, Parameters::weight_bound);
                break;

            default:
                break;
        }
    }

    return;
}

void Genotype::add_link(link_role role_)
{
    Node* source_;
    Node* target_;

    for (int attempts_ = Parameters::mutation_attempts; attempts_; --attempts_)
    {
        switch (role_)
        {
            case FORWARD:
                source_ = nodes->random({INPUT, HIDDEN}, {ENABLED});
                target_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                break;

            case BIASING:
                source_ = nodes->random({BIAS}, {ENABLED});
                target_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                break;

            case RECURRENT:
                source_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                target_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                break;

            case LOOPED:
                source_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                target_ = source_;
                break;

            default:
                break;
        }

        switch (role_)
        {
            case FORWARD:
                if (source_ == nullptr || target_ == nullptr)
                {
                    continue;
                }
                else if (source_ == target_)
                {
                    continue;
                }
                else if (source_->x > target_->x)
                {
                    std::swap(source_, target_);
                }
                break;

            case BIASING:
                if (source_ == nullptr || target_ == nullptr)
                {
                    continue;
                }
                break;

            case RECURRENT:
                if (source_ == target_)
                {
                    continue;
                }
                break;

            case LOOPED:
                break;

            default:
                break;
        }

        if (this->contain(role_, LINK, source_->tag, target_->tag))
        {
            continue;
        }

        this->encode(role_, LINK, source_, target_, U(-Parameters::weight_bound, Parameters::weight_bound));

        return;
    }

    return;
}

void Genotype::enable_node(node_role role_)
{
    Node* source_;
    Node* target_;

    switch (role_)
    {
        case HIDDEN:
            source_ = nodes->random({INPUT}, {DISABLED});
            target_ = nodes->random({HIDDEN}, {ENABLED});
            break;

        case OUTPUT:
            source_ = nodes->random({INPUT}, {DISABLED});
            target_ = nodes->random({OUTPUT}, {ENABLED});
            break;

        default:
            break;
    }

    switch (role_)
    {
        case HIDDEN:
            if (source_ == nullptr || target_ == nullptr)
            {
                return;
            }

        case OUTPUT:
            if (source_ == nullptr || target_ == nullptr)
            {
                return;
            }

        default:
            break;
    }

    nodes->toggle(source_, ENABLED);

    this->encode(FORWARD, LINK, source_, target_, U(-Parameters::weight_bound, Parameters::weight_bound));

    return;
}

// TODO: Make the alterations more likely for newer `Node`s, leaving the older and more time-tested ones relatively unaltered.
void Genotype::alter_nodes()
{
    for (const auto& node_ : nodes->retrieve({HIDDEN}, {ENABLED}))
    {
        if (auto sample_ = P(Parameters::altering_activation))
        {
            node_->activation = (node_activation)sample_;
        }
    }

    return;
}

void Genotype::add_node(link_role role_)
{
    Link* link_;
    Node* node_;

    std::vector<double> priorities_;

    for (int attempts_ = Parameters::mutation_attempts; attempts_; --attempts_)
    {
        switch (role_)
        {
            case RECURRENT:
                priorities_ = links->priorities({RECURRENT}, {ENABLED}, Parameters::splitting_priority);
                break;

            case FORWARD:
                priorities_ = links->priorities({FORWARD}, {ENABLED}, Parameters::splitting_priority);
                break;

            default:
                break;
        }

        switch (role_)
        {
            case RECURRENT:
                link_ = links->random({RECURRENT}, {ENABLED}, priorities_);
                break;

            case FORWARD:
                link_ = links->random({FORWARD}, {ENABLED}, priorities_);
                break;

            default:
                break;
        }

        switch (role_)
        {
            case RECURRENT:
                if (link_ == nullptr)
                {
                    return;
                }
                break;

            case FORWARD:
                if (link_ == nullptr)
                {
                    return;
                }
                break;

            default:
                break;
        }

        if (this->contain(HIDDEN, NODE, link_->source->tag, link_->target->tag))
        {
            continue;
        }

        links->toggle(link_, DISABLED);

        node_ = this->encode(HIDDEN, NODE, link_->source, link_->target, Parameters::initial_activation);
        this->encode(role_, LINK, link_->source, node_, 1.);
        this->encode(role_, LINK, node_, link_->target, link_->weight);

        return;
    }

    return;
}

// TODO: Make it so that `Genotype`s can also fuse during crossover.
void Genotype::assimilate(Genotype* genotype_)
{
    // `Link` assimilations.
    if (P(Parameters::assimilating_links))
    {
        this->assimilate_links(genotype_->links);
    }

    // `Node` assimilations.
    if (P(Parameters::assimilating_nodes))
    {
        this->assimilate_nodes(genotype_->nodes);
    }

    return;
}

void Genotype::assimilate_links(Chromosome<Link>* chromosome_)
{
    for (const auto& link_ : links->retrieve({FORWARD, BIASING, RECURRENT, LOOPED}, {ENABLED, DISABLED}))
    {
        Link* homologous_ = chromosome_->find(link_->key);

        if (P(Parameters::assimilating_weight, homologous_ != nullptr))
        {
            link_->weight = homologous_->weight;
        }
    }

    return;
}

void Genotype::assimilate_nodes(Chromosome<Node>* chromosome_)
{
    for (const auto& node_ : nodes->retrieve({INPUT, HIDDEN, BIAS, OUTPUT}, {ENABLED, DISABLED}))
    {
        Node* homologous_ = chromosome_->find(node_->key);

        if (P(Parameters::assimilating_activation, homologous_ != nullptr))
        {
            node_->activation = homologous_->activation;
        }
    }

    return;
}

double Genotype::compatibility(Genotype* genotype_)
{
    double matching_ = 0.;
    double disjoint_ = 0.;
    double excess_ = 0.;
    double difference_ = 0.;

    std::vector<Link*> these_ = links->sort();
    std::vector<Link*> those_ = genotype_->links->sort();

    auto this_ = these_.begin();
    auto that_ = those_.begin();

    while (this_ != these_.end() && that_ != those_.end())
    {
        if (links->element_comparison(*this_, *that_))
        {
            ++disjoint_;
            ++this_;
        }
        else if (links->element_comparison(*that_, *this_))
        {
            ++disjoint_;
            ++that_;
        }
        else
        {
            difference_ += std::fabs((*that_)->weight - (*this_)->weight);
            ++matching_;
            ++this_;
            ++that_;
        }
    }

    if (this_ == these_.end())
    {
        excess_ = those_.end() - that_;
    }
    else if (that_ == those_.end())
    {
        excess_ = these_.end() - this_;
    }

    double total_ = matching_ + disjoint_ + excess_;

    std::vector<double> comparison_ {difference_/matching_, disjoint_/total_, excess_/total_};

    return std::inner_product(comparison_.begin(), comparison_.end(), Parameters::compatibility_weights.begin(), 0.);
}

GenotypeData Genotype::data()
{
    std::vector<NodeData> nodes_data_;
    std::vector<LinkData> links_data_;

    for (const auto& node_ : nodes->retrieve({INPUT, BIAS, OUTPUT, HIDDEN}, {ENABLED}))
    {
        nodes_data_.push_back(node_->data());
    }

    for (const auto& link_ : links->retrieve({FORWARD, RECURRENT, BIASING, LOOPED}, {ENABLED}))
    {
        links_data_.push_back(link_->data());
    }

    GenotypeData data_ (nodes_data_, links_data_);

    return data_;
}
