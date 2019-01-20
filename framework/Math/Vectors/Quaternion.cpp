#include "Quaternion.h"
#include <math.h>

namespace Kepler {

/*
Takes a unit vector and an angle and produces a Quaternion in number notation.
The Angle is halved due to the fact that in any rotation the point will be
multiplied twice so that the angel given will result in the angle of rotation.
*/
Quaternion::Quaternion(Vec3 &axis, float angle)
    : x(axis.x * sin(angle / 2)), // X
      y(axis.y * sin(angle / 2)), // Y
      z(axis.z * sin(angle / 2)), // Z
      w(cos(angle / 2))           // W
{}

static Quaternion FromAxis( Vec3& axis, float angle){
  Vec3 normAxis = axis.Normalize();
  return Quaternion(normAxis, angle);
}

static Quaternion FromEuler(float yaw, float pitch, float roll) {
  yaw /= 2;
  pitch /= 2;
  roll /= 2;
  return Quaternion(
      (cos(yaw) * cos(pitch) * cos(roll)) - (sin(yaw) * sin(pitch) * sin(roll)),
      (sin(yaw) * sin(pitch) * cos(roll)) + (cos(yaw) * cos(pitch) * sin(roll)),
      (sin(yaw) * cos(pitch) * cos(roll)) + (cos(yaw) * sin(pitch) * sin(roll)),
      (cos(yaw) * sin(pitch) * cos(roll)) - (sin(yaw) * cos(pitch) * sin(roll))
    );
}

// Creates a new inverse Quaternion based on an existing one.
Quaternion Quaternion::Invert(const Quaternion &quat) {
  return Quaternion(-quat.x, -quat.y, -quat.z, quat.w);
}

// Quaternion multiplication
Quaternion &Quaternion::operator*(const Quaternion &other) const {
  return *new Quaternion(
      (x * other.x) - (y * other.y) - (z * other.z) - (w * other.w),
      (x * other.y) + (y * other.x) + (z * other.w) - (w * other.z),
      (x * other.z) + (y * other.w) - (z * other.x) + (w * other.y),
      (x * other.w) - (y * other.z) + (z * other.y) + (w * other.x));
}

// Equivalency
bool Quaternion::operator==(const Quaternion &other) const {
  return ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w));
}

bool Quaternion::operator!=(const Quaternion &other) const {
  return !(*this == other);
}

} // namespace Kepler
