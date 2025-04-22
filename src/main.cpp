// #include "make_example_ppm.h"
#include "rt_common.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
int main()
{
    //make_example_ppm(0, 255);
    // point3 sphere_one_pos(0, 0, -1);
    // point3 sphere_two_pos(0, -100.5, -1);

    std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    std::shared_ptr<lambertian> material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    // std::shared_ptr<metal> material_left   = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.3f);
    std::shared_ptr<dielectric> material_left   = std::make_shared<dielectric>(1.50);
    std::shared_ptr<metal> material_right       = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0f);
    
    // float radius_sphere_one = 0.5f;
    // float radius_sphere_two = 100.0f;

    // sphere sphere_one(sphere_one_pos, radius_sphere_one);
    // sphere sphere_two(sphere_two_pos, radius_sphere_two);

    hittable_list world;
    // world.add(std::make_shared<sphere>(sphere_one));
    // world.add(std::make_shared<sphere>(sphere_two));
    world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

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