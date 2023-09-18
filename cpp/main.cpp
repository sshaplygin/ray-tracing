#include "rtweekend.h"

#include "hitable_list.h"
#include "color.h"
#include "camera.h"
#include "material.h"
#include "sphere.h"

int main() {
    hitable_list world;

    auto R = cos(pi/4);

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3( 0.0,  -100.5, -1.0), 100, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,  0.0,    -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,  0.0,    -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,  0.0,    -1.0),-0.4, material_left));
    world.add(make_shared<sphere>(point3( 1.0,  0.0,    -1.0), 0.5, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(-2, 2, 1);
    cam.lookat = point3(0,0,-1);
    cam.vup = vec3(0,1,0);

    cam.render(world);
}