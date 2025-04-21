#pragma once

// #include <iostream>
#include "interval.h"
#include "vec3.h"

using color = vec3;

// Convert color from linear space to gamma
float linear_to_gamma(float linear_component);
//Convert vector colors from [0,1] to [0,255], write
void write_color(std::ostream& out, const color& pixel_color);

