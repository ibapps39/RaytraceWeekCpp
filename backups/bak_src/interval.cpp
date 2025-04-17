#include "interval.h"

interval::interval() : min(+infinity), max(-infinity) {}
interval::interval(float min, float max) : min(min), max(max) {}

float interval::size() const
{
    return max-min;
}
bool interval::contains(float x) const
{
    return (min <= x) && (x <= max);
}
bool interval::surrounds(float x) const
{
    return (min < x) && (x < max);
}

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);