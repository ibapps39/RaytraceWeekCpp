#pragma once

#include <iostream>
#include "vec3.hpp"

using color = vec3;

//Convert vector colors from [0,1] to [0,255], write
void write_color(std::ostream& out, const color& pixel_color);
