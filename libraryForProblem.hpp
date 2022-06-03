
#ifndef LIBRARY_FOR_PROBLEM
#define LIBRARY_FOR_PROBLEM

#include <vector>

using aSimpleChain = std::vector<int>;

void PrintMatrix(short** pMatrix, size_t uSize);

void InputNetSizes(int& n, int& m);

bool CanPresentWith4And3(const int n, const int m);

short** GetAdjacencyMatrix(const int n, const int m);

std::vector<aSimpleChain> FullFillTheNet(short** pMatrix, const int n, const int m);

void PrintCreatedChains(std::vector<aSimpleChain>&& aChains);

#endif // LIBRARY_FOR_PROBLEM