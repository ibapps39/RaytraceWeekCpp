#pragma once
#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

//bool hit_sphere(const point3& center, float radius, const ray& r);
float hit_sphere(const point3& center, float radius, const ray& r);

color sphere_ray_color(const ray& r);