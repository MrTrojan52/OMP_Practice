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

    std::vector<int8_t> nPrimeNumbers(nMaxVectorSize + 1, true);
    nPrimeNumbers[0] = nPrimeNumbers[1] = false;

    ull nSqrtLimit = static_cast<size_t>(sqrt(nMaxVectorSize));

    std::cout << "Max threads: " << omp_get_max_threads() << std::endl;
    std::cout << "Max vector size: " << nMaxVectorSize << std::endl;

    double dStartTime = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (ull i = 2; i <= nSqrtLimit; ++i)
    {
        if (nPrimeNumbers[i])
        {
            for (ull j = i * i; j <= nMaxVectorSize; j += i)
            {
                nPrimeNumbers[j] = false;
            }
        }
    }

    double dEndTime = omp_get_wtime();


    std::cout << "Prime numbers founded in " << (dEndTime - dStartTime) << " second(s)" << std::endl;
    std::cout << "Count: " << std::count(nPrimeNumbers.begin(), nPrimeNumbers.end(), true) << std::endl;
    return 0;
}
