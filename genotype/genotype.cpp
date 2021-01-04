#include "../genotype/genotype.h"

// Constructors:

// Initialization constructor responsible for building a `Genotype` from a minimal `Graph`.
Genotype::Genotype(Organism* thatOrganism_, Graph thatGraph_)
{
    // Initializes an auxiliary record of all user-defined `Vertex` labels.
    std::unordered_map<unsigned long int, Node*> record_;

    // Assigns this `Genotype` to the pertinent `Organism`.
    organism = thatOrganism_;

    // Initializes this `Genotype`'s `Chromosome`s.
    links = new Chromosome<Link>();
    nodes = new Chromosome<Node>();

    // Unpacks the input `Graph` into `Vertex`es and `Edge`s.
    auto [vertexes_, edges_] = thatGraph_;

    // Creates a `Node` from each `Vertex` in the input `Graph`.
    for (const auto& [label_, ignore_, state_, role_, activation_, x_, y_] : vertexes_)
    {
        // Encodes the new `Node`.
        Node* newNode_ = this->encode(state_, role_, NODE, activation_, x_, y_);

        // Records the new `Node*` under its user-defined `Vertex` label.
        record_.insert(std::make_pair(label_, newNode_));
    }

    // Creates a `Link` from each `Edge` in the input `Graph`.
    for (const auto& [ignore_, ignore__, state_, role_, in_label_, out_label_, weight_] : edges_)
    {
        // Locates the new `Link`'s source and target `Node`s through their user-defined `Vertex` labels.
        Node* inNode_ = record_[in_label_];
        Node* outNode_ = record_[out_label_];

        // Encodes the new `Link`.
        this->encode(role_, LINK, inNode_, outNode_, weight_.value_or(U(-weight_bound, weight_bound)));
    }
}

// Copy constructor responsible for making a deep copy of the input `Genotype`.
Genotype::Genotype(Organism* thatOrganism_, Genotype* thatGenotype_)
{
    // Assigns this `Genotype` to the pertinent `Organism`.
    organism = thatOrganism_;

    // Initializes this `Genotype`'s `Chromosome`s.
    links = new Chromosome<Link>();
    nodes = new Chromosome<Node>();

    // Copies all `Node`s encoded in the input `Genotype`.
    for (const auto& theNode_ : thatGenotype_->nodes->retrieve({INPUT, HIDDEN, BIAS, OUTPUT}, {ENABLED, DISABLED}))
    {
        // Copies the current `Node`.
        nodes->insert(new Node(theNode_));
    }

    // Copies all `Link`s encoded in the input `Genotype`.
    for (const auto& theLink_ : thatGenotype_->links->retrieve({FORWARD, BIASING, RECURRENT, LOOPED}, {ENABLED, DISABLED}))
    {
        // Copies the current `Link`.
        Link* newLink_ = links->insert(new Link(theLink_));

        // Ensures the newly copied `Link` joins the appropriate source and target `Node`s.
        newLink_->inNode = nodes->find(theLink_->inNode->key);
        newLink_->outNode = nodes->find(theLink_->outNode->key);
    }
}

// Constructs a `Genotype` from an input `Graph`.
Genotype::Genotype(Graph thatGraph_)
{
    // Does not assign this `Genotype` to any `Organism`.
    organism = nullptr;

    // Initializes this `Genotype`'s `Chromosome`s.
    links = new Chromosome<Link>();
    nodes = new Chromosome<Node>();

    // Unpacks the input `Graph` into `Vertex`es and `Edge`s.
    auto [vertexes_, edges_] = thatGraph_;

    // Creates a `Node` from each `Vertex` in the input `Graph`.
    for (const auto& [key_, tag_, state_, role_, activation_, x_, y_] : vertexes_)
    {
        // Inserts the new `Node`.
        nodes->insert(new Node(key_, tag_.value(), state_, role_, activation_, x_, y_));
    }

    // Creates a `Link` from each `Edge` in the input `Graph`.
    for (const auto& [key_, tag_, state_, role_, in_key_, out_key_, weight_] : edges_)
    {
        // Indentifies the source and target `Node`s to be joined by the new `Link`.
        Node* inNode_ = nodes->find(in_key_);
        Node* outNode_ = nodes->find(out_key_);

        // Inserts the new `Link`.
        links->insert(new Link(key_.value(), tag_.value(), state_, role_, inNode_, outNode_, weight_.value()));
    }
}


// Destructor:

