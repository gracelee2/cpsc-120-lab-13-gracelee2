// Grace Lee
// CPSC 120-01
// 2021-10-28
// grace1@csu.fullerton.edu
// @gracelee2
//
// Lab 08-01
//
// This is the main function, makes a picture of spheres
//
/// \file

#include <Magick++.h>

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
//#include <limits>
#include <memory>
//#include <sstream>
#include <string>
#include <vector>

#include "ray.h"
#include "rng.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"

using namespace std;
using namespace Magick;

/// RayColor computes the color the ray \p r sees through the camera lens.
/// Given a Ray \p r, calculate the color that is visible to the ray.
/// \param r A ray eminating from the camera through the scene
/// \returns The color visible from that ray
Color RayColor(const Ray& r, const Sphere& world) {
  HitRecord rec;
  ColorRGB c;
  // check to see if the ray intersects with the world
  if (world.hit(r, 0, kInfinity, rec)) {
    // This is the base color of the sphere. You may set this color
    // to whatever you like.
    // TODO: set the color of the sphere to something you like.
    ColorRGB sphere_color(.5, .3, 1);
    // These are the values that are in the README for the coefficients for our shading equation.
    const double kAmbientReflection = 0.3;
    const double kDiffuseReflection = 0.7;
    const double kSpecularReflection = 0.5;
    const double kSpecularShininess = 32.0;
    // If the ray intersects an object in the world (the sphere), then
    // set the color to be the
    Vec3 light{1, -1, 0.25};

    // TODO: Calculate the following:
    // the vector to the light
    // the unit normal at the interection point rec.p
    // the unit vector from rec.p to the viewer
    // the reflection vector of the light around the surface normal
    // It's important that these are all unit vectors.
    Vec3 to_light_vector = UnitVector(light - r.at(root);
    Vec3 unit_normal = UnitVector((rec.at(root) - center_) / radius_;);
    Vec3 to_viewer = UnitVector(-rec.at(root));
    Vec3 reflection = Reflect(to_light_vector, unit_normal);

    // TODO: Calculate the ambient color
    ColorRGB phong_ambient = kAmbientReflection * sphere_color;
    // TODO: Calculate the dot product between l and n
    double l_dot_n = std::max(Dot(to_light_vector, unit_normal), 0.0);
    // TODO: Calcualte the diffuse reflection
    ColorRGB phong_diffuse = kDiffuseReflection * l_dot_n * sphere_color;

    double r_dot_v = std::max(Dot(reflection, to_viewer), 0.0);

    double r_dot_v_to_alpha = std::pow(r_dot_v, kSpecularShininess);

    // TODO: Calculate the specular reflection (the shiny spot)
    ColorRGB phong_specular =
        kSpecularReflection * r_dot_v_to_alpha * sphere_color;
    // Sum up the three types of relfection
    ColorRGB phong = phong_ambient + phong_diffuse + phong_specular;
    // Clamp the color to be between 0 and 1
    c = Clamp(phong);
  } else {
    // Figure out what color the sky is for Ray r.
    ColorRGB sky_top{1, 1, 1};
    ColorRGB sky_bottom{0.4980392156862745, 0.7450980392156863,
                        0.9215686274509803};
    Vec3 unit_direction = UnitVector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    c = (1.0 - t) * sky_bottom + t * sky_top;
  }
  return c;
}

/// Main function - Entry point for our ray tracer
/// The program takes one argument which is the output file name.
int main(int argc, char const* argv[]) {
  InitializeMagick(*argv);
  auto args = vector<string>(argv, argv + argc);
  if (args.size() < 2) {
    cout << "Please provide a path to a file.\n";
    exit(1);
  }
  string output_file_name;
  try {
    output_file_name = args.at(1);
  } catch (exception const& problem) {
    cout << "There was a problem getting the file name.\n";
    cout << problem.what() << "\n";
    exit(1);
  }
  /// Image definition in main
  /// The image is the output from the virtual camera. The image is what
  /// you will see when you open the output in an image viewer. The image's
  /// dimensions are specified in pixels and are therefore in integer units.
  /// The aspect ratio represents the ratio of width / height. The ratio
  /// 16:9 is the ratio used for wide format movies. Traditional 35mm film
  /// photographs have an image that is 36 mm x 24 mm which has an aspect
  /// ratio of 36:24 or 1.5.
  const double kAspectRatio = 16.0 / 9.0;
  // Set the image width to 512 pixels
  const int kImageWidth = 512;
  // Calculate the height of the image using the width and aspect ratio.
  // Remember to round the number to the closest integer.
  const int kImageHeight = int(lround(kImageWidth / kAspectRatio));
  // Create a new Image object using the file name provided on the
  // command line.
  ColorRGB yellow(1, 1, 0);
  // Create a yellow image the size that we'd like. Use yellow or some
  // obviously wrong color (a color not in our image)to help us debug
  // our output.
  Image image(Geometry(kImageWidth, kImageHeight), yellow);
  // Print out some information about the image to help us debug what's
  // going on.
  cout << "Your image has " << image.columns() << " columns (x direction) and "
       << image.rows() << " rows (y direction).\n";

  /// World definition in main
  auto world = Sphere(Point3(0, 0, -1), 0.5);

  /// Camera definition in main
  /// The [viewport](https://en.wikipedia.org/wiki/Viewport) is the
  /// rectangular viewing region visible to the camera. You can think of it
  /// as the dimensions of the camera's film or sensor. The coordinates
  /// are specfied in floating point units (doubles). Unlike an image which
  /// has its dimensions expressed as pixels, the camera's viewport dimensions
  /// can be expressed in whatever units you would like to use. Since we are
  /// creating a make believe image of make believe things, you can imagine
  /// the size of the objects to be as small (millimeters) or as large
  /// (kilometers) as you like.
  // The height of the viewport
  const double kViewportHeight = 2.0;
  // The width of the viewport is calculated using the height and the
  // previously defined aspect ratio.
  const double kViewportWidth = kAspectRatio * kViewportHeight;
  // The focal length is the distance between the projection plane (the end
  // of the lens) and the projection point (the inside of the camera).
  const double kFocalLength = 1.0;
  // The origin is as we expect. Everything in our world will be measured
  // from the center of the camera.
  const Point3 kOrigin{0, 0, 0};
  // Create a vector that represents the horizontal direction with respect
  // to the viewport.
  const Vec3 kHorizontal{kViewportWidth, 0, 0};
  // Create a vecotr that represents the vertical direction with respect
  // to the viewport
  const Vec3 kVertical{0, kViewportHeight, 0};
  // Calculate a vector that starts at the origin and points to the lower
  // left hand corner of the viewport. We will use this when we generate
  // all the rays that emanate out from the viewplane.
  const Vec3 kLowerLeftCorner =
      kOrigin - kHorizontal / 2 - kVertical / 2 - Vec3(0, 0, kFocalLength);

  /// Rendering the image in main
  /// Using nested loops, start from the top row of the viewplane and
  /// calculate the color for each pixel in each column of the image.
  /// The image (the output file) is the result of this calculation so
  /// keep in mind that each ray that is created maps onto a pixel in the
  /// image.
  // Save the starting time so the elapsed time can
  // be calculated.
  chrono::time_point<chrono::high_resolution_clock> start =
      chrono::high_resolution_clock::now();
  for (unsigned int column = 0; column < image.columns(); column++) {
    for (unsigned int row = 0; row < image.rows(); row++) {
      // This is a way to make sure you don't accidentally have the wrong
      // logic in your for loops. What an assertion does is it says this must
      // be true and if it isn't then the program is going to halt with an
      // error message. If your program halts, then you know you have something
      // wrong with your for loop counters.
      assert(row < image.rows());
      assert(column < image.columns());

      // It may help you to debug what you are doing by printing
      // each pixel out. Remember you can always resize the image to be
      // something smaller by changing kImageWidth and recompiling.
      // Remember column is the x direction and row is the y direction.
      // cout << "(c:" << column << ", r:" << row << ")\n";

      // The pixel starts off as black
      ColorRGB pixel_color(0, 0, 0);

      // u is the distance from the left edge of the image to the right
      // edge of the image measured as a percentage.
      // The column divided by the image.width() - 1 is the percentage of
      // the distance from the left side of the image to the right.
      // Consider column = 0 then colum / (image.width() - 1) -> 0.0
      //          column = (image.width() - 1) / 2 then
      //          colum / (image.width() - 1) -> 0.5
      //          column = image.width() - 1 then
      //          colum / (image.width() - 1) -> 1.0
      // The same is true for v
      double u = double(column) / double(image.columns() - 1);
      // Assign v as the ratio of the current row to the total number of rows.
      double v = double(row) / double(image.rows() - 1);

      // Create a ray that starts at the camera's center, the origin, and
      // travels through the pixel center defined by
      // kLowerLeftCorner + u * kHorizontal + v * kVertical - kOrigin
      Ray r{kOrigin,
            kLowerLeftCorner + u * kHorizontal + v * kVertical - kOrigin};

      // Calculate and return the color at the pixel that Ray r
      // points through.
      pixel_color = pixel_color + RayColor(r, world);
      // It may help you to debug what you are doing by printing
      // each pixel out.
      // cout << pixel_color << "\n";

      // Set the color for pixel(row, column) to the calculated color.
      image.pixelColor(column, row, pixel_color);
    }
  }
  // Save the ending time
  chrono::time_point<chrono::high_resolution_clock> end =
      chrono::high_resolution_clock::now();

  // Write the image to a file.
  image.write(output_file_name);

  // Calculate the elapsed time by taking the difference between end
  // and start.
  chrono::duration<double> elapsed_seconds = end - start;
  // Display the elapsed number of seconds.
  cout << "Time elapsed: " << elapsed_seconds.count() << " seconds.\n";

  return 0;
}
