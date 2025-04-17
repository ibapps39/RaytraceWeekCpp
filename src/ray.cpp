#include "ray.h"

const point3& ray::origin() const  { return origin_; }
const vec3& ray::direction() const { return direction_; }

ray::ray()
{}
ray::ray(const point3& origin, const vec3& direction) : origin_(origin), direction_(direction)
{}
point3 ray::at(float t) const {
    return origin_ + t*direction_;
}


color ray_color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());
    float a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    
}
  