// Recursive destructor.
Genotype::~Genotype()
{
    // Deletes the `Chromosome`s which make up this `Genotype`.
    delete links;
    delete nodes;
}


// Methods:

// Retrieves the total number of `Link`s and `Node`s encoded by this `Genotype`.
int Genotype::size()
{
    // Returns the total number of `Link`s and `Node`s encoded by this `Genotype`.
    return links->size() + nodes->size();
}

// Searches for a `Link` or `Node` with matching bounding identification tags.
bool Genotype::contain(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_)
{
    // Generates the search key associated with the `Link` or `Node` of interest.
    unsigned long int key_ = Key(role_, type_, in_tag_, out_tag_);

    // Inspects the appropriate `Chromosome`.
    if (type_ == LINK)
    {
        // Returns the search result.
        return (bool)links->find(key_);
    }
    else if (type_ == NODE)
    {
        // Returns the search result.
        return (bool)nodes->find(key_);
    }
}

// Encodes a new `Link` into this `Genotype`.
Link* Genotype::encode(link_role role_, element_type type_, Node* inNode_, Node* outNode_, double weight_)
{
    // Retrieves the `Genus` log entry matching the new `Link`.
    std::pair<unsigned long int, unsigned int> log_ = organism->species->genus->tag(role_, type_, inNode_->tag, outNode_->tag);

    // Creates the new `Link`.
    Link* newLink_ = new Link(log_.first, log_.second, ENABLED, role_, inNode_, outNode_, weight_);

    // Inserts the new `Link` into the appropriate `Chromosome`.
    return links->insert(newLink_);
}

// Encodes a new `Node` into this `Genotype`.
Node* Genotype::encode(node_role role_, element_type type_, Node* inNode_, Node* outNode_, node_activation activation_)
{
    // Retrieves the `Genus` log entry matching the new `Node`.
    std::pair<unsigned long int, unsigned int> log_ = organism->species->genus->tag(role_, type_, inNode_->tag, outNode_->tag);

    // Creates the new `Node`.
    Node* newNode_ = new Node(log_.first, log_.second, ENABLED, role_, inNode_, outNode_, activation_);

    // Inserts the new `Node` into the appropriate `Chromosome`.
    return nodes->insert(newNode_);
}

// Encodes a new `Node` into this `Genotype`.
Node* Genotype::encode(element_state state_, node_role role_, element_type type_, node_activation activation_, int x_, int y_)
{
    // Retrieves the `Genus` log entry matching the new `Node`.
    std::pair<unsigned long int, unsigned int> log_ = organism->species->genus->tag(role_, type_, x_, y_);

    // Creates the new `Node`.
    Node* newNode_ = new Node(log_.first, log_.second, state_, role_, activation_, x_, y_);

    // Inserts the new `Node` into the appropriate `Chromosome`.
    return nodes->insert(newNode_);
}

// Alters and/or adds new `Link`s and `Node`s to this `Genotype`.
// TODO: Make it possible to set the rate at which structural and parameter mutations occur.
void Genotype::mutate()
{
    // `Link` mutations.

    // Samples the probability mass function for enabling a `Link`.
    if (P(enabling_link))
    {
        // Attempts to enable a DISABLED `Link`.
        this->enable_link();
    }

    // Samples the probability mass function for altering each `Link`.
    if (P(altering_links))
    {
        // Attempts to alter the weight of each ENABLED `Link`.
        this->alter_links();
    }

    // Samples the probability mass function for encoding a new `Link`.
    if (int sample_ = P(adding_link))
    {
        // Attempts to add a new `Link` of the sampled role.
        this->add_link((link_role)sample_);
    }


    // `Node` mutations.

    // Samples the probability mass function for enabling a `Node`.
    if (P(enabling_node))
    {
        // Attempts to enable a DISABLED INPUT `Node`.
        this->enable_node();
    }

    // Samples the probability mass function for altering each `Node`.
    if (P(altering_nodes))
    {
        // Attempts to alter the activation function of each ENABLED HIDDEN `Node`.
        this->alter_nodes();
    }

    // Samples the probability mass function for encoding a new `Node`.
    if (int sample_ = P(adding_node))
    {
        // Attempts to encode a new HIDDEN `Node` by splitting a `Link` of the sampled role.
        this->add_node((link_role)sample_);
    }

    return;
}

