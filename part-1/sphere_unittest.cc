
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include "sphere.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <sstream>
#include <string>

namespace {

class SphereTest : public testing::Test {
 protected:
  void SetUp() override {
    s1_ = Sphere(Point3(1.1, 2.2, 3.3), 1.23);
    s2_ = Sphere(Point3(3.1, 4.2, 5.3), 3.45);
  }

  // void TearDown() override { }

  Sphere s1_;
  Sphere s2_;
};

TEST_F(SphereTest, GetOrigin) {
  EXPECT_TRUE(Point3(1.1, 2.2, 3.3) == s1_.center());
  EXPECT_TRUE(Point3(3.1, 4.2, 5.3) == s2_.center());
}

TEST_F(SphereTest, GetRadius) {
  EXPECT_DOUBLE_EQ(1.23, s1_.radius());
  EXPECT_DOUBLE_EQ(3.45, s2_.radius());
}

TEST_F(SphereTest, StreamInsertionOperator) {
  std::ostringstream message_buffer;
  message_buffer << s1_;
  EXPECT_TRUE(message_buffer.str() ==
              "Sphere(center=(1.1, 2.2, 3.3), radius=1.23)");
  message_buffer = std::ostringstream();
  message_buffer << s2_;
  EXPECT_TRUE(message_buffer.str() ==
              "Sphere(center=(3.1, 4.2, 5.3), radius=3.45)");
}

}  // namespace
