#include "constant_medium.h"

aabb constant_medium::bounding_box() const
{
     return boundary->bounding_box();
}
constant_medium::constant_medium(std::shared_ptr<hittable> boundary, float density, std::shared_ptr<texture> tex)
      : boundary(boundary), neg_inv_density(-1/density),
        phase_function(std::make_shared<isotropic>(tex))
    {}

constant_medium::constant_medium(std::shared_ptr<hittable> boundary, float density, const color& albedo)
      : boundary(boundary), neg_inv_density(-1/density),
        phase_function(std::make_shared<isotropic>(albedo))
    {}
bool constant_medium::hit(const ray& r, interval ray_t, hit_record& rec) const {
        hit_record rec1, rec2;

        if (!boundary->hit(r, interval::universe, rec1))
            return false;

        if (!boundary->hit(r, interval(rec1.t+0.0001, infinity), rec2))
            return false;

        if (rec1.t < ray_t.min) rec1.t = ray_t.min;
        if (rec2.t > ray_t.max) rec2.t = ray_t.max;

        if (rec1.t >= rec2.t)
            return false;

        if (rec1.t < 0)
            rec1.t = 0;

        auto ray_length = r.direction().length();
        auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
        auto hit_distance = neg_inv_density * std::log(rand_f());

        if (hit_distance > distance_inside_boundary)
            return false;

        rec.t = rec1.t + hit_distance / ray_length;
        rec.p = r.at(rec.t);

        rec.normal = vec3(1,0,0);  // arbitrary
        rec.front_face = true;     // also arbitrary
        rec.mat = phase_function;

        return true;
    }
