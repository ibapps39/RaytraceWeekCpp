#include "make_example_ppm.hpp"

void make_example_ppm(unsigned char min_val, unsigned char max_val)
{
    uint image_width = 250;
    uint image_height = 250;

    unsigned char rgb_max_value = max_val;
    //unsigned char rgb_min_value = min_val;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n" << int(rgb_max_value) << "\n";
    for (size_t j = 0; j<image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << "\n" << std::flush;
        for (size_t i = 0; i<image_width; i++)
        {
            int r = int(float(i)/(image_width-1) * (rgb_max_value+0.999));
            int g = int(float(j)/(image_height-1) * (rgb_max_value+0.999));
            int b = int(float(i+j)/(image_width-1)) * (rgb_max_value+0.999);

            std::cout << r << ' ' << g << ' ' << b << std::endl;
        }
    }
    std::clog << "\rDone.                 \n";
}