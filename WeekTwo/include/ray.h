#pragma once
#include "vec3.h"
class ray {
    private:
    point3 origin_;
    vec3 direction_;

    public:
      ray();
  
      ray(const point3& origin, const vec3& direction);
  
      const point3& origin() const;
      const vec3& direction() const;
  
      point3 at(float t) const;
  };

  