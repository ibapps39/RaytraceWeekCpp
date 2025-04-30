#include "sphere.h"

sphere::sphere(const point3 &static_center, float radius, std::shared_ptr<material> mat) : 
displacement_ray(static_center, vec3(0, 0, 0)), radius(std::fmax(0, radius)), mat(mat)
{}
sphere::sphere(const point3 &center1, const point3 &center2, float radius, std::shared_ptr<material> mat) : 
displacement_ray(center1, center2-center1), radius(std::fmax(0, radius)), mat(mat)
{}

bool sphere::hit(const ray& r, interval ray_t, hit_record& hit_rec) const 
{
    point3 current_center = displacement_ray.at(r.time());
    vec3 oc = current_center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    float discriminant = h*h - a*c;

    if (discriminant < 0) { return false; }

    float sqrt_det = std::sqrtf(discriminant);
    float root = (h - sqrt_det) / a;
    if (!ray_t.surrounds(root))
    {
        root = (h + sqrt_det)/a;
        if (!ray_t.surrounds(root))
        {
            return false;
        }
    }
    hit_rec.t = root;
    //hit position
    hit_rec.p = r.at(hit_rec.t);
    // Sphere, so can norm. w/radius
    vec3 outward_normal = (hit_rec.p - current_center) / radius;
    // record a hit and by how much, and if a surface. Records surface normals
    hit_rec.set_face_normal(r, outward_normal);
    hit_rec.mat = mat;
    return true;
}
