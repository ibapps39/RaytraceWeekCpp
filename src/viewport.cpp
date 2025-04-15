#include "viewport.hpp"
#include "sphere.h"
viewport::viewport() :
    // set the aspect ration to float precision
    aspect_ratio(float(16.0 / 9.0)),
    // 
    image_width(400),
    // Calculate the image height, and ensure that it's at least 1.
    image_height(int(image_width / aspect_ratio)),
    // Viewport widths <1 are ok since they are real valued.
    viewport_height(float(2.0)),
    viewport_width(
        viewport_height * (float(image_width)/image_height)
    ),
    
    focal_length(1.0f),
    camera_center(point3(0, 0 ,0)),
    viewport_xv(vec3(viewport_width, 0, 0)),
    viewport_yv(vec3(0, -viewport_height, 0)),
    pixel_delta_x(viewport_xv / image_width),
    pixel_delta_y(viewport_yv / image_height),

    viewport_upper_left( camera_center - vec3(0, 0, focal_length) - (viewport_xv/2) - (viewport_yv/2 )),
    pixel00_loc(viewport_upper_left + (pixel_delta_x+pixel_delta_y)/2)
{}
void viewport::render()
{
    image_height = (image_height < 1) ? 1 : image_height;
    viewport_width = viewport_height * (float(image_width)/image_height);
    std::cout << "P3" << std::endl;
    std::cout << image_width << " " << image_height << std::endl;
    std::cout << "255" << std::endl;

    for (int h = 0; h < image_height; h++) {
        std::clog << "\rScanlines remaining: " << (image_height - h) << ' ' << std::flush;
        for (int w = 0; w < image_width; w++) {
            point3 pixel_center = pixel00_loc + (w * pixel_delta_x) + (h * pixel_delta_y);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            //color pixel_color = ray_color(r);
            color pixel_color = sphere_ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}