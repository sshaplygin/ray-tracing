#include "rtweekend.h"

#include "sphere.h"
#include "hitable_list.h"
#include "ray.h"
#include "camera.h"
#include "color.h"

#include <iostream>

color ray_color(const ray &r, const hitable& world) {
    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        vec3 target = rec.p + rec.nornal + random_in_unit_sphere();
        return 0.5 * color( ray(rec.p, target-rec.p), world);
    }

    vec3 unit_direction = unit_vector(r.direction());

    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t)*color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;

    const int image_size = 100;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World

    hitable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera

    const auto focal_length = 1.0;
    const auto viewport_heigth = 2.0;
    const auto viewport_width = viewport_heigth * (static_cast<double>(image_width)/image_height);
    auto camera_center = point3();

    camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; j--) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            vec3 col(0,0,0);
            for (int s = 0; s < image_size; s++) {
                double u = double(i) / double(image_width);
                double v = double(j) / double(image_height);

                ray r = cam.get_ray(u, v);
                vec3 p = r.at(2.0);
                col += ray_color(r, world);
            }
            
            col /= double(image_size);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );

            auto pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\nDone!" << std::endl;
}