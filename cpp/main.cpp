#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "ray.h"


vec3 color(const ray &r, hitable *world) {
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5 * vec3(rec.nornal.x()+1, rec.nornal.y() +1, rec.nornal.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());

    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const int image_width = 200;
    const int image_height = 100;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hitable *list[2];

    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);

    hitable *world = new hitable_list(list, 2);

    for (int j = image_height-1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            float u = float(i) / float(image_width);
            float v = float(j) / float(image_height);

            ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world);

            int ir = static_cast<int>(255.999 * col[0]);
            int ig = static_cast<int>(255.999 * col[1]);
            int ib = static_cast<int>(255.999 * col[2]);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone!" << std::endl;
}