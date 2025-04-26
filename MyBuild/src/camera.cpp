#include "camera.h"

void camera::initialize()
{
    
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    
    px_sample_scale = 1.0f / samples_per_px;

    camera_center = lookfrom;

    cam_z = unit_vector(lookfrom-lookat);
    cam_x = unit_vector(cross(camera_up, cam_z));
    cam_y = cross(cam_z, cam_x); // already a unit vector since cam_z and cam_x are.

    // Determine viewport dimensions.
    //focal_length = (lookat-lookfrom).length();
    camera_theta = (float)degrees_to_radians(vfov);
    camera_height = std::tanf(camera_theta/2.0f);
    //viewport_height = 2.0f * camera_height * focal_length;
    viewport_height = 2.0f * camera_height * focus_dist;
    viewport_width = viewport_height * (float(image_width) / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewport_x = viewport_width * cam_x;
    viewport_y = viewport_height * -cam_y;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_x = viewport_x / image_width;
    pixel_delta_y = viewport_y / image_height;

    // Calculate the location of the upper left pixel.
    //point3 viewport_upper_left = camera_center - (focal_length * cam_z) - viewport_x/2 - viewport_y/2;
    point3 viewport_upper_left = camera_center - (focus_dist*cam_z) - viewport_x/2.0f - viewport_y/2.0f;
    pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_x + pixel_delta_y);
     // Calculate the camera defocus disk basis vectors.
     float defocus_radius = focus_dist * std::tanf(degrees_to_radians(defocus_angle / 2.0f));
     def_disk_xr = cam_x * defocus_radius;
     def_disk_yr = cam_y * defocus_radius;
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
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, depth-1, world);
        }
        return color(0,0,0);
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

point3 camera::defocus_sampling() const
{
    vec3 p = random_in_unit_disk();
    return camera_center + (p[0] * def_disk_xr) + (p[1] * def_disk_yr);
}

// Construct a camera ray originating from the origin and directed at randomly sampled point around the pixel location h, w.
ray camera::get_ray(int h, int w) const
{
        // get ideal square sample
        vec3 offset = sample_square();
        vec3 px_sample = pixel00_loc 
                        + ((w + offset.x()) * pixel_delta_x)
                        + ((h + offset.y()) * pixel_delta_y);
        // vec3 ray_origin = camera_center;
        // if the def angle is less than or is 0, dont defocus, otherwise do. But test ie-8 too 
        vec3 ray_origin = (defocus_angle <= 0) ? camera_center : defocus_sampling();
        vec3 ray_direction = px_sample - ray_origin;
        return ray(ray_origin, ray_direction);
}
void camera::render(const hittable &world)
{
    initialize();
    image_height = (image_height < 1) ? 1 : image_height;
    viewport_width = viewport_height * (float(image_width) / image_height);
    std::clog << "MAX_DEPTH: " << max_depth << std::endl;
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
// void camera::render(const hittable &world)
// {
//     initialize();
//     image_height = (image_height < 1) ? 1 : image_height;
//     viewport_width = viewport_height * (float(image_width) / image_height);
//     std::clog << "MAX_DEPTH: " << max_depth << std::endl;
//     std::cout << "P3" << std::endl;
//     std::cout << image_width << " " << image_height << std::endl;
//     std::cout << "255" << std::endl;

//     // Create a buffer to store all pixel colors
//     std::vector<color> pixel_buffer(image_width * image_height);
    
//     // Get number of hardware threads
//     unsigned int num_threads = std::thread::hardware_concurrency();
//     std::vector<std::thread> threads(num_threads);
    
//     // Divide the work among threads
//     for (unsigned int t = 0; t < num_threads; t++) {
//         threads[t] = std::thread([&, t]() {
//             // Calculate range for this thread
//             int start_h = (image_height * t) / num_threads;
//             int end_h = (image_height * (t + 1)) / num_threads;
            
//             for (int h = start_h; h < end_h; h++) {
//                 for (int w = 0; w < image_width; w++) {
//                     color pixel_color(0,0,0);
//                     for (int sample = 0; sample < samples_per_px; sample++) {
//                         ray r = get_ray(h, w);
//                         pixel_color += ray_color(r, max_depth, world);
//                     }
//                     pixel_buffer[h * image_width + w] = px_sample_scale * pixel_color;
//                 }
//             }
//         });
//     }
    
//     // Wait for all threads to complete
//     for (auto& thread : threads) {
//         thread.join();
//     }
    
//     // Output all pixels in the correct order
//     for (int h = 0; h < image_height; h++) {
//         std::clog << "\rScanlines remaining: " << (image_height - h) << ' ' << std::flush;
//         for (int w = 0; w < image_width; w++) {
//             write_color(std::cout, pixel_buffer[h * image_width + w]);
//         }
//     }
    
//     std::clog << "\rDone.                 \n";
// }