#pragma once
#include "hittable.h"

class material
{
    public:
        virtual ~material() = default;
        virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const
        {
            return false;
        };
};

class lambertain : public material {
    private:
        color albedo;
    public:
        lambertain(const color& albedo);
        bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};

class metal : public material {
    private:
        color albedo;
    public:
    metal(const color& albedo);
    bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};