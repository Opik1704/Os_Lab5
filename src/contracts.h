#ifndef CONTRACTS_H
#define CONTRACTS_H
#include <stddef.h>

#if defined(_WIN32) && defined(BUILDING_LIBRARY)
#define LIBRARY_API __declspec(dllexport)
#elif defined(_WIN32) && defined(USING_LIBRARY)
#define LIBRARY_API __declspec(dllimport)
#else
#define LIBRARY_API
#endif

typedef float (*PiFunction)(int);
typedef int* (*SortFunction)(int*);

LIBRARY_API float Pi(int K);
LIBRARY_API int* Sort(int* array);

#endif
