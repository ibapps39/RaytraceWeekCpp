#include "ray.hpp"

const point3& ray::origin() const  { return origin_; }
const vec3& ray::direction() const { return direction_; }

ray::ray()
{}
ray::ray(const point3& origin, const vec3& direction) : origin_(origin), direction_(direction)
{}
point3 ray::at(double t) const {
    return origin_ + t*direction_;
}
color ray::ray_color(const ray& r)
{
    return color(0,0,0);
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
  