#pragma once
#include "hittable.h"

class sphere : public hittable
{
    private:
        point3 center_pos;
        float radius;
        std::shared_ptr<material> mat;
    public:
        sphere(const point3& center_pos, float radius, std::shared_ptr<material> mat);
        bool hit(const ray& r, interval ray_t, hit_record& hit_rec) const override;
};
float hit_sphere(const point3& center, float radius, const ray& r);
color sphere_ray_color(const ray& r);