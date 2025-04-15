#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "viewport.hpp"
#include "make_example_ppm.hpp"
int main()
{
    //make_example_ppm(0, 255);
     viewport vp;
     vp.render();
    return 0;
}