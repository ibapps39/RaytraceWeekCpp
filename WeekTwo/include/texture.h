#pragma once
#include "color.h"
class texture 
{
    public:
        virtual ~texture() = default;
        virtual color value(float u, float v, const point3& p) const = 0;
};
class solid_color : public texture
{
    private:
        color albedo;

    public:
        solid_color(const color& albedo);
        solid_color(float red, float green, float blue);
        color value(float u, float v, const point3& p) const override;
};