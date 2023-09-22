#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <chrono>
#include <iostream>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
};

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
};

inline double random_double(double min, double max) {
    return min + (max-min) * random_double();
}

void write_duration(std::ostream &out, std::chrono::steady_clock::time_point start_time, std::chrono::steady_clock::time_point end_time) {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    auto mm = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= mm;
    auto ss = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= ss;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    out << "Execution time: " <<
        std::to_string(mm.count()) + "m" +
        std::to_string(ss.count()) + "s" +
        std::to_string(ms.count()) + "ms" << '\n';
};

#include "interval.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"

#endif
