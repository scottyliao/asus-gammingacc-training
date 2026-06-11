#define NUMERICLIB_EXPORTS
#include "NumericLib.h"
#include <cmath>

// Implementations of the functions declared in NumericLib.h
double mean(const double* values, int count)
{
    if (values == nullptr || count <= 0)
    {
        return 0.0;
    }

    double sum = 0.0;

    for (int i = 0; i < count; ++i)
    {
        sum += values[i];
    }

    return sum / count;
}

double standard_deviation(const double* values, int count)
{
    if (values == nullptr || count <= 1)
    {
        return 0.0;
    }
    double variance = 0.0;

    for (int i = 0; i < count; ++i)
    {
        double diff = values[i] - mean(values, count);
        variance += diff * diff;
    }

    variance /= count;

    return std::sqrt(variance);
}

// Implementation of the integrate function using the trapezoidal rule
double integrate(function f, double a, double b, int count) {
    if (f == nullptr || count <= 0) return 0.0;

    double h = (b - a) / count;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < count; ++i) {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}