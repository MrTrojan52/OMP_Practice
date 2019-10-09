#include <iostream>
#include <omp.h>

#define LOG(x) std::cout << #x " = " << x << std::endl

using UNARY_DOUBLE = double (*)(double);

long double CalcIntegral(double dA, double dB, double dAccuracy, UNARY_DOUBLE f)
{
    long double dIntegralSum = 0;
    int nStepsCount = static_cast<int>((dB - dA) / dAccuracy);

    double dStartTime = omp_get_wtime();

    #pragma omp parallel for default(shared) reduction(+:dIntegralSum)
    for (size_t i = 0; i <= nStepsCount; ++i)
    {
        dIntegralSum += (f(dA + dAccuracy * i) + f(dA + dAccuracy * (i + 1)));
    }
    dIntegralSum = (dIntegralSum * dAccuracy) / 2;

    double dEndTime = omp_get_wtime();

    std::cout << "Integral was calculated in " << (dEndTime - dStartTime) << " second(s)" << std::endl;

    return dIntegralSum;
}


int main(int argc, char** argv)
{
    double A = 1;
    double B = 15;
    double Accuracy = 0.0001;

    if (argc >= 4)
    {
        A = std::stod(argv[1]);
        B = std::stod(argv[2]);
        double dAcc = std::stod(argv[3]);
        if (dAcc > 0)
        {
            Accuracy = dAcc;
        }
    }

    std::cout << "Max threads: " << omp_get_max_threads() << std::endl;
    
    LOG(A);
    LOG(B);
    LOG(Accuracy);

    long double IntegralValue = CalcIntegral(A, B, Accuracy, [](double x) { return x; });

    std::cout << std::scientific;
    LOG(IntegralValue);

    return 0;
}