// Attempts to enable a DISABLED `Link` belonging to this `Genotype`.
void Genotype::enable_link()
{
    // Retrieves a random DISABLED `Link`.
    Link* theLink_ = links->random({FORWARD, BIASING, RECURRENT, LOOPED}, {DISABLED});

    // Enables the selected `Link`, if any has been found.
    if (theLink_ != nullptr)
    {
        links->toggle(theLink_, ENABLED);
    }

    return;
}

// Attempts to alter the weights of each ENABLED `Link` belonging to this `Genotype`.
// TODO: Make the alterations more likely for newer `Link`s, leaving the older and more time-tested ones relatively unaltered.
void Genotype::alter_links()
{
    // Attempts to alter each ENABLED `Link`.
    for (const auto& theLink_ : links->retrieve({FORWARD, BIASING, RECURRENT, LOOPED}, {ENABLED}))
    {
        // Samples the probability mass function for altering a `Link`'s weight.
        switch (P(altering_weight))
        {
            case PERTURB:
                // Perturbs the `Link` weight by a normally distributed value.
                theLink_->weight += N(0., perturbation_power);
                break;

            case REPLACE:
                // Replaces the `Link` weight by an entirely new uniformly distributed value.
                theLink_->weight = U(-weight_bound, weight_bound);
                break;

            default:
                // Leaves the `Link` unaltered.
                break;
        }
    }

    return;
}

// Attempts to add a new `Link` to this `Genotype`.
void Genotype::add_link(link_role role_, int attempts_)
{
    // The `Node*`s between which the new `Link` will be added.
    Node* inNode_;
    Node* outNode_;

    // Attempts to find two `Node`s which have not yet been connected by a `Link`.
    while (attempts_--)
    {
        // Randomly chooses two encoded `Node`s.
        switch (role_)
        {
            case FORWARD:
                // FORWARD `Link`s must not originate from neither an OUTPUT nor a BIAS `Node`, and must not terminate at neither an INPUT nor a BIAS `Node`.
                inNode_ = nodes->random({INPUT, HIDDEN}, {ENABLED});
                outNode_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                break;

            case BIASING:
                // BIASING `Link`s must originate from the BIAS `Node`, and must terminate at an either HIDDEN or OUTPUT `Node`.
                inNode_ = nodes->random({BIAS}, {ENABLED});
                outNode_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                break;

            case RECURRENT:
                // RECURRENT `Link`s must not originate from nor terminate at neither an INPUT nor a BIAS `Node`.
                inNode_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                outNode_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                break;

            case LOOPED:
                // LOOPED `Link`s cannot be attached neither an INPUT nor a BIAS `Node`.
                inNode_ = nodes->random({HIDDEN, OUTPUT}, {ENABLED});
                outNode_ = inNode_;
                break;

            default:
                // No other `Link` roles exist.
                break;
        }

        // Makes sure the randomly selected `Node`s satisfy certain consistency requirements.
        switch (role_)
        {
            case FORWARD:
                // Ensures the candidate `Link` is not LOOPED.
                if (inNode_ == outNode_)
                {
                    continue;
                }
                // Ensures the candidate `Link` is FORWARD-oriented.
                else if (inNode_->x > outNode_->x)
                {
                    std::swap(inNode_, outNode_);
                }
                break;

            case BIASING:
                // No additional checks needed for a candidate BIASING `Link`.
                break;

            case RECURRENT:
                // Ensures the candidate `Link` is not LOOPED.
                if (inNode_ == outNode_)
                {
                    continue;
                }
                break;

            case LOOPED:
                // No additional checks needed for a candidate LOOPED `Link`.
                break;

            default:
                // No other `Link` roles exist.
                break;
        }

        // Checks whether the selected `Node`s have ever been directly linked in this `Genotype`.
        if (this->contain(role_, LINK, inNode_->tag, outNode_->tag))
        {
            // Enforces the selection of another pair of random `Node`s.
            continue;
        }

        // Encodes the new `Link`.
        this->encode(role_, LINK, inNode_, outNode_, U(-weight_bound, weight_bound));

        // A `Link` has been added to this `Genotype`.
        return;
    }

    // All attempts to add a `Link` to this `Genotype` have failed.
    return;
}

