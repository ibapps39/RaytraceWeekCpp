#pragma once
// #include "vec3.h"
// #include "ray.h"
#include "rt_common.h"

// Needs to be set for calculating height. Currently 800.0f
#define DEFAULT_VIEW_WIDTH (800.0f)
// 1.77777777778f
#define HARDCODED_ASPECT_RATIO (16.0f / 9.0f)
// DEFAULT_VIEW_WIDTH / (HARDCODED_ASPECT_RATIO). Easier to maintain desired aspect ration if calculated
#define DEFAULT_VIEW_HEIGHT ( (DEFAULT_VIEW_WIDTH) / (HARDCODED_ASPECT_RATIO) )
// 1.77777777778f
#define HARDCODED_ASPECT_RATIO_VALUE 1.77777777778f
// 16:9 ~= 1.77..8
#define DEFAULT_ASPECT_RATIO ( (DEFAULT_VIEW_WIDTH) / (DEFAULT_VIEW_HEIGHT) )

#define MAX_P3_COLOR_SIZE 255

void make_viewport();

class viewport
{
    private:
        //
        float aspect_ratio;
        //
        int image_width;
        // Calculate the image height, and ensure that it's at least 1.
        int image_height;
        // Viewport widths less than one are ok since they are real valued.
        float viewport_height;
        float viewport_width;
        //
        float focal_length;
        point3 camera_center;
        //
        vec3 viewport_xv;
        vec3 viewport_yv;
        //
        vec3 pixel_delta_x;
        vec3 pixel_delta_y;
        //
        vec3 viewport_upper_left;
        //
        point3 pixel00_loc;

    public:
        // Constructor
        viewport();
        void render();
};


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