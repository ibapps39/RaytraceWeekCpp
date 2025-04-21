#include "camera.h"

void camera::initialize()
{
    
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    px_sample_scale = 1.0f / samples_per_px;

    camera_center = point3(0, 0, 0);

    // Determine viewport dimensions.
    focal_length = 1.0;
    viewport_height = 2.0;
    viewport_width = viewport_height * (float(image_width) / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewport_x = vec3(viewport_width, 0, 0);
    viewport_y = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_x = viewport_x / image_width;
    pixel_delta_y = viewport_y / image_height;

    // Calculate the location of the upper left pixel.
    point3 viewport_upper_left =
        camera_center - vec3(0, 0, focal_length) - viewport_x / 2 - viewport_y / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_x + pixel_delta_y);
    max_depth = 10;
}

color camera::ray_color(const ray &r, int depth, const hittable &world) const
{
    if (depth <= 0)
    {
        return color(0,0,0);
    }
    hit_record rec;
    if (world.hit(r, interval(0.001, infinity), rec))
    {
        vec3 dir = rec.normal + rand_unit_vec();
        return 0.5 * ray_color(ray(rec.p, dir), depth-1, world);
    }

    vec3 unit_direction = unit_vector(r.direction());
    float a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
//Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
vec3 camera::sample_square() const
{
    return vec3(rand_f() - 0.5f, rand_f() - 0.5f, 0);
}
// Construct a camera ray originating from the origin and directed at randomly sampled point around the pixel location h, w.
ray camera::get_ray(int h, int w) const
{

        // get ideal square sample
        vec3 offset = sample_square();
        vec3 px_sample = pixel00_loc 
                        + ((w + offset.x()) * pixel_delta_x)
                        + ((h + offset.y()) * pixel_delta_y);
        vec3 ray_origin = camera_center;
        vec3 ray_direction = px_sample - ray_origin;
        return ray(ray_origin, ray_direction);
}
void camera::render(const hittable &world)
{
    initialize();
    image_height = (image_height < 1) ? 1 : image_height;
    viewport_width = viewport_height * (float(image_width) / image_height);
    std::cout << "P3" << std::endl;
    std::cout << image_width << " " << image_height << std::endl;
    std::cout << "255" << std::endl;

    for (int h = 0; h < image_height; h++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - h) << ' ' << std::flush;
        for (int w = 0; w < image_width; w++)
            {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_px; sample++)
                {
                    ray r = get_ray(h, w);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, px_sample_scale*pixel_color); 
            }
    }
    std::clog << "\rDone.                 \n";
}
