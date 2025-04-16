#include "vec3.hpp"
#include "ray.hpp"
class hit_record
{
    public:
        point3 p;
        vec3 normal;
        float t;
        bool front_face;
        void set_face_normal(const ray& r, const vec3& outward_normal);
};

class hittable 
{
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const = 0;
};