
#include <iostream>
#include <cassert>

#include "libraryForProblem.hpp"

enum class EPos
{
    left,
    top,
    right,
    bottom
};

short** GetAdjacencyMatrix(const int n, const int m)
{
    size_t uMatrixRowLength = (n + 1) * (m + 1);

    short** pMatrix = new short* [uMatrixRowLength];
    for (size_t i = 0; i < uMatrixRowLength; ++i)
    {
        pMatrix[i] = new short[uMatrixRowLength] {};
    }

    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            if ((j - 1) >= 0)
            {
                pMatrix[(m + 1) * i + j][(m + 1) * i + j - 1] = 1;
            }
            if ((j + 1) <= m)
            {
                pMatrix[(m + 1) * i + j][(m + 1) * i + j + 1] = 1;
            }
            if ((i - 1) >= 0)
            {
                pMatrix[(m + 1) * i + j][(m + 1) * i + j - (m + 1)] = 1;
            }
            if ((i + 1) <= n)
            {
                pMatrix[(m + 1) * i + j][(m + 1) * i + j + (m + 1)] = 1;
            }
        }
    }

    return pMatrix;
}

namespace
{
    bool CheckInput(const int n, const int m)
    {
        return n > 0 && m > 0;
    }

    /*
    * pre-condition: have bottom vertex
    */
    int BottomPosition(int& iDir, const int iRowLength)
    {
        return iDir += iRowLength + 1;
    }

    /*
    * pre-condition: have top vertex
    */
    int TopPosition(int& iDir, const int iRowLength)
    {
        return iDir -= iRowLength + 1;
    }

    /*
    * pre-condition: have right vertex
    */
    int RightPosition(int& iDir)
    {
        return iDir += 1;
    }

    /*
    * pre-condition: have left vertex
    */
    int LeftPosition(int& iDir)
    {
        return iDir -= 1;
    }

    aSimpleChain GetNLengthStraithChain(int& iCurrentDir, int N)
    {
        aSimpleChain CurrentChain;

        CurrentChain.push_back(iCurrentDir);

        for (int i = 0; i < N; ++i)
        {
            CurrentChain.push_back(RightPosition(iCurrentDir));
        }

        return CurrentChain;
    }

    aSimpleChain GetNLengthVerticalChain(int& iCurrentDir, int N, int iMatrix_m)
    {
        aSimpleChain CurrentChain;

        CurrentChain.push_back(iCurrentDir);

        for (int i = 0; i < N; ++i)
        {
            CurrentChain.push_back(BottomPosition(iCurrentDir, iMatrix_m));
        }

        return CurrentChain;
    }

    aSimpleChain Get_i_Bottom_j_LeftChain(int& iCurrentDir, int i, int j, int iMatrix_m)
    {
        aSimpleChain CurrentChain;

        CurrentChain.push_back(iCurrentDir);

        for (int iCount_i = 0; iCount_i < i; ++iCount_i)
        {
            CurrentChain.push_back(BottomPosition(iCurrentDir, iMatrix_m));
        }

        for (int iCount_j = 0; iCount_j < j; ++iCount_j)
        {
            CurrentChain.push_back(LeftPosition(iCurrentDir));
        }

        return CurrentChain;
    }

    aSimpleChain Get_i_Bottom_j_Left_k_TopChain(int& iCurrentDir, int i, int j, int k, int iMatrix_m)
    {
        aSimpleChain CurrentChain;

        CurrentChain.push_back(iCurrentDir);

        for (int iCount_i = 0; iCount_i < i; ++iCount_i)
        {
            CurrentChain.push_back(BottomPosition(iCurrentDir, iMatrix_m));
        }

        for (int iCount_j = 0; iCount_j < j; ++iCount_j)
        {
            CurrentChain.push_back(LeftPosition(iCurrentDir));
        }

        for (int iCount_k = 0; iCount_k < k; ++iCount_k)
        {
            CurrentChain.push_back(TopPosition(iCurrentDir, iMatrix_m));
        }

        return CurrentChain;
    }

