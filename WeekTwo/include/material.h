#pragma once
#include "hittable.h"
#include "texture.h"
class material
{
    public:
        virtual ~material() = default;
        virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const
        {
            return false;
        };
};

class lambertian : public material {
    private:
        color albedo;
        std::shared_ptr<texture> tex;
    public:
        lambertian(const color& albedo);
        lambertian(std::shared_ptr<texture> tex);
        bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};

class metal : public material {
    private:
        color albedo;
        float fuzz;
    public:
        metal(const color& albedo, float fuzz);
        bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};

class dielectric: public material {
    private:
        float refract_index;
        static float reflectance(float cosine, float refraction_index);
    public:
        dielectric(float refract_index);
        bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};