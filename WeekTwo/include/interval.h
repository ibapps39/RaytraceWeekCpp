
#pragma once
#include "rt_common.h"

class interval 
{
    public:
        float min, max;
        interval();
        interval(float min, float max);
        interval(const interval& a, const interval& b);
        float size() const;
        bool contains(float x) const;
        bool surrounds(float x) const;

        float clamp(float x) const;
        interval expand(float delta) const;
        static const interval empty, universe;
};