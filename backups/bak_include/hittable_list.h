#pragma once

//#include <memory>
#include <vector>
#include "hittable.h"
#include "rt_common.h"
class hittable_list : public hittable
{
    public:
        std::vector<std::shared_ptr<hittable>> objects;
        hittable_list();
        hittable_list(std::shared_ptr<hittable> object);
        void clear();
        void add(std::shared_ptr<hittable> object);

        //bool hit(const ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const override;
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};