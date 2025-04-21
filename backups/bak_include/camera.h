#pragma once
#include "hittable.h"

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

class camera
{
private:
    // Calculate the image height, and ensure that it's at least 1.
    int image_height;
    // Viewport widths less than one are ok since they are real valued.
    float viewport_height;
    float viewport_width;
    vec3 viewport_x;
    vec3 viewport_y;
    vec3 viewport_upper_left;
    //
    float focal_length;
    point3 camera_center;
    vec3 pixel_delta_x;
    vec3 pixel_delta_y;
    point3 pixel00_loc;

    float px_sample_scale; // Color scale factor for a sum of pixel samples

    void initialize();
    color ray_color(const ray &r, int depth, const hittable &world) const;
    vec3 sample_square() const;
    ray get_ray( int h, int w) const;

public:
    float aspect_ratio;
    int image_width;
    int samples_per_px;
    int max_depth;
    void render(const hittable &world);
};