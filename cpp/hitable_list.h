#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hitable_list: public hitable {
    public:
        std::vector<shared_ptr<hitable>> objects;

        hitable_list() {}
        hitable_list(shared_ptr<hitable> obj) { add(obj); }
        
        void clear() { objects.clear(); }

        void add(shared_ptr<hitable> obj) {
            objects.push_back(obj);
        }

        bool hit(const ray& r , double t_min, double t_max, hit_record& rec) const override{
            hit_record temp_rec;
            bool hit_anything = false;

            auto closest_so_far = t_max;
            for (const auto& obj : objects) {
                if (!obj->hit(r, t_min, closest_so_far, temp_rec))) {
                    continue;
                }

                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }

            return hit_anything;
        };
};


#endif