// Attempts to enable a DISABLED INPUT `Node` belonging to this `Genotype`.
void Genotype::enable_node()
{
    // Retrieves a random DISABLED INPUT `Node`.
    Node* inNode_ = nodes->random({INPUT}, {DISABLED});

    // Checks whether a DISABLED INPUT `Node` has been found.
    if (inNode_ != nullptr)
    {
        // Enables the selected INPUT `Node`.
        nodes->toggle(theNode_, ENABLED);

        // Retrieves and a random OUTPUT `Node`.
        Node* outNode_ = nodes->random({OUTPUT}, {ENABLED})

        // Encodes a FORWARD `Link` connecting the two selected `Node`s.
        this->encode(FORWARD, LINK, inNode_, outNode_, U(-weight_bound, weight_bound));
    }

    return;
}

// Attempts to alter the activation of each ENABLED HIDDEN `Node` belonging to this `Genotype`.
// TODO: Make the alterations more likely for newer `Node`s, leaving the older and more time-tested ones relatively unaltered.
void Genotype::alter_nodes()
{
    // Attempts to alter each ENABLED HIDDEN `Node`.
    for (const auto& theNode_ : nodes->retrieve({HIDDEN}, {ENABLED}))
    {
        // Samples the probability mass function for altering a `Node`'s activation.
        if (auto sample_ = P(altering_activation))
        {
            // Equips the `Node` with the sampled activation.
            theNode_->activation = (node_activation)sample_;
        }
    }

    return;
}

// Attempts to add a new HIDDEN `Node` to this `Genotype`.
// TODO: Make the splitting of newer `Link`s less likely, avoiding deleterious chain splittings in young `Organisms`.
void Genotype::add_node(link_role role_, int attempts_)
{
    // The `Link` to be split, and the new `Node` to be added.
    Link* theLink_;
    Node* newNode_;

    // Attempts to find two `Node`s which have not yet been connected by a `Link`.
    while (attempts_--)
    {
        // Selects the `Link` to be split.
        switch (role_)
        {
            case RECURRENT:
                // Selects a random RECURRENT `Link` to be split.
                theLink_ = links->random({RECURRENT}, {ENABLED});
                break;

            case FORWARD:
                // Selects a random FORWARD `Link` to be split.
                theLink_ = links->random({FORWARD}, {ENABLED});
                break;

            default:
                // All other `Link` roles are invalid.
                break;
        }

        // Makes sure a `Link` was successfully selected.
        switch (role_)
        {
            case RECURRENT:
                // Exits in case there are no RECURRENT `Link`s to be split.
                if (theLink_ == nullptr)
                {
                    return;
                }
                break;

            case FORWARD:
                // There is always an available FORWARD `Link` to be split.
                break;

            default:
                // All other `Link` roles are invalid.
                break;
        }

        // Checks whether the selected `Link` has ever been split in this `Genotype`.
        if (this->contain(HIDDEN, NODE, theLink_->inNode->tag, theLink_->outNode->tag))
        {
            // Enforces the selection of another pair of random `Node`s.
            continue;
        }

        // Ensures the selected `Link`'s state is toggled.
        links->toggle(theLink_, DISABLED);

        // Encodes the new HIDDEN `Node` and its associated `Link`s.
        newNode_ = this->encode(HIDDEN, NODE, theLink_->inNode, theLink_->outNode, RELU);
        this->encode(role_, LINK, theLink_->inNode, newNode_, 1.);
        this->encode(role_, LINK, newNode_, theLink_->outNode, theLink_->weight);

        // A `Node` has been added to this `Genotype`.
        return;
    }

    // All attempts to add a `Node` to this `Genotype` have failed.
    return;
}

// Assimilates the homologous `Link`s and `Node`s belonging to the input `Genotype`.
// TODO: Make it so that `Genotype`s can also fuse during crossover.
void Genotype::assimilate(Genotype* thatGenotype_)
{
    // `Link` assimilations.

    // Samples the probability mass function for assimilating each homologous `Link`.
    if (P(assimilating_links))
    {
        // Attempts to assimilate each homologous `Link`.
        this->assimilate_links(thatGenotype_->links);
    }


    // `Node` assimilations.

    // Samples the probability mass function for assimilating each homologous `Node`.
    if (P(assimilating_nodes))
    {
        // Attempts to assimilate each homologous `Node`.
        this->assimilate_nodes(thatGenotype_->nodes);
    }

    return;
}

