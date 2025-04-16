#include "sphere.h"


sphere::sphere(const point3& center_pos, float radius) : center_pos(center_pos), radius(std::fmaxf(0.0f, radius))
{}

bool sphere::hit(const ray& r, float ray_tmin, float ray_tmax, hit_record& hit_rec) const 
{
    vec3 center_to_surface = center_pos-r.origin();
    float a = r.direction().length_squared();
    float h = dot(r.direction(), center_to_surface);
    float c = center_to_surface.length_squared() - (radius*radius);
    float discriminant = h*h - a*c;

    if (discriminant < 0) { return false; }

    float sqrt_det = std::sqrtf(discriminant);

    float root = (h - sqrt_det) / a;
    bool outsideCircle = (root <= ray_tmin || root >= ray_tmax);
    if (outsideCircle)
    {
        root = (h + sqrt_det)/a;
        if (outsideCircle)
        {
            return false;
        }
    }
    hit_rec.t = root;
    hit_rec.p = r.at(hit_rec.t);
    hit_rec.normal = (hit_rec.p - center_pos) / radius;
    vec3 outward_normal = (hit_rec.p - center_pos) / radius;
    hit_rec.set_face_normal(r, outward_normal);
    return true;
}

// bool hit_sphere(const point3& center, float radius, const ray& r)
// {
//     vec3 ray_to_center = center - (r.origin()); // C-P
//     float a = dot(r.direction(), r.direction());
//     float b = -2.0f * dot(r.direction(), ray_to_center);
//     float c = dot(ray_to_center, ray_to_center) - (radius*radius);
//     float discriminant =(b*b) - (4*a*c);
//     return (discriminant >= 0); // 1 or 2 roots
    
// }
float hit_sphere(const point3& center, float radius, const ray& r)
{
    vec3 ray_to_center = center - (r.origin()); // C-P
    float a = r.direction().length_squared(); // v dot v == (v_length)^2
    float h = dot(r.direction(), ray_to_center); // dir dot dist
    float c = ray_to_center.length_squared() - (radius*radius);
    float discriminant = (h*h) - (a*c);
    if (discriminant < 0 )
    {
        return -1.0f;
    } else {
        return ( h - std::sqrtf(discriminant) ) / float(a);
    }
}

color sphere_ray_color(const ray& r)
{
    vec3 sphere_pos = vec3(0,0,-1);
    float sphere_r = 0.5;
    float t = hit_sphere(sphere_pos, sphere_r, r);
    if (t > 0.0f) 
    {
        /// N = unit length vec
        vec3 N = unit_vector(r.at(t) - sphere_pos); // P(t) - C term
        return 0.5 * color(N.x()+1, N.y()+1, N.z()+1); // map xyz to rgb
    }
    vec3 unit_direction = unit_vector(r.direction());
    float alpha = 0.5f * (unit_direction.y() + 1.0);
    color startColor = color(1.0, 1.0, 1.0);
    color endColor = color(0.5, 0.7, 1.0);
    return (1.0-alpha)*startColor + alpha*endColor; // (lerp), (1-alpha)*startColor+alpha(endColor)
}
