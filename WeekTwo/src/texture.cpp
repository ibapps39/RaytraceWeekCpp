#include "texture.h"

solid_color::solid_color(const color& albedo) : albedo(albedo)
{}
solid_color::solid_color(float red, float green, float blue) : solid_color(color(red, green, blue))
{}
color solid_color::value(float u, float v, const point3& p) const
{}