// #include "color.h"
// #include "ray.h"
// #include "vec3.h"
#include "viewport.h"
// #include "make_example_ppm.h"
#include "rt_common.h"
#include "hittable.h"
//#include "hittable_list.h"
#include "sphere.h"
int main()
{
    //make_example_ppm(0, 255);
     viewport vp;
     vp.render();
    return 0;
}