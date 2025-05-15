#include "material.h"

lambertian::lambertian(const color& albedo) : tex(std::make_shared<solid_color>(albedo)) {}
lambertian::lambertian(std::shared_ptr<texture> tex) : tex(tex) {}



bool lambertian::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const 
{
    vec3 scatter_dir = rec.normal + rand_unit_vec();
    if (scatter_dir.near_zero())
    {
        scatter_dir = rec.normal;
    }
    scattered = ray(rec.p, scatter_dir, ray_in.time());
    attenuation = tex->value(rec.u, rec.v, rec.p);
    return true;
}
metal::metal(const color& albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
bool metal::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    vec3 reflected = reflect(ray_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz*rand_unit_vec());
    scattered = ray(rec.p, reflected, ray_in.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(float refract_index) : refract_index(refract_index){}
float dielectric::reflectance(float cosine, float refraction_index)
{
        float r0 = (1 - refraction_index) / (1+refraction_index);
        r0 = r0*r0;
        return r0 + (1/r0)*std::powf((1-cosine), 5);
}
bool dielectric::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    attenuation = color(1.0, 1.0, 1.0);
    float ri = rec.front_face ? (1.0/refract_index) : refract_index;
    
    vec3 unit_direction = unit_vector(ray_in.direction());
    float cos_theta = std::fminf(dot(-unit_direction, rec.normal), 1.0f);
    float sin_theta = std::sqrtf(1.0f - cos_theta*cos_theta);
    
    bool cannot_refract = ri * sin_theta > 1.0;
    vec3 direction;
    if ( cannot_refract )
    {
        direction = reflect(unit_direction, rec.normal);
    } 
    else 
    {
        direction = refract(unit_direction, rec.normal, ri);
    }

    scattered = ray(rec.p, direction, ray_in.time());
    return true;

}

bool isotropic::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const {
            scattered = ray(rec.p, rand_unit_vec(), r_in.time());
            attenuation = tex->value(rec.u, rec.v, rec.p);
            return true;
        }
isotropic::isotropic(const color& albedo) : tex(std::make_shared<solid_color>(albedo)) {}
isotropic::isotropic(std::shared_ptr<texture> tex) : tex(tex) {}