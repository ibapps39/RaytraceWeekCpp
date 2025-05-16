#include "camera.h"

void camera::initialize()
{

    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    sqrt_spp = int(std::sqrtf(samples_per_px));
    px_sample_scale = float(1.0f / (sqrt_spp * sqrt_spp));
    recip_sqrt_spp = float(1.0f / sqrt_spp);

    camera_center = lookfrom;

    cam_z = unit_vector(lookfrom - lookat);
    cam_x = unit_vector(cross(camera_up, cam_z));
    cam_y = cross(cam_z, cam_x); // already a unit vector since cam_z and cam_x are.

    // Determine viewport dimensions.
    camera_theta = (float)degrees_to_radians(vfov);
    camera_height = std::tanf(camera_theta / 2.0f);
    viewport_height = 2.0f * camera_height * focus_dist;
    viewport_width = viewport_height * (float(image_width) / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewport_x = viewport_width * cam_x;
    viewport_y = viewport_height * -cam_y;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_x = viewport_x / image_width;
    pixel_delta_y = viewport_y / image_height;

    // Calculate the location of the upper left pixel.
    point3 viewport_upper_left = camera_center - (focus_dist * cam_z) - viewport_x / 2.0f - viewport_y / 2.0f;
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
        return color(0, 0, 0);
    }

    hit_record rec;
    // If the ray hits nothing, return the background color.
    if (!world.hit(r, interval(0.001, infinity), rec))
    {
        return background;
    }

    ray scattered;
    color attenuation;
    // Remember Q + u + v, p = Q
    color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat->scatter(r, rec, attenuation, scattered))
    {
        return color_from_emission;
    }

    color color_from_scatter = attenuation * ray_color(scattered, depth - 1, world);
    return color_from_emission + color_from_scatter;
}
// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
vec3 camera::sample_square() const
{
    return vec3(rand_f() - 0.5f, rand_f() - 0.5f, 0);
}

point3 camera::defocus_sampling() const
{
    vec3 p = random_in_unit_disk();
    return camera_center + (p[0] * def_disk_xr) + (p[1] * def_disk_yr);
}

vec3 camera::sample_square_stratified(int s_i, int s_j) const
{
    // Returns the vector to a random point in the square sub-pixel specified by grid
    // indices s_i and s_j, for an idealized unit square pixel [-.5,-.5] to [+.5,+.5].

    auto px = float((s_i + rand_f()) * recip_sqrt_spp) - 0.5f;
    auto py = float((s_j + rand_f()) * recip_sqrt_spp) - 0.5f;

    return vec3(px, py, 0);
}

// Construct a camera ray originating from the origin and directed at randomly sampled point around the pixel location h, w.
ray camera::get_ray(int i, int j, int s_i, int s_j) const
{
    // get ideal square sample
    vec3 offset = sample_square_stratified(s_i, s_j);
    vec3 px_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_x) + ((j + offset.y()) * pixel_delta_y);
    // vec3 ray_origin = camera_center;
    vec3 ray_origin = (defocus_angle <= 0) ? camera_center : defocus_sampling();
    vec3 ray_direction = px_sample - ray_origin;
    float ray_time = rand_f();
    return ray(ray_origin, ray_direction, ray_time);
}
void camera::render(const hittable &world)
{
    initialize();

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            color pixel_color(0, 0, 0);
            for (int s_j = 0; s_j < sqrt_spp; s_j++)
            {
                for (int s_i = 0; s_i < sqrt_spp; s_i++)
                {
                    ray r = get_ray(i, j, s_i, s_j);
                    pixel_color += ray_color(r, max_depth, world);
                }
            }
            write_color(std::cout, px_sample_scale * pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}