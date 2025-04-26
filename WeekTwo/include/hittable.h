#pragma once
#include "rt_common.h"
class material;
class hit_record
{
    public:
        point3 p;
        vec3 normal;
        std::shared_ptr<material> mat;
        float t;
        bool front_face;
        void set_face_normal(const ray& r, const vec3& outward_normal);
};

class hittable 
{
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};