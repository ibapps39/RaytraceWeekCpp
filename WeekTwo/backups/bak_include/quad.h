#pragma once
#include "rt_common.h"
#include "hittable.h"
class quad : public hittable 
{
    private:
        point3 Q;
        vec3 u, v, w, normal;
        float D;
        std::shared_ptr<material> mat;
        aabb bbox;

    public: 
        quad(const point3& Q, const vec3& u, const vec3& v, std::shared_ptr<material> mat);
        virtual void set_bounding_box()
        {
            aabb bbox_diagional1 = aabb(Q, Q + u + v);
            aabb bbox_diagional2 = aabb(Q + u, Q + v);
            bbox = aabb(bbox_diagional1, bbox_diagional2);
        }
        virtual bool is_interior(float a, float b, hit_record& rec) const;
        aabb bounding_box() const override;
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};