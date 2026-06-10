#pragma once
#define WIN32_LEAN_AND_MEAN           
#include <windows.h>
#ifdef MATH_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

extern "C" {
    MATH_API int evk(int base, int mod);
    MATH_API int extendEvk(int a, int b, char ret);
    MATH_API int sqrtZ(int m);
}