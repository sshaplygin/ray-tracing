#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

struct hit_record {
    public:
        double t;
        point3 p;
        vec3 normal;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hitable {
    public: 
        virtual ~hitable() = default;

        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
