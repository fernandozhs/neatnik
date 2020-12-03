#include "io.h"

/*
  Print:
  -----
*/

// Prints the input `Link`.
void Print(Link* thatLink_)
{
    // Prints the input `Link`'s role, source `Node`, target `Node`, and weight.
    std::wcout << std::setw(2) << std::right << " ";
    std::wcout << std::setw(4) << std::right << thatLink_->tag;
    std::wcout << std::setw(5) << std::right << " ";
    std::wcout << std::setw(6) << std::right << thatLink_->inNode->tag;
    std::wcout << std::setw(5) << std::right << " ";
    std::wcout << std::setw(6) << std::right << thatLink_->outNode->tag;
    std::wcout << std::setw(5) << std::right << " ";
    std::wcout << std::setw(6) << std::right << thatLink_->weight;
    std::wcout << std::setw(2) << std::right << " ";
    std::wcout << std::endl;
}

// Prints the input `Genotype`.
void Print(Genotype* thatGenotype_)
{
    // Prints the table header.
    std::wcout << std::setw(41) << std::wstring(41, L'-') << std::endl;
    std::wcout << std::setw(2) << std::right << " ";
    std::wcout << std::setw(4) << std::right << "Link";
    std::wcout << std::setw(5) << std::right << " ";
    std::wcout << std::setw(6) << std::right << "Source";
    std::wcout << std::setw(5) << std::right << " ";
    std::wcout << std::setw(6) << std::right << "Target";
    std::wcout << std::setw(5) << std::right << " ";
    std::wcout << std::setw(6) << std::right << "Weight";
    std::wcout << std::setw(2) << std::right << " " << std::endl;
    std::wcout << std::setw(41) << std::wstring(41, L'-') << std::endl;

    // Prints each `Link` in the input `Genotype`.
    for (auto const& theLink_ : thatGenotype_->links->retrieve({FORWARD, BIASING, RECURRENT, LOOPED}, {ENABLED}))
    {
        Print(theLink_);
    }

    // Prints the table footer.
    std::wcout << std::setw(41) << std::wstring(41, L'-') << std::endl;
}

/*
  Read:
  ----
*/

// ...


/*
  Write:
  -----
*/

// ...
