#include "texture.h"

solid_color::solid_color(const color& albedo) : albedo(albedo)
{}
solid_color::solid_color(float red, float green, float blue) : solid_color(color(red, green, blue))
{}
color solid_color::value(float u, float v, const point3& p) const
{
    return albedo;
}
checker_texture::checker_texture(float scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd)
    : inv_scale(1.0f/scale), even(even), odd(odd)
    {}
checker_texture::checker_texture(float scale, const color& c1, const color& c2) 
    : checker_texture(
        scale, 
        std::make_shared<solid_color>(c1),
        std::make_shared<solid_color>(c2)
    )
    {}
color checker_texture::value(float u, float v, const point3& p) const
{
    int xInt = int( std::floorf( p.x() * inv_scale ) );
    int yInt = int( std::floorf( p.y() * inv_scale ) );
    int zInt = int( std::floorf( p.z() * inv_scale ) );

    bool isEven = (xInt + yInt + zInt) % 2 == 0;

    return isEven ? even->value(u, v, p) : odd->value(u, v, p);
}