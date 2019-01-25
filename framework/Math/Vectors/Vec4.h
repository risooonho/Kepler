
#ifndef Vec4_h
#define Vec4_h

#include "Vec2.h"
#include "Vec3.h"
#include <iostream>

namespace Kepler {

class Vec4 {
public:
  union {
    // General Notation
    struct {
      const float x, y, z, w;
    };
    // RGBA Color Notation
    struct {
      const float r, g, b, a;
    };
    // HSVA Color Notation
    struct {
      const float h, s, v;
    };
  };

public:
  Vec4() : x(0), y(0), z(0), w(0) {}
  Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};
  Vec4(const Vec2 &vec2, float z, float w) : x(vec2.x), y(vec2.y), z(z), w(w){};
  Vec4(const Vec2 &vec2, const Vec2 &vec22)
      : x(vec2.x), y(vec2.y), z(vec22.x), w(vec22.y){};
  Vec4(const Vec3 &vec3, float w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}
  Vec4 operator+(const Vec4 &other) const;
  Vec4 operator-(const Vec4 &other) const;
  Vec4 operator*(const Vec4 &other) const;
  Vec4 operator*(const float &other) const;
  Vec4 operator/(const Vec4 &other) const;
  Vec4 operator/(const float &other) const;
  friend std::ostream &operator<<(std::ostream &out, const Vec4 &other);
  float Dot(const Vec4 &other) const;
  float DistanceTo(const Vec4 &other) const;
  float Magnitude() const;
  Vec4 Normalize() const;
};

} // namespace Kepler

#endif
