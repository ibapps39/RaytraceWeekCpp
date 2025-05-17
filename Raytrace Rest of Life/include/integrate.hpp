#pragma once
#include "rt_common.h"
#include "iostream"
#include "iomanip"

inline int integrate_monty_avg()
{
    int a = 0;
    int b = 2;
    int N = 100000;
    float sum = 0.0f;

    for (int i = 0; i < N; i++)
    {
        float x = rand_f(a, b);
        sum += x*x;
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "I = " << (b-a)*(sum/N) << std::endl;
}