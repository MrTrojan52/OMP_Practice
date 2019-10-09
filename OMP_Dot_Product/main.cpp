#include <iostream>
#include <omp.h>
#include <vector>

long long GetDotProduct(std::vector<int>& rFirst, std::vector<int>& rSecond)
{
    long long lDotProduct = 0;
    if (rFirst.size() != rSecond.size())
    {
        throw std::invalid_argument("Vectors must be the same size!");
    }

    double dStartTime = omp_get_wtime();

    #pragma omp parallel for default(none) shared(rFirst, rSecond) reduction(+:lDotProduct)
    for (size_t i = 0; i < rFirst.size(); ++i)
    {
        lDotProduct += (static_cast<long long>(rFirst[i]) * rSecond[i]);
    }

    double dEndTime = omp_get_wtime();

    std::cout << "Dot product was calculated in " << (dEndTime - dStartTime) << " second(s)" << std::endl;

    return lDotProduct;
}


int main(int argc, char* argv[])
{
    size_t nMaxVectorSize = 1'000'000;
    if (argc >= 2)
    {
        long nSize = std::stol(argv[1]);
        if (nSize > 0)
        {
            nMaxVectorSize = nSize;
        }
    }


    std::vector<int> vFirst(nMaxVectorSize);
    std::vector<int> vSecond(nMaxVectorSize);

    std::cout << "Max threads: " << omp_get_max_threads() << std::endl;
    std::cout << "Max vector size: " << nMaxVectorSize << std::endl;

    double dStartTime = omp_get_wtime();

    #pragma omp parallel for default(none) shared(vFirst, vSecond, nMaxVectorSize)
    for (size_t i = 0; i < nMaxVectorSize; ++i)
    {
        vFirst[i] = i;
        vSecond[i] = i;
    }

    double dEndTime = omp_get_wtime();

    std::cout << "Vectors are filled with numbers in " << (dEndTime - dStartTime) << " second(s)" << std::endl;

    long long lDotProduct = GetDotProduct(vFirst, vSecond);

    std::cout << "Dot product: " << lDotProduct << std::endl;

    return 0;
}