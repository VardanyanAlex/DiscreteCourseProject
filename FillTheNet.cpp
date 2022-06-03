
#include <iostream>

#include "libraryForProblem.hpp"

int main()
{
    int n{}, m{};
    InputNetSizes(n, m);

    if (CanPresentWith4And3(n, m))
    {

        size_t uMatrixN = (n + 1) * (m + 1);

        short** pMatrix = GetAdjacencyMatrix(n, m);

        PrintMatrix(pMatrix, uMatrixN);

        std::vector<aSimpleChain> aChains = FullFillTheNet(pMatrix, n, m);

        PrintCreatedChains(std::move(aChains));

    }
    else
    {
        std::cout << "Oops!!! There is no chance to fullfill this net with 3 and 4 length chains" << std::endl;
    }
}