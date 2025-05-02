#pragma once
#include "interval.h"
class aabb
{
    public:
        interval x,y,z;

        aabb();
        aabb(const interval& x, const interval& y, const interval& z);
        aabb(const point3& a, const point3& b);
        aabb(const aabb& box_a, const aabb& box_b);

        const interval& axis_interval (int n) const;

        bool hit(const ray& r, interval ray_t) const;

};