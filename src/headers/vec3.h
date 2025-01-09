#ifndef MY_VEC3_H
#define MY_VEC3_H 1

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vec3 vec3;
struct vec3 {
	double x;
	double y;
	double z;
};

typedef vec3 point3;

void print_vec3(vec3* u);

// Small and frequently used functions are statically inlined.

/**
 * dot - computes the dot product of two vectors `u` and `v`. The dot product
 * of u=<x0, y0, z0> and v=<x1, y1, z1> is
 * dot(u, v) = (x0*x1) + (y0*y1) + (z0*z1).
 * The result is a scalar value. If either vectors is NULL, NAN is returned.
 * @u: pointer to the first vector (input).
 * @v: pointer to the second vector (input).
 * @Returns: scalar value or NAN.
 */
static
inline
double dot(vec3 const* u, vec3 const* v){
	return (u && v) ? (u->x * v->x) + (u->y * v->y) + (u->z * v->z): NAN;
}

/**
 * scalar_mul - computes the multiplication of a vector `u` with a scalar `t`.
 * The vector `u` is modified inplace.
 * @u: pointer to the vector (input).
 * @t: scalar multiplier of the vector (input).
 * @Returns: modified vector `u`
 */
inline
vec3* scalar_mul(vec3* u, double t) {
	if (u) {
		u->x *= t;
		u->y *= t;
		u->z *= t;
	}
	return u;
}

/**
 * scalar_div - computes the division of a vector `u` with a scalar `t`.
 * The vector `u` is modified inplace.
 * @u: pointer to the vector (input).
 * @t: scalar divider of the vector (input).
 * @Returns: modified vector `u`
 */
inline
vec3* scalar_div(vec3* u, double t) {
	if (u) {
		u->x /= t;
		u->y /= t;
		u->z /= t;
	}
	return u;
}

/**
 * len_squared - computes the square of the magnitude of a vector u. If vector `u`
 * is a null pointer, NAN is returned.
 * @u: pointer to the vector (input).
 * @Returns: |u|^2. Otherwise, `NAN`.
 * */
static
inline
double len_squared(vec3 const* u) {
	return u ? (u->x * u->x) + (u->y * u->y) + (u->z * u->z) : NAN;
}

/**
 * len - computes the magnitude of a vector u. If vector `u` is a null pointer,
 * NAN is returned.
 * @u: ponter to the vector (input).
 * @Returns: |u| or `NAN`.
 */
static
inline
double len(vec3 const* u) {
	return u ? sqrt(len_squared(u)): NAN;
}

/**
 * unit_vec3 - normalises the vector `u`. This operation involves dividing
 * the vector with its length.
 * @u: pointer to the vector.
 * @Returns: a normalised vector.
 */
vec3* unit_vec3(vec3* u); 

/**
 * sub - computes the difference between two vectors `u` and `v`. The result
 * is stored in the output vector `out`.
 * @u: pointer to the first vector (input).
 * @v: pointer to the second vector (input).
 * @out: ponter to a stack allocated vector (output).
 * @Returns: `out`.
 */
vec3* sub(vec3 const* u, vec3 const* v, vec3* out);

/**
 * add - computes the sum of two vectors `u` and `v`. The result
 * is stored in the output vector `out`.
 * @u: pointer to the first vector (input).
 * @v: pointer to the second vector (input).
 * @out: ponter to a stack allocated vector (output).
 * @Returns: `out`.
 */
vec3* add(vec3 const* u, vec3 const* v, vec3* out);

/**
 * cross - computes the cross product of two vectors `u` and `v`. The result
 * is stored in the output vector `out`.
 * The cross product of u = <a1, a2, a3> and v = <b1, b2, b3> is
 * `u` x `v` = (a2*b3 - a3*b2)i + (a3*b1 - a1*b3)j + (a1*b2 - a2*b1)k
 * Note: `out` is a pointer to a stack allocated object.
 * @u: pointer to the first vector (input).
 * @v: pointer to the second vector (input).
 * @out: pointer to a stack allocated vector (output).
 * @Returns: `out`.
 */
vec3* cross(vec3* u, vec3* v, vec3* out);



#ifdef __cplusplus
}
#endif

#endif
