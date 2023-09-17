#include "rtweekend.h"

#include "hitable_list.h"
#include "camera.h"
#include "sphere.h"

int main() {
    hitable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 18.0 / 9.0;
    cam.image_width = 200;
    // cam.samples_per_pixel = 100;
    // cam.max_depth = 50;

    cam.render(world);
}