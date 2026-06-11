#pragma once
// NumericLib.h - Header file for the NumericLib library
#ifdef NUMERICLIB_EXPORTS
#define NUMERICLIB_API __declspec(dllexport)
#else
#define NUMERICLIB_API __declspec(dllimport)
#endif

typedef double (__cdecl *function)(double);

// Function declarations for the NumericLib library
extern "C" {
	NUMERICLIB_API double mean(const double* values, int count);
	NUMERICLIB_API double standard_deviation(const double* values, int count);
	NUMERICLIB_API double integrate(function f, double a, double b, int count);
}