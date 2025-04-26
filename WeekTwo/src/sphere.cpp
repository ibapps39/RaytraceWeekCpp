#include "sphere.h"

sphere::sphere(const point3& center_pos, float radius, std::shared_ptr<material> mat) : 
center_pos(center_pos), 
radius(std::fmaxf(0.0f, radius)),
mat(mat)
{}

bool sphere::hit(const ray& r, interval ray_t, hit_record& hit_rec) const 
{
    vec3 center_to_surface = center_pos-r.origin();
    float a = r.direction().length_squared();
    float h = dot(r.direction(), center_to_surface);
    float c = center_to_surface.length_squared() - (radius*radius);
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
    vec3 outward_normal = (hit_rec.p - center_pos) / radius;
    // record a hit and by how much, and if a surface. Records surface normals
    hit_rec.set_face_normal(r, outward_normal);
    hit_rec.mat = mat;
    return true;
}
