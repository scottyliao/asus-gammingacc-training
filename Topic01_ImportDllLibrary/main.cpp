#include <iostream>
#include <iomanip>
#include <windows.h>
// Include the header file for the NumericLib library
#include "NumericLib.h"

// Implicit link with the NumericLib library
#pragma comment(lib, "NumericLib.lib")

int main()
{
    double data[] = {
        10.0, 12.0, 13.0, 15.0, 20.0
    };

    int count = sizeof(data) / sizeof(data[0]);

	// Call mean and standard_deviation functions from the NumericLib library
    double _mean = mean(data, count);
    double stddev = standard_deviation(data, count);

	// Display the results and format the output
	std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(20) << "Mean" << "= " << _mean << std::endl;
    std::cout << std::left << std::setw(20) << "Standard deviation"<< "= " << stddev << std::endl;
    return 0;
}