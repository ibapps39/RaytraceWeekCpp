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

aabb translate::bounding_box() const 
{
  return bbox;
}

translate::translate(std::shared_ptr<hittable> object, const vec3& offset) : 
  object(object), offset(offset)
{
  bbox = translate::object->bounding_box() + offset;
}

bool translate::hit(const ray& r, interval ray_t, hit_record& rec) const 
{
        // Move the ray backwards by the offset
        ray offset_r(r.origin() - offset, r.direction(), r.time());

        // Determine whether an intersection exists along the offset ray (and if so, where)
        if (!object->hit(offset_r, ray_t, rec))
            return false;

        // Move the intersection point forwards by the offset
        rec.p += offset;

        return true;
    }