// Attempts to assimilate each homologous `Link` belonging to the input `Chromosome`.
void Genotype::assimilate_links(Chromosome<Link>* thatChromosome_)
{
    // Attempts to assimilate each homologous `Link`.
    for (const auto& theLink_ : links->retrieve({FORWARD, BIASING, RECURRENT, LOOPED}, {ENABLED, DISABLED}))
    {
        // Searches the input `Chromosome` for a homologous `Link`.
        Link* thatLink_ = thatChromosome_->find(theLink_->key);

        // Samples the probability mass function for assimilating the homologous `Link`.
        if (P(assimilating_weight, thatLink_ != nullptr))
        {
            // Assimilates the homologous `Link` by absorbing its weight.
            theLink_->weight = thatLink_->weight;
        }
    }

    return;
}

// Attempts to assimilate each homologous `Node` belonging to the input `Chromosome`.
void Genotype::assimilate_nodes(Chromosome<Node>* thatChromosome_)
{
    // Attempts to assimilate each homologous `Node`.
    for (const auto& theNode_ : nodes->retrieve({INPUT, HIDDEN, BIAS, OUTPUT}, {ENABLED, DISABLED}))
    {
        // Searches the input `Chromosome` for a homologous `Node`.
        Node* thatNode_ = thatChromosome_->find(theNode_->key);

        // Samples the probability mass function for assimilating the homologous `Node`.
        if (P(assimilating_function, thatNode_ != nullptr))
        {
            // Assimilates the homologous `Node` by absorbing its activation function.
            theNode_->activation = thatNode_->activation;
        }
    }

    return;
}

// Computes the degree of compatibility with the input `Genotype`.
double Genotype::compatibility(Genotype* thatGenotype_)
{
    // The number of matching, disjoint, and excess `Link`s.
    double matching_ = 0.;
    double disjoint_ = 0.;
    double excess_ = 0.;

    // The cumulative difference between each matching `Link`s' weights.
    double difference_ = 0.;

    // Sorts all `Link`s stored in each `Genotype`.
    std::vector<Link*> theseLinks_ = links->sort();
    std::vector<Link*> thoseLinks_ = thatGenotype_->links->sort();

    // Extracts iterators at the beginning of each sorted sequence of `Link`s.
    auto this_ = theseLinks_.begin();
    auto that_ = thoseLinks_.begin();

    // Tallies disjoint and matching `Link`s.
    while (this_ != theseLinks_.end() && that_ != thoseLinks_.end())
    {
        // Counts a disjoint `Link`.
        if (links->element_comparison(*this_, *that_))
        {
            ++disjoint_;
            ++this_;
        }
        // Counts a disjoint `Link`.
        else if (links->element_comparison(*that_, *this_))
        {
            ++disjoint_;
            ++that_;
        }
        // Counts a matching `Link`.
        else
        {
            difference_ += std::fabs((*that_)->weight - (*this_)->weight);
            ++matching_;
            ++this_;
            ++that_;
        }
    }

    // Tallies the excess `Link`s.
    if (this_ == theseLinks_.end())
    {
        excess_ = thoseLinks_.end() - that_;
    }
    else if (that_ == thoseLinks_.end())
    {
        excess_ = theseLinks_.end() - this_;
    }

    // Computes the total number of `Link`s.
    double total_ = matching_ + disjoint_ + excess_;

    // The `std::vector<double>` encapsulating the comparison between the two `Genotype`s.
    std::vector<double> comparison_ {difference_/matching_, disjoint_/total_, excess_/total_};

    // Returns the degree of compatibility with the input `Genotype`.
    return std::inner_product(comparison_.begin(), comparison_.end(), compatibility_weights.begin(), 0.);
}

// Produces this `Genotype`'s associated `Graph`.
Graph Genotype::graph()
{
    // Initializes the output `Graph`.
    Graph theGraph_;

    // Produces a `Vertex` from each ENABLED `Node`.
    for (const auto& theNode_ : nodes->retrieve({INPUT, HIDDEN, BIAS, OUTPUT}, {ENABLED}))
    {
        // Produces the current `Node`'s associated `Vertex`.
        Vertex theVertex_ = theNode_->graph();

        // Inserts the new `Vertex` into the output `Graph`.
        std::get<NODE>(theGraph_).push_back(theVertex_);
    }

    // Produces an `Edge` from each ENABLED `Link`.
    for (const auto& theLink_ : links->retrieve({FORWARD, RECURRENT, BIASING, LOOPED}, {ENABLED}))
    {
        // Produces the current `Link`'s associated `Edge`.
        Edge theEdge_ = theLink_->graph();

        // Inserts the new `Edge` into the output `Graph`.
        std::get<LINK>(theGraph_).push_back(theEdge_);
    }

    // Returns this `Genotype`'s associated `Graph`.
    return theGraph_;
}