    aSimpleChain Get_i_Top_j_RightChain(int& iCurrentDir, int i, int j, int iMatrix_m)
    {
        aSimpleChain CurrentChain;

        CurrentChain.push_back(iCurrentDir);

        for (int iCount_i = 0; iCount_i < i; ++iCount_i)
        {
            CurrentChain.push_back(TopPosition(iCurrentDir, iMatrix_m));
        }

        for (int iCount_j = 0; iCount_j < j; ++iCount_j)
        {
            CurrentChain.push_back(RightPosition(iCurrentDir));
        }

        return CurrentChain;
    }

    aSimpleChain Get_i_Top_j_Right_k_BottomChain(int& iCurrentDir, int i, int j, int k, int iMatrix_m)
    {
        aSimpleChain CurrentChain = Get_i_Top_j_RightChain(iCurrentDir, i, j, iMatrix_m);

        for (int iCount_k = 0; iCount_k < k; ++iCount_k)
        {
            CurrentChain.push_back(BottomPosition(iCurrentDir, iMatrix_m));
        }

        return CurrentChain;
    }

    aSimpleChain Get_i_Right_j_Bottom_k_LeftChain(int& iCurrentDir, int i, int j, int k, int iMatrix_m)
    {
        aSimpleChain CurrentChain;

        CurrentChain.push_back(iCurrentDir);

        for (int iCount_i = 0; iCount_i < i; ++iCount_i)
        {
            CurrentChain.push_back(RightPosition(iCurrentDir));
        }

        for (int iCount_j = 0; iCount_j < j; ++iCount_j)
        {
            CurrentChain.push_back(BottomPosition(iCurrentDir, iMatrix_m));
        }

        for (int iCount_k = 0; iCount_k < k; ++iCount_k)
        {
            CurrentChain.push_back(LeftPosition(iCurrentDir));
        }

        return CurrentChain;
    }


    void ChangePos(EPos ePos, int& iCurrentDir, int iCount, int iMatrix_m)
    {
        switch (ePos)
        {
        case EPos::left:
            for (int i = 0; i < iCount; ++i)
            {
                LeftPosition(iCurrentDir);
            }
            break;
        case  EPos::top:
            for (int i = 0; i < iCount; ++i)
            {
                TopPosition(iCurrentDir, iMatrix_m);
            }
            break;
        case EPos::right:
            for (int i = 0; i < iCount; ++i)
            {
                RightPosition(iCurrentDir);
            }
            break;
        case  EPos::bottom:
            for (int i = 0; i < iCount; ++i)
            {
                BottomPosition(iCurrentDir, iMatrix_m);
            }
            break;
        }
    }

    void Get4And3LenghtChainsCount(int iChainLength, int& iFour, int& iThree)
    {
        if (iChainLength % 4 == 0 && iChainLength > 0)
        {
            iFour = iChainLength / 4;

            iThree = 0;
        }

        iFour = iThree = 0;

        while (iChainLength % 4 != 0)
        {
            ++iThree;
            iChainLength -= 3;
        }

        if (iChainLength != 0)
        {
            iFour = iChainLength / 4;
        }

    }
} // unnamed namespace

bool CanPresentWith4And3(const int n, const int m)
{
    return (n == m && n == 1) ? false : true;
}

