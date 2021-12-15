// Grace Lee
// CPSC 120-01
// 2021-10-28
// grace1@csu.fullerton.edu
// @gracelee2
//
// Lab 08-01
//
// This program makes the rays
//
/// \file

#include "ray.h"

[[nodiscard]] Point3 Ray::origin() const { return origin_; }

[[nodiscard]] Vec3 Ray::direction() const { return direction_; }

[[nodiscard]] Point3 Ray::at(double t) const {
  return origin_ + t * direction_;
}

std::ostream& operator<<(std::ostream& out, const Ray& r) {
  out << "Ray(origin=(" << r.origin() << "), direction=(" << r.direction()
      << "))";
  return out;
}
