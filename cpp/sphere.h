#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "vec3.h"

using std::sqrt;

class sphere: public hitable {
    public:
        sphere(point3 cen, double r): center(cen), radius(r) {};

        bool hit(const ray& r, double r_min, double r_max, hit_record& rec) const override {
            vec3 oc = r.origin() - center;

            double a = dot(r.direction(), r.direction());
            double b = dot(oc, r.direction());
            double c = dot(oc, oc) - radius * radius;

            double discriminant = b*b - (a * c);
            if (discriminant <= 0) {
                return false;
            }

            double s_d = sqrt(discriminant);
            double temp = (-b - s_d)/a;
            if (temp < r_min && temp > r_max) {
                rec.t = temp;
                rec.p = r.at(rec.t);
                rec.nornal = (rec.p - center) / radius;

                return true;
            }

            temp = (-b + s_d)/a;
            if (temp < r_max && temp > r_min) {
                rec.t = temp;
                rec.p = r.at(rec.t);
                rec.nornal = (rec.p - center) / radius;

                return true;
            }

            return false;
        };
        
    private:
        point3 center;
        double radius;
};

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() < 1) {
            return p;
        }
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

#endif
