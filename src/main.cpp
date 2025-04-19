// #include "make_example_ppm.h"
#include "rt_common.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
//#include "material.h"
#include "sphere.h"
int main()
{
    //make_example_ppm(0, 255);
    point3 sphere_one_pos(0, 0, -1);
    point3 sphere_two_pos(0, -100.5, -1);
    
    float radius_sphere_one = 0.5f;
    float radius_sphere_two = 100.0f;

    sphere sphere_one(sphere_one_pos, radius_sphere_one);
    sphere sphere_two(sphere_two_pos, radius_sphere_two);

    hittable_list world;
    world.add(std::make_shared<sphere>(sphere_one));
    world.add(std::make_shared<sphere>(sphere_two));

    camera cam;
    cam.aspect_ratio = float(16.0f/9.0f);
    cam.image_width = 400;
    cam.samples_per_px = 100;
    cam.max_depth = 50;
    // int md;
    // std::cin >> md;
    // std::clog << "Enter max_depth: " << std::endl;;
    // cam.max_depth = md;

    cam.render(world);

    return 0;
}