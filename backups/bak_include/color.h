#pragma once

// #include <iostream>
#include "vec3.h"
#include "rt_common.h"

using color = vec3;

//Convert vector colors from [0,1] to [0,255], write
void write_color(std::ostream& out, const color& pixel_color);
