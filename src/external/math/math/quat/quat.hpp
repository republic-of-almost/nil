#ifndef QUATERNION_INCLUDED_ED2C1105_82A1_477F_B62C_5093DE20C971
#define QUATERNION_INCLUDED_ED2C1105_82A1_477F_B62C_5093DE20C971


/*
  Quaternion
  Used for rotation math.
*/


#include "../detail/detail.hpp"
#include "quat_types.hpp"
#include "../general/general.hpp"
#include "../mat/mat4.hpp"
#include "../mat/mat3.hpp"
#include "../vec/vec3.hpp"


_MATH_NS_OPEN


// Interface

inline quat             quat_init();
inline quat             quat_init(const float x, const float y, const float z, const float w);
inline quat             quat_init_with_axis_angle(const float x, const float y, const float z, const float theta_radians);
inline quat             quat_init_with_axis_angle(const vec3 axis, const float theta_radians);
inline quat             quat_init_with_euler_angles(const float pitch_radians, const float yaw_radians, const float roll_radians);
inline quat             quat_init_with_mat3(const mat3 &mat);

inline quat             quat_conjugate(const quat to_conj);
inline quat             quat_multiply(const quat left, const quat right);
inline quat             quat_multiply(const quat a, const quat b, const quat c);
inline quat             quat_normalize(const quat to_normalize);
inline float            quat_length(const quat to_length);
inline vec3             quat_rotate_point(const quat rotation, const vec3 point);

inline mat3             quat_get_rotation_matrix(const quat to_mat3);
inline vec3             quat_get_axis();
inline vec3             quat_get_euler_angles_in_radians();
inline void             quat_to_array(const quat to_array, float out[4]);

inline float            quat_get_x(const quat quat);
inline float            quat_get_y(const quat quat);
inline float            quat_get_z(const quat quat);
inline float            quat_get_w(const quat quat);
inline float            quat_get(const quat quat, const uint32_t i);


// Shorthand getters
inline float            get_x(const quat quat) { return quat_get_x(quat); }
inline float            get_y(const quat quat) { return quat_get_y(quat); }
inline float            get_z(const quat quat) { return quat_get_z(quat); }
inline float            get_w(const quat quat) { return quat_get_w(quat); }


// Impl

namespace detail
{
  struct internal_quat
  {
    float x, y, z, w;
  };
}


quat
quat_init()
{
  return quat_init(0,0,0,1);
}


quat
quat_init(const float x, const float y, const float z, const float w)
{
  quat return_quat;
  detail::internal_quat *internal_quat = reinterpret_cast<detail::internal_quat*>(&return_quat);

  internal_quat->x = x;
  internal_quat->y = y;
  internal_quat->z = z;
  internal_quat->w = w;

  return return_quat;
}


quat
quat_init_with_axis_angle(const float x, const float y, const float z, const float theta_radians)
{
  const float half_angle = 0.5f * theta_radians;
  const float sin_angle  = MATH_NS_NAME::sin(half_angle);

  const float qx = sin_angle * x;
  const float qy = sin_angle * y;
  const float qz = sin_angle * z;
  const float qw = MATH_NS_NAME::cos(half_angle);

  return quat_init(qx, qy, qz, qw);
}


void
quat_to_array(const quat to_array, float out[4])
{
  const detail::internal_quat *array = reinterpret_cast<const detail::internal_quat*>(&to_array);
  
  memcpy(out, array, sizeof(float) * 4);
}


quat
quat_init_with_axis_angle(const vec3 axis, const float theta_radians)
{
  return quat_init_with_axis_angle(vec3_get_x(axis), vec3_get_y(axis), vec3_get_z(axis), theta_radians);
}


quat
quat_init_with_euler_angles(const float pitch_radians, const float yaw_radians, const float roll_radians)
{
  const float half_roll  = roll_radians * 0.5f;
  const float half_yaw   = yaw_radians * 0.5f;
  const float half_pitch = pitch_radians * 0.5f;

  const float cz = MATH_NS_NAME::cos(half_roll);
  const float sz = MATH_NS_NAME::sin(half_roll);
  const float cy = MATH_NS_NAME::cos(half_yaw);
  const float sy = MATH_NS_NAME::sin(half_yaw);
  const float cx = MATH_NS_NAME::cos(half_pitch);
  const float sx = MATH_NS_NAME::sin(half_pitch);

  const float w = cz * cy * cx + sz * sy * sz;
  const float x = cz * cy * sx - sz * sy * cz;
  const float y = cz * sy * cx + sz * cy * sz;
  const float z = sz * cy * cx - cz * sy * sz;

  return quat_init(x, y, z, w);
}


quat
quat_init_with_mat3(const mat3 &mat)
{
  const float w = MATH_NS_NAME::sqrt(MATH_NS_NAME::max( 0.f, 1 + mat3_get(mat, 0,0) + mat3_get(mat, 1,1) + mat3_get(mat, 2,2) )) * 0.5f;
  const float x = MATH_NS_NAME::sqrt(MATH_NS_NAME::max( 0.f, 1 + mat3_get(mat, 0,0) - mat3_get(mat, 1,1) - mat3_get(mat, 2,2) )) * 0.5f;
  const float y = MATH_NS_NAME::sqrt(MATH_NS_NAME::max( 0.f, 1 - mat3_get(mat, 0,0) + mat3_get(mat, 1,1) - mat3_get(mat, 2,2) )) * 0.5f;
  const float z = MATH_NS_NAME::sqrt(MATH_NS_NAME::max( 0.f, 1 - mat3_get(mat, 0,0) - mat3_get(mat, 1,1) + mat3_get(mat, 2,2) )) * 0.5f;
  
  const float q_x = x * MATH_NS_NAME::sign(mat3_get(mat,2,1) - mat3_get(mat,1,2));
  const float q_y = y * MATH_NS_NAME::sign(mat3_get(mat,0,2) - mat3_get(mat,2,0));
  const float q_z = z * MATH_NS_NAME::sign(mat3_get(mat,1,0) - mat3_get(mat,0,1));
  
  return quat_init(q_x, q_y, q_z, w);
}


quat
quat_conjugate(const quat to_conj)
{
  const detail::internal_quat *conj_quat = reinterpret_cast<const detail::internal_quat*>(&to_conj);
  return quat_init(-conj_quat->x, -conj_quat->y, -conj_quat->z, conj_quat->w);
}


quat
quat_multiply(const quat left, const quat right)
{
  const detail::internal_quat *left_quat  = reinterpret_cast<const detail::internal_quat*>(&left);
  const detail::internal_quat *right_quat = reinterpret_cast<const detail::internal_quat*>(&right);

  const float w = (left_quat->w * right_quat->w) - (left_quat->x * right_quat->x) - (left_quat->y * right_quat->y) - (left_quat->z * right_quat->z);
  const float x = (left_quat->w * right_quat->x) + (left_quat->x * right_quat->w) + (left_quat->y * right_quat->z) - (left_quat->z * right_quat->y);
  const float y = (left_quat->w * right_quat->y) + (left_quat->y * right_quat->w) + (left_quat->z * right_quat->x) - (left_quat->x * right_quat->z);
  const float z = (left_quat->w * right_quat->z) + (left_quat->z * right_quat->w) + (left_quat->x * right_quat->y) - (left_quat->y * right_quat->x);

  return quat_init(x, y, z, w);
}


quat
quat_multiply(const quat a, const quat b, const quat c)
{
  return quat_multiply(a, quat_multiply(b, c));
}


quat
quat_normalize(const quat to_normalize)
{
  const detail::internal_quat *internal_quat = reinterpret_cast<const detail::internal_quat*>(&to_normalize);

  const float length = quat_length(to_normalize);
  assert(length); // Can't have zero length.

  const float w = internal_quat->w / length;
  const float x = internal_quat->x / length;
  const float y = internal_quat->y / length;
  const float z = internal_quat->z / length;

  return quat_init(x,y,z,w);
}


float
quat_length(const quat to_length)
{
  const detail::internal_quat *length_quat = reinterpret_cast<const detail::internal_quat*>(&to_length);
  return MATH_NS_NAME::sqrt((length_quat->w * length_quat->w) + (length_quat->x * length_quat->x) + (length_quat->y * length_quat->y) + (length_quat->z * length_quat->z));
}


vec3
quat_rotate_point(const quat rotation, const vec3 point)
{
  const auto rot_mat = quat_get_rotation_matrix(rotation);

  return mat3_multiply(point, rot_mat);
}


mat3
quat_get_rotation_matrix(const quat to_mat3)
{
  const float quat_x = quat_get_x(to_mat3);
  const float quat_y = quat_get_y(to_mat3);
  const float quat_z = quat_get_z(to_mat3);
  const float quat_w = quat_get_w(to_mat3);

  const float x_sq = quat_x * quat_x;
  const float y_sq = quat_y * quat_y;
  const float z_sq = quat_z * quat_z;
  
  float mat_data[9]
	{
		1 - 2 * y_sq - 2 * z_sq,
    2 * (quat_x * quat_y) - 2 * (quat_z * quat_w),
		2 * (quat_x * quat_z) + 2 * (quat_y * quat_w),
        
		2 * (quat_x * quat_y) + 2 * (quat_z * quat_w),
		1 - 2 * x_sq - 2 * z_sq,
		2 * (quat_y * quat_z) - 2 * (quat_x * quat_w),
        
		2 * (quat_x * quat_z) - 2 * (quat_y * quat_w),
		2 * (quat_y * quat_z) + 2 * (quat_x * quat_w),
		1 - 2 * x_sq - 2 * y_sq,
	};

  return mat3_init_with_array(mat_data);
}


// vec3
// quat_get_axis()
// {

// }


// vec3
// quat_get_euler_angles_in_radians()
// {

// }


float
quat_get_x(const quat quat)
{
  const detail::internal_quat *internal_quat = reinterpret_cast<const detail::internal_quat*>(&quat);
  return internal_quat->x;
}


float
quat_get_y(const quat quat)
{
  const detail::internal_quat *internal_quat = reinterpret_cast<const detail::internal_quat*>(&quat);
  return internal_quat->y;
}


float
quat_get_z(const quat quat)
{
  const detail::internal_quat *internal_quat = reinterpret_cast<const detail::internal_quat*>(&quat);
  return internal_quat->z;
}


float
quat_get_w(const quat quat)
{
  const detail::internal_quat *internal_quat = reinterpret_cast<const detail::internal_quat*>(&quat);
  return internal_quat->w;
}


float
quat_get(const quat quat, const uint32_t i)
{
  assert(i < 4);

  if(i < 4)
  {
    return quat.data[i];
  }
  
  return 0.f;
}


_MATH_NS_CLOSE


#endif // include guard
