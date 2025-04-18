#pragma once
// #include "vec3.h"
// #include "color.h"
// #include "ray.h"
#include "rt_common.h"
#include "hittable.h"

class sphere : public hittable
{
    private:
        point3 center_pos;
        float radius;
    public:
        sphere(const point3& center_pos, float radius);
        bool hit(const ray& r, interval ray_t, hit_record& hit_rec) const override;
};
float hit_sphere(const point3& center, float radius, const ray& r);
color sphere_ray_color(const ray& r);

// bool hit(const ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const override;
// class sphere : public hittable {
//     public:
//       bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
//           vec3 oc = center - r.origin();
//           auto a = r.direction().length_squared();
//           auto h = dot(r.direction(), oc);
//           auto c = oc.length_squared() - radius*radius;
  
//           auto discriminant = h*h - a*c;
//           if (discriminant < 0)
//               return false;
  
//           auto sqrtd = std::sqrt(discriminant);
  
//           // Find the nearest root that lies in the acceptable range.
//           auto root = (h - sqrtd) / a;
//           if (root <= ray_tmin || ray_tmax <= root) {
//               root = (h + sqrtd) / a;
//               if (root <= ray_tmin || ray_tmax <= root)
//                   return false;
//           }
  
//           rec.t = root;
//           rec.p = r.at(rec.t);
//           rec.normal = (rec.p - center) / radius;
  
//           return true;
//       }
  
//     private:
//       point3 center;
//       double radius;
//   };
  
//bool hit_sphere(const point3& center, float radius, const ray& r);
// float hit_sphere(const point3& center, float radius, const ray& r);

// color sphere_ray_color(const ray& r);