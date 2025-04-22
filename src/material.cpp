#include "material.h"

lambertain::lambertain(const color& albedo) : albedo(albedo){}
bool lambertain::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const 
{
    vec3 scatter_dir = rec.normal + rand_unit_vec();
    if (scatter_dir.near_zero())
    {
        scatter_dir = rec.normal;
    }
    scattered = ray(rec.p, scatter_dir);
    attenuation = albedo;
    return true;
}
metal::metal(const color& albedo) : albedo(albedo){}
bool metal::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    vec3 reflected = reflect(ray_in.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
}
