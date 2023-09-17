#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "vec3.h"

using std::sqrt;

class sphere: public hitable {
    public:
        sphere(point3 cen, double r): center(cen), radius(r) {};
        sphere(point3 cen, double r, shared_ptr<material> _material) 
            : center(cen), radius(r), mat(_material) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = r.origin() - center;

            double a = dot(r.direction(), r.direction());
            double half_b = dot(oc, r.direction());
            double c = oc.length_squared() - radius * radius;

            auto discriminant = half_b * half_b - a * c;
            if (discriminant <= 0) {
                return false;
            }

            auto sqrtd = sqrt(discriminant);
            auto root = (-half_b - sqrtd)/a;
            if (!ray_t.surrounds(root)) {
                root = (-half_b + sqrtd) / a;
                if (!ray_t.surrounds(root)) {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        };
        
    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;
};

#endif
