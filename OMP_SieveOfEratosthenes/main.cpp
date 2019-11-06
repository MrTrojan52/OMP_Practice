#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "omp.h"

using ull = unsigned long long;

int main(int argc, char* argv[])
{
    ull nMaxVectorSize = 100'000'000;
    if (argc >= 2)
    {
        long nSize = std::stol(argv[1]);
        if (nSize > 0)
        {
            nMaxVectorSize = nSize;
        }
    }

    std::vector<bool> bPrimeNumbers(nMaxVectorSize + 1, true);
    bPrimeNumbers[0] = bPrimeNumbers[1] = false;

    ull nSqrtLimit = static_cast<size_t>(sqrt(nMaxVectorSize));

    std::cout << "Max threads: " << omp_get_max_threads() << std::endl;
    std::cout << "Max vector size: " << nMaxVectorSize << std::endl;

    double dStartTime = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (ull i = 2; i <= nSqrtLimit; ++i)
    {
        if (bPrimeNumbers[i])
        {
            for (ull j = i * i; j <= nMaxVectorSize; j += i)
            {
                bPrimeNumbers[j] = false;
            }
        }
    }

    double dEndTime = omp_get_wtime();


    std::cout << "Prime numbers founded in " << (dEndTime - dStartTime) << " second(s)" << std::endl;
    std::cout << "Count: " << std::count(bPrimeNumbers.begin(), bPrimeNumbers.end(), true) << std::endl;
    return 0;
}