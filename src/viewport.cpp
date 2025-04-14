#include "viewport.hpp"

viewport::viewport() :
    aspect_ratio(16.0f/9.0f),
    image_width(400),
    image_height(int(image_width / aspect_ratio)),
    
    focal_length(1.0f),
    viewport_height(2.0f),
    viewport_width(viewport_height * (float(image_width)/image_height)),

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
    std::cout << "P3" << std::endl;
    std::cout << image_width << " " << image_height << std::endl;
    std::cout << "255" << std::endl;

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_x) + (j * pixel_delta_y);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}
// class viewport 
// {
//     public:
//         int image_width = 400;
//         int image_height = (int(image_width)/(aspect_ratio) < 1) ? 1 : int(image_width)/(aspect_ratio);

//         float aspect_ratio = 16.0f / 9.0f;
//         float focal_length = 400;

//         float viewport_height = 2.0f;
//         float viewport_width = viewport_height * (float(image_width)/image_height);

//         point3 camera_center = point3(0.0f, 0.0f, 0.0f);

//         vec3 viewport_xv = vec3(viewport_width, 0, 0);
//         vec3 viewport_yv = vec3(0, -viewport_height, 0);
//         vec3 pixel_delta_x = viewport_xv / image_width;
//         vec3 pixel_delta_y = viewport_yv / image_height;

//         // Calculate the location of the upper left pixel.
//         vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_xv/2 - viewport_yv/2;
//         point3 pixel00_loc = viewport_upper_left + (pixel_delta_x+pixel_delta_y)/2;

//         void viewport::render()
//         {
//             std::cout << "P3" << std::endl;
//             std::cout << MAX_P3_COLOR_SIZE << std::endl;
//             std::cout << image_width << " " << image_height << std::endl;
//             for (size_t i = 0; i < image_height; i++) 
//             {
//                 std::clog << "\rScanlines remaining: " << (image_height-i) << " " << std::flush;
//                 for (size_t j = 0; j < image_width; j++)
//                 {
//                     point3 pixel_center = pixel00_loc + (j*pixel_delta_x) + (i*pixel_delta_y);
//                     vec3 ray_direction = pixel_center - camera_center;
//                     ray r(camera_center, ray_direction);
//                     color pixel_color = 
//                 }
//             }
        
//         }
// };