#include "material.h"

lambertian::lambertian(const color& albedo) : albedo(albedo){}
bool lambertian::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const 
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
metal::metal(const color& albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
bool metal::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    vec3 reflected = reflect(ray_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz*rand_unit_vec());
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(float refract_index) : refract_index(refract_index){}
bool dielectric::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    attenuation = color(1.0, 1.0, 1.0);
    float ri = rec.front_face ? (1.0/refract_index) : refract_index;

    vec3 unit_direction = unit_vector(ray_in.direction());
    vec3 refracted = refract(unit_direction, rec.normal, ri);

    scattered = ray(rec.p, refracted);
    return true;

}