/*
* pre-condition: n <= m
*/
std::vector<aSimpleChain> FullFillTheNet(short** pMatrix, const int n, const int m)
{
    std::vector<std::vector<int>> aChains;
    if (n == 1)
    {
        for (int i = 0; i < m; ++i)
        {
            int iDir = 1;
            if (i == 0)
            {
                aSimpleChain CurrentChain;
                CurrentChain.push_back(iDir);

                CurrentChain.push_back(BottomPosition(iDir, m));

                CurrentChain.push_back(RightPosition(iDir));

                CurrentChain.push_back(TopPosition(iDir, m));

                aChains.push_back(std::move(CurrentChain));
            }
            else if (i == 1)
            {
                aChains.push_back(std::move(Get_i_Right_j_Bottom_k_LeftChain(iDir, 2, 1, 1, m)));
            }
            else
            {
                iDir += i;
                aChains.push_back(std::move(Get_i_Right_j_Bottom_k_LeftChain(iDir, 1, 1, 1, m)));
            }
        }
    }
    else if (n == 2)
    {
        if (m == 4)
        {
            //      |
            //    __|
            for (int i = 1; i <= m; ++i)
            {
                int iDir = i + 1;
                aChains.push_back(std::move(Get_i_Bottom_j_LeftChain(iDir, n, 1, m)));
            }

            // ----
            int iDir = m + 2;
            aChains.push_back(std::move(GetNLengthStraithChain(iDir, m)));

            aSimpleChain CurrentChain;

            BottomPosition(iDir, m);
            BottomPosition(iDir, m);

            //  __
            // |
            // |
            iDir = 1;
            ChangePos(EPos::bottom, iDir, 2, m);
            CurrentChain.push_back(iDir);

            CurrentChain.push_back(TopPosition(iDir, m));

            CurrentChain.push_back(TopPosition(iDir, m));

            CurrentChain.push_back(RightPosition(iDir));

            aChains.push_back(CurrentChain);

            CurrentChain.clear();
            CurrentChain.resize(0);

            // ---
            aChains.push_back(GetNLengthStraithChain(iDir, 3));

        }
        else
        { // n == 2, m != 4 

            //   |
            // __|
            int iDir = 1;
            for (int i = 1; i <= m; ++i)
            {
                iDir = 1 + i;
                aChains.push_back(std::move(Get_i_Bottom_j_LeftChain(iDir, n, 1, m)));
            }

            int iFour{}, iThree{};
            Get4And3LenghtChainsCount(m + 1, iFour, iThree);

            if (iThree == 0)
            {
                //  _ _ _
                // |
                for (int i = 1; i <= n; ++i)
                {
                    iDir = 1;
                    for (int j = 0; j < i; ++j)
                    {
                        BottomPosition(iDir, m);
                    }
                    aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 3, m)));
                }
                --iFour;

                // ----
                for (int line = 0; line < n; ++line)
                {
                    iDir = 4;
                    ChangePos(EPos::bottom, iDir, line, m);
                    for (int k = 0; k < iFour; ++k)
                    {
                        aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                    }
                }

            }
            else // iThree > 0
            {
                //  _ _
                // |
                for (int i = 1; i <= n; ++i)
                {
                    iDir = 1;
                    for (int j = 0; j < i; ++j)
                    {
                        BottomPosition(iDir, m);
                    }
                    aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 2, m)));
                }
                --iThree;

                for (int line = 0; line < n; ++line)
                {
                    iDir = 3;
                    ChangePos(EPos::bottom, iDir, line, m);
                    // ---
                    for (int k = 0; k < iThree; ++k)
                    {
                        aChains.push_back(std::move(GetNLengthStraithChain(iDir, 3)));
                    }
                    // ----
                    for (int k = 0; k < iFour; ++k)
                    {
                        aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                    }
                }

            }
        }
    }
    else if ((n == 4 || n == 5) && m == 5)
    {

        int iDir{};

        //      | 
        //      | m
        //    |_| 
        int iThree{}, iFour{};
        Get4And3LenghtChainsCount(m + 2, iFour, iThree);

        if (iThree == 0)
        {
            iDir = 2;
            for (int j = 0; j < iFour - 1; ++j)
            {
                aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 4, n)));
            }
            aChains.push_back(std::move(Get_i_Bottom_j_Left_k_TopChain(iDir, 2, 1, 1, n)));
        }
        else // iThree != 0
        {
            iDir = 2;
            if (iFour == 0 && iThree > 0)
            {
                while (iThree > 1)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 3, n)));
                    --iThree;
                }
                aChains.push_back(std::move(Get_i_Bottom_j_Left_k_TopChain(iDir, 1, 1, 1, n)));
                --iThree;
            }
            else // iFour != 0
            {
                while (iThree > 0)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 3, n)));
                    --iThree;
                }
                while (iFour > 1)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 4, n)));
                    --iFour;
                }
                aChains.push_back(std::move(Get_i_Bottom_j_Left_k_TopChain(iDir, 2, 1, 1, n)));
            }
        }

        //      | 
        //      | m
        //     _| 
        Get4And3LenghtChainsCount(m + 1, iFour, iThree);
        if (iThree == 0)
        {
            for (int i = 1; i < n - 1; ++i)
            {
                iDir = 2;
                ChangePos(EPos::right, iDir, i, n);
                for (int j = 0; j < iFour - 1; ++j)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 4, n)));
                }
                aChains.push_back(std::move(Get_i_Bottom_j_LeftChain(iDir, 3, 1, n)));
            }
        }
        else // iThree != 0
        {
            for (int i = 1; i < n - 1; ++i)
            {
                iDir = 2;
                ChangePos(EPos::right, iDir, i, n);
                for (int j = 0; j < iFour; ++j)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 4, n)));
                }
                for (int j = 0; j < iThree - 1; ++j)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 3, n)));
                }
                aChains.push_back(std::move(Get_i_Bottom_j_LeftChain(iDir, 2, 1, n)));

            }
        }

        //    _ _n_ _  
        //   |       |
        // 

        iDir = 1;
        BottomPosition(iDir, n);
        for (int i = 0; i < m - 1; ++i)
        {
            Get4And3LenghtChainsCount(n + 2, iFour, iThree);
            iDir = 1;
            ChangePos(EPos::bottom, iDir, i + 1, n);
            if (iThree == 0)
            {
                aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 3, n)));
                for (int i = 0; i < iFour - 1; ++i)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                }
                aChains.push_back(std::move(Get_i_Top_j_Right_k_BottomChain(iDir, 0, 3, 1, n)));
            }
            else // iThree != 0
            {
                aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 2, n)));
                --iThree;
                while (iThree > 1)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 3)));
                    --iThree;
                }
                if (iFour == 0 && iThree == 1)
                {
                    aChains.push_back(std::move(Get_i_Top_j_Right_k_BottomChain(iDir, 0, 2, 1, n)));
                }
                else
                {
                    while (iFour > 1)
                    {
                        aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                        --iFour;
                    }
                    aChains.push_back(std::move(Get_i_Top_j_Right_k_BottomChain(iDir, 0, 3, 1, n)));
                }
            }
        }

        //
        //  _ _n_ _
        //        _| 
        iDir = 1;
        ChangePos(EPos::bottom, iDir, m - 1, n);
        Get4And3LenghtChainsCount(n + 2, iFour, iThree);

        if (iThree == 0)
        {
            while (iFour > 1)
            {
                aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                --iFour;
            }
            aChains.push_back(std::move(Get_i_Right_j_Bottom_k_LeftChain(iDir, 2, 1, 1, n)));
        }
        else // iThree != 0
        {
            if (iFour == 0)
            {
                while (iThree > 1)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 3)));
                    --iThree;
                }
                aChains.push_back(std::move(Get_i_Right_j_Bottom_k_LeftChain(iDir, 1, 1, 1, n)));
            }
            else
            {
                while (iThree > 0)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 3)));
                    --iThree;
                }
                while (iFour > 1)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                    --iFour;
                }
                aChains.push_back(std::move(Get_i_Right_j_Bottom_k_LeftChain(iDir, 2, 1, 1, n)));
            }
        }
    }
    else if (n == 3 && m > 4)
    {
        int iDir{};
        for (int i = 1; i <= m; ++i)
        {
            iDir = 1;
            ChangePos(EPos::right, iDir, i, m);
            aChains.push_back(std::move(Get_i_Bottom_j_LeftChain(iDir, 3, 1, m)));
        }

        for (int i = 1; i <= 3; ++i)
        {
            int iThree{}, iFour{};
            Get4And3LenghtChainsCount(m + 1, iFour, iThree);
            iDir = 1;
            ChangePos(EPos::bottom, iDir, i, m);
            if (iThree == 0)
            {
                aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 3, m)));
                for (int j = 0; j < iFour - 1; ++j)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                }
            }
            else // iThree != 0
            {
                aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 2, m)));
                --iThree;
                while (iThree > 0)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 3)));
                    --iThree;
                }
                while (iFour > 0)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                    --iFour;
                }
            }
        }
    }
    else if ((n == 3 || n == 4) && (m == 3 || m == 4))
    {
        int iDir{};
        for (int i = 0; i <= m; ++i)
        {
            iDir = 1;
            ChangePos(EPos::right, iDir, i, m);
            if (n == 3)
            {
                aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 3, m)));
            }
            else
            {
                aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 4, m)));
            }
        }
        for (int i = 0; i <= n; ++i)
        {
            iDir = 1;
            ChangePos(EPos::bottom, iDir, i, m);
            aChains.push_back(std::move(GetNLengthStraithChain(iDir, m)));
        }
    }
    else if (n > 5 && m > 5)
    {
        int iDir{};

        int iFour{}, iThree{};
        Get4And3LenghtChainsCount(n + 1, iFour, iThree);
        //       _ _n_ _
        //      |     
        //
        if (iThree == 0)
        {
            for (int i = 0; i < m; ++i)
            {
                iDir = 1;
                ChangePos(EPos::bottom, iDir, i + 1, n);
                aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 3, n)));
            }
            --iFour;

            // ----
            for (int line = 0; line < m; ++line)
            {
                iDir = 4;
                ChangePos(EPos::bottom, iDir, line, n);
                for (int k = 0; k < iFour; ++k)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                }
            }
        }
        else // iThree != 0
        {
            for (int i = 0; i < m; ++i)
            {
                iDir = 1;
                ChangePos(EPos::bottom, iDir, i + 1, n);
                aChains.push_back(std::move(Get_i_Top_j_RightChain(iDir, 1, 2, n)));
            }
            --iThree;

            // ----
            for (int line = 0; line < m; ++line)
            {
                iDir = 3;
                ChangePos(EPos::bottom, iDir, line, n);
                for (int k = 0; k < iFour; ++k)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 4)));
                }
                for (int k = 0; k < iThree; ++k)
                {
                    aChains.push_back(std::move(GetNLengthStraithChain(iDir, 3)));
                }
            }
        }

        //      |
        //      | m
        //     _|
        Get4And3LenghtChainsCount(m + 1, iFour, iThree);
        if (iThree == 0)
        {
            for (int i = 1; i <= n; ++i)
            {
                iDir = 1;
                ChangePos(EPos::right, iDir, i, n);
                for (int j = 0; j < iFour - 1; ++j)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 4, n)));
                }
                aChains.push_back(std::move(Get_i_Bottom_j_LeftChain(iDir, 3, 1, n)));

            }
        }
        else // iThree != 0
        {
            for (int i = 1; i <= n; ++i)
            {
                iDir = 1;
                ChangePos(EPos::right, iDir, i, n);
                for (int j = 0; j < iFour; ++j)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 4, n)));
                }
                for (int j = 0; j < iThree - 1; ++j)
                {
                    aChains.push_back(std::move(GetNLengthVerticalChain(iDir, 3, n)));
                }
                aChains.push_back(std::move(Get_i_Bottom_j_LeftChain(iDir, 2, 1, n)));

            }
        }
    }

    return aChains;
}

void PrintMatrix(short** pMatrix, size_t uSize)
{
    std::cout << "\n Adjacency Matrix \n";
    for (size_t i = 0; i < uSize; ++i)
    {
        std::cout << "\t";
        for (size_t j = 0; j < uSize; ++j)
        {
            std::cout << pMatrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void InputNetSizes(int& n, int& m)
{
    std::cout << "Input n x m: \n";
    std::cout << "\tn = ";
    std::cin >> n;
    std::cout << "\tm = ";
    std::cin >> m;

    assert(CheckInput(n, m));

    if (m < n)
    {
        std::swap(n, m);
    }
}

void PrintCreatedChains(std::vector<aSimpleChain>&& aChains)
{
    for (auto& it : aChains)
    {
        for (aSimpleChain::iterator vertex = it.begin(); vertex != std::prev(it.end()); std::advance(vertex, 1))
        {
            std::cout << *vertex << " -> ";
        }
        std::cout << *std::prev(it.end()) << std::endl;
    }

    std::cout << std::endl;
}