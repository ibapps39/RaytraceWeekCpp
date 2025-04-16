#include "ray.hpp"

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


/////
// class ray
// {
//     private:
//         point3 origin;
//         vec3 direction;
//     public:
//     ray() {}
//     ray(point3 origin, const vec3& direction);
//     color ray_color(const ray& r) {}
    
//     const point3 origin() const;
//     const vec3& direction() const;
//     point3 at(float t) const;
    
// };

// class ray {
//     public:
//       ray() {}
  
//       ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
  
//       const point3& origin() const  { return orig; }
//       const vec3& direction() const { return dir; }
  
//       point3 at(double t) const {
//           return orig + t*dir;
//       }
  
//     private:
//       point3 orig;
//       vec3 dir;
//   };
  