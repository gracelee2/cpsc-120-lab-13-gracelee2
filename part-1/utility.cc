
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include "utility.h"

#include <algorithm>
// #include <limits>

const double kInfinity = std::numeric_limits<double>::infinity();
const double kPi = 3.14159265358979323846;

double Square(double x) { return x * x; }

double DegreesToRadians(double degrees) { return degrees * kPi / 180.0; }

std::ostream& operator<<(std::ostream& out, Magick::ColorRGB color) {
  out << "(" << color.red() << ", " << color.green() << ", " << color.blue()
      << ")";
  return out;
}

Magick::ColorRGB operator*(double t, Magick::ColorRGB color) {
  return Magick::ColorRGB(std::clamp((t * color.red()), 0.0, 1.0),
                          std::clamp((t * color.green()), 0.0, 1.0),
                          std::clamp((t * color.blue()), 0.0, 1.0));
}

Magick::ColorRGB operator*(Magick::ColorRGB color, double t) {
  return (t * color);
}

Magick::ColorRGB operator+(Magick::ColorRGB lhs, Magick::ColorRGB rhs) {
  return Magick::ColorRGB(std::clamp((lhs.red() + rhs.red()), 0.0, 1.0),
                          std::clamp((lhs.green() + rhs.green()), 0.0, 1.0),
                          std::clamp((lhs.blue() + rhs.blue()), 0.0, 1.0));
}

Magick::ColorRGB operator-(Magick::ColorRGB lhs, Magick::ColorRGB rhs) {
  return Magick::ColorRGB(std::clamp((lhs.red() - rhs.red()), 0.0, 1.0),
                          std::clamp((lhs.green() - rhs.green()), 0.0, 1.0),
                          std::clamp((lhs.blue() - rhs.blue()), 0.0, 1.0));
}

Magick::ColorRGB Clamp(Magick::ColorRGB c) {
  return Magick::ColorRGB(std::clamp(c.red(), 0.0, 1.0),
                          std::clamp(c.green(), 0.0, 1.0),
                          std::clamp(c.blue(), 0.0, 1.0));
}
