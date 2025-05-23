#include "hittable.h"
#include "rt_common.h"

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal)
{
          // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        front_face = dot(r.direction(), outward_normal) < 0.0f;
        // if >0, its face outside towards camera, otherwise its inside, and facing the same direction
        normal = front_face ? outward_normal : -outward_normal;
};