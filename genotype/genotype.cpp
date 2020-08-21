#include "genotype.h"

// Constructor:

// Minimal fully-connected constructor.
Genotype::Genotype(Organism* thatOrganism_, Archetype thatArchetype_)
{
    // Assigns this `Genotype` to the pertinent `Organism`.
    organism = thatOrganism_;

    // Initializes this `Genotype`'s `Chromosome`s.
    links = new Chromosome<Link>();
    nodes = new Chromosome<Node>();

    // Encodes the INPUT, BIAS, and OUTPUT `Node`s.
    for (const auto& [state_, role_, function_, x_, y_] : thatArchetype_)
    {
        // Encodes the new `Node`.
        this->encode(state_, role_, NODE, function_, x_, y_);
    }

    // Encodes FORWARD and BIASING `Link`s, fully connecting the above-created `Node`s.
    for (const auto& inNode_ : nodes->retrieve({INPUT, BIAS}, {ENABLED}))
    {
        for (const auto& outNode_ : nodes->retrieve({OUTPUT}, {ENABLED}))
        {
            // Encodes a new `Link` joining the current source and target `Node`s.
            this->encode((link_role)inNode_->role, LINK, inNode_, outNode_, U(-bound, bound));
        }
    }
}

// Copy constructor responsible for making a deep copy of the input `Genotype`.
Genotype::Genotype(Organism* thatOrganism_, Genotype* thatGenotype_)
{
    // Assigns this `Genotype` to the pertinent `Organism`.
    organism = thatOrganism_;

    // Makes deep copies of the input `Genotype`'s `Chromosome`s.
    links = new Chromosome<Link>(thatGenotype_->links);
    nodes = new Chromosome<Node>(thatGenotype_->nodes);

    // Interlaces the newly created `Chromosome`s.
    for (const auto& [locus_, elements_] : links->genes)
    {
        for (const auto& element_ : elements_)
        {
            // Ensures each `Link` joins the appropriate source `Node` ...
            element_->inNode = nodes->match(element_->inNode);

            // ... and target `Node` pair.
            element_->outNode = nodes->match(element_->outNode);
        }
    }
}


// Destructor.

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

// Encodes a new `Link` into this `Genotype`.
void Genotype::encode(link_role role_, element_type type_, Node* inNode_, Node* outNode_, double weight_)
{
    // Retrieves or generates the `Innovation` which will tag the new `Link`.
    Innovation* innovation_ = organism->population->tag(type_, inNode_->innovation->tag, outNode_->innovation->tag);

    // Creates a new `Link`.
    Link* newLink_ = new Link(innovation_, ENABLED, role_, inNode_, outNode_, weight_);

    // Inserts the new `Link` into the appropriate `Chromosome`.
    links->insert(newLink_);

    return;
}

// Encodes a new `Node` into this `Genotype`.
Node* Genotype::encode(node_role role_, element_type type_, Node* inNode_, Node* outNode_, activation function_)
{
    // Retrieves or generates the `Innovation` which will tag the new `Node`.
    Innovation* innovation_ = organism->population->tag(type_, inNode_->innovation->tag, outNode_->innovation->tag);

    // Creates a new `Node`.
    Node* newNode_ = new Node(innovation_, ENABLED, role_, inNode_, outNode_, function_);

    // Inserts the new `Node` into the appropriate `Chromosome`.
    nodes->insert(newNode_);

    return newNode_;
}

// Encodes a new `Node` into this `Genotype`.
void Genotype::encode(element_state state_, node_role role_, element_type type_, activation function_, int x_, int y_)
{
    // Retrieves or generates the `Innovation` which will tag the new `Node`.
    Innovation* innovation_ = organism->population->tag(type_, x_, x_);

    // Creates a new `Node`.
    Node* newNode_ = new Node(innovation_, state_, role_, function_, x_, y_);

    // Inserts the new `Node` into the appropriate `Chromosome`.
    nodes->insert(newNode_);

    return;
}

// Mutates this `Genotype`.
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

