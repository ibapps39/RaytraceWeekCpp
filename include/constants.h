#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

#include "vec3.h"
#include "color.h"
#include "ray.h"
// using std::make_shared;
// using std::shared_ptr;

const float infinity = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;

inline float degrees_to_radians(float degrees)
{
    return (degrees*(float)pi) / 180.0f;
}