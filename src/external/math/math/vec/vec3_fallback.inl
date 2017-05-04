#ifndef VEC3_FALLBACK_INCLUDED_78A1B493_AA3B_4D09_89FC_D86CBBDEE3F0
#define VEC3_FALLBACK_INCLUDED_78A1B493_AA3B_4D09_89FC_D86CBBDEE3F0


#include "../detail/detail.hpp"
#include "vec_types.hpp"
#include "../general/general.hpp"
#include <assert.h>


#ifdef MATH_ON_FPU


/*
  Vector3
  3D vector fallback impl
*/


_MATH_NS_OPEN


// ** Implimentation ** //


// Constants
vec3
vec3_zero()
{
  return vec3_init(0.f);
}


vec3
vec3_one()
{
  return vec3_init(1.f);
}


vec3
vec3_zero_zero_one()
{
  return vec3_init(0.f, 0.f, 1.f);
}

// Initialize

vec3
vec3_init(const float val)
{
  return vec3_init(val, val, val);
}


vec3
vec3_init(const float x, const float y, const float z)
{
  vec3 return_vec;

  return_vec.data[0] = x;
  return_vec.data[1] = y;
  return_vec.data[2] = z;

  return return_vec;
}


vec3
vec3_init_with_array(const float *arr)
{
  return vec3_init(arr[0], arr[1], arr[2]);
}


// Get components.

float
vec3_get_x(const vec3 vec)
{
  return vec.data[0];
}


float
vec3_get_y(const vec3 vec)
{
  return vec.data[1];
}


float
vec3_get_z(const vec3 vec)
{
  return vec.data[2];
}


void
vec3_to_array(const vec3 a, float *out_array)
{
  out_array[0] = vec3_get_x(a);
  out_array[1] = vec3_get_y(a);
  out_array[2] = vec3_get_z(a);
}


vec3
vec3_add(const vec3 a, const vec3 b)
{
  return vec3_init(get_x(a) + get_x(b), get_y(a) + get_y(b), get_z(a) + get_z(b));
}


vec3
vec3_subtract(const vec3 a, const vec3 b)
{
  return vec3_init(get_x(a) - get_x(b), get_y(a) - get_y(b), get_z(a) - get_z(b));
}


vec3
vec3_multiply(const vec3 a, const vec3 b)
{
  return vec3_init(get_x(a) * get_x(b), get_y(a) * get_y(b), get_z(a) * get_z(b));
}


vec3
vec3_divide(const vec3 a, const vec3 b)
{
  // Divide by zero check.
  assert(get_x(b) != 0 && get_y(b) != 0 && get_z(b) != 0);

  return vec3_init(get_x(a) / get_x(b), get_y(a) / get_y(b), get_z(a) / get_z(b));
}


vec3
vec3_lerp(const vec3 start, const vec3 end, const float dt)
{
  const vec3 difference = vec3_subtract(end, start);
  const vec3 scaled     = vec3_scale(difference, dt);
  const vec3 position   = vec3_add(start, scaled);

  return position;
}


// vec3
// vec3_slerp(const vec3 start, const vec3 end, const float dt)
// {
//   const float dot                   = vec3_dot(start, end);
//   const float clamp                 = caffmath::clamp(dot, -1.f, 1.f);
//   const float theta                 = caffmath::a_cos(clamp) * dt;

//   const vec3 start_scale         = vec3_scale(start, dot);
//   const vec3 relative            = vec3_subtract(end, start_scale);
//   const vec3 normal              = vec3_normalize(relative);

//   const float cos_theta             = caffmath::cos(theta);
//   const float sin_theta             = caffmath::sin(theta);

//   const vec3 start_cos_scale     = vec3_scale(start, cos_theta);
//   const vec3 relative_sin_scale  = vec3_scale(normal, sin_theta);

//   return vec3_add(start_cos_scale, relative_sin_scale);
// }


vec3
vec3_scale(const vec3 a, const float scale)
{
  const vec3 scale_vec = vec3_init(scale);
  return vec3_multiply(a, scale_vec);
}


vec3
vec3_normalize(const vec3 a)
{
  const float length = vec3_length(a);

  assert(length != 0); // Don't pass zero vectors. (0,0,0);

  return vec3_scale(a, (1.f / length));
}


float
vec3_length(const vec3 a)
{
  const float x = get_x(a) * get_x(a) + get_y(a) * get_y(a) + get_z(a) * get_z(a);

  return sqrt(x);
}


vec3
vec3_cross(const vec3 a, const vec3 b)
{
  const float x = (vec3_get_y(a) * vec3_get_z(b)) - (vec3_get_z(a) * vec3_get_y(b));
  const float y = (vec3_get_x(a) * vec3_get_z(b)) - (vec3_get_z(a) * vec3_get_x(b));
  const float z = (vec3_get_x(a) * vec3_get_y(b)) - (vec3_get_y(a) * vec3_get_x(b));

  return vec3_init(x, -y, z);
}


float
vec3_dot(const vec3 a, const vec3 b)
{
  return (vec3_get_x(a) * vec3_get_x(b)) +
         (vec3_get_y(a) * vec3_get_y(b)) +
         (vec3_get_z(a) * vec3_get_z(b));
}


bool
vec3_is_equal(const vec3 a, const vec3 b)
{
	return
  (
    (vec3_get_x(a) == vec3_get_x(b))
    &&
    (vec3_get_y(a) == vec3_get_y(b))
    &&
    (vec3_get_z(a) == vec3_get_z(b))
  );
}


bool
vec3_is_not_equal(const vec3 a, const vec3 b)
{
	return !vec3_is_equal(a, b);
}


bool
vec3_is_near(const vec3 a, const vec3 b, const float error)
{
  return(
    is_near(vec3_get_x(a), vec3_get_x(b), error)
    &&
    is_near(vec3_get_y(a), vec3_get_y(b), error)
    &&
    is_near(vec3_get_z(a), vec3_get_z(b), error)
  );
}


bool
vec3_is_not_near(const vec3 a, const vec3 b, const float error)
{
	return !vec3_is_near(a, b, error);
}


_MATH_NS_CLOSE


#endif // on fpu
#endif // inc guard