// Enables a DISABLED `Link` belonging to this `Genotype`.
void Genotype::enable_link()
{
    // Retrieves a random DISABLED `Link`.
    Link* theLink_ = links->random({FORWARD, BIASING, RECURRENT, LOOPED}, {DISABLED});

    // Enables the selected `Link`, if any has been found.
    if (theLink_ != NULL)
    {
        links->toggle(theLink_);
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
                theLink_->weight += N(0., power);
                break;

            case REPLACE:
                // Replaces the `Link` weight by an entirely new uniformly distributed value.
                theLink_->weight = U(-bound, bound);
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
                else if (inNode_->y > outNode_->y)
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
                // Ensures the candidate `Link` is RECURRENT.
                else if (inNode_->y < outNode_->y)
                {
                    std::swap(inNode_, outNode_);
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
        if (links->contain({role_}, {ENABLED, DISABLED}, inNode_->innovation->tag, outNode_->innovation->tag))
        {
            // Enforces the selection of another pair of random `Node`s.
            continue;
        }

        // Encodes the new `Link`.
        this->encode(role_, LINK, inNode_, outNode_, U(-bound, bound));

        // A `Link` has been added to this `Genotype`. Return.
        return;
    }

    // All attempts to add a `Link` to this `Genotype` have failed. Return.
    return;
}

// Enables a DISABLED INPUT `Node` belonging to this `Genotype`.
void Genotype::enable_node()
{
    // Retrieves a random DISABLED `Link`.
    Node* theNode_ = nodes->random({INPUT}, {DISABLED});

    // Enables the selected `Link`, if any has been found.
    if (theNode_ != NULL)
    {
        nodes->toggle(theNode_);
    }

    return;
}

// Attempts to alter the activation function of each ENABLED HIDDEN `Node` belonging to this `Genotype`.
// TODO: Make the alterations more likely for newer `Node`s, leaving the older and more time-tested ones relatively unaltered.
void Genotype::alter_nodes()
{
    // Attempts to alter each ENABLED HIDDEN `Node`.
    for (const auto& theNode_ : nodes->retrieve({HIDDEN}, {ENABLED}))
    {
        // Samples the the probability mass function for altering a `Node`'s activation function.
        switch (P(altering_function))
        {
            case HEAVISIDE:
                // Equips the `Node` with the Heaviside activation function.
                theNode_->function = Heaviside;
                break;

            case RELU:
                // Equips the `Node` with the Rectified Linear Unit activation function.
                theNode_->function = ReLU;
                break;

            case LOGISTIC:
                // Equips the `Node` with the Logistic activation function.
                theNode_->function = Logistic;
                break;

            default:
                // Leaves the `Node` unaltered.
                break;
        }
    }

    return;
}

// Attempts to add a new `Node` to this `Genotype`.
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
                if (theLink_ == NULL)
                {
                    return;
                }
                break;

            case FORWARD:
                // There is always an availble FORWARD `Link` to be split.
                break;

            default:
                // All other `Link` roles are invalid.
                break;
        }

        // Checks whether the selected `Link` has ever been split in this `Genotype`.
        if (nodes->contain({HIDDEN}, {ENABLED}, theLink_->innovation->in_tag, theLink_->innovation->out_tag))
        {
            // Enforces the selection of another pair of random `Node`s.
            continue;
        }

        // Ensures the selected `Link`'s state is toggled.
        links->toggle(theLink_);

        // Encodes the new HIDDEN `Node` and its associated `Link`s.
        newNode_ = this->encode(HIDDEN, NODE, theLink_->inNode, theLink_->outNode, ReLU);
        this->encode(role_, LINK, theLink_->inNode, newNode_, 1.);
        this->encode(role_, LINK, newNode_, theLink_->outNode, theLink_->weight);

        // A `Node` has been added to this `Genotype`. Return.
        return;
    }

    // All attempts to add a `Node` to this `Genotype` have failed. Return.
    return;
}

// Assimilates another `Genotype` through a crossover operation.
void Genotype::crossover(Genotype* thatGenotype_)
{
    // Performs the crossover between the two `Genotype`s.
    links->crossover(thatGenotype_->links);
    nodes->crossover(thatGenotype_->nodes);

    return;
}
