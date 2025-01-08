#ifndef MY_VEC3_H
#define MY_VEC3_H 1

#include <math.h>

typedef struct vec3 vec3;
struct vec3 {
	double x;
	double y;
	double z;
};

typedef vec3 point3;

void print_vec3(vec3* u);

/**
 * cross - computes the cross product of vectors `u` and `v` and stores
 * the result in vector `out`. The cross product of u = <a1, a2, a3> and
 * v = <b1, b2, b3> is (a2*b3 - a3*b2)i + (a3*b1 - a1*b3)j + (a1*b2 - a2*b1)k
 * @u: pointer to a vector object.
 * @v: pointer to a vector object.
 * @out: pointer to a vector object.
 */
inline 
vec3* cross(vec3* u, vec3* v, vec3* out) {
	if (u && v && out) {
		out->x = (u->y * v->z) - (u->z * v->y);
		out->y = (u->z * v->x) - (u->x * v->z);
		out->z = (u->x * v->y) - (u->y * v->x);
	}
	return out;
}

/**
 * dot - compute the dot product of two vectors: u=<x0, y0, z0>
 * and v=<x1, y1, z1> where dot(u, v) = (x0*x1) + (y0*y1) + (z0*z1).
 * The result is a scalar value. If either vectors is NULL, inf is returned.
 * @u: pointer to a vec3 object.
 * @v: pointer to a vec3 object.
 * @Returns: scalar value or inf.
 */
inline
double dot(vec3* u, vec3* v){
	double ret = 1.0 / 0.0;
	if (u && v) {
		ret = (u->x * v->x) + (u->y * v->y) + (u->z * v->z);
	}
	return ret;
}

inline
vec3* sub(vec3* u, vec3* v, vec3* out) {
	if (u && v && out) {
		out->x = u->x - v->x;
		out->y = u->y - v->y;
		out->z = u->z - v->z;
	}
	return out;
}

inline
vec3* add(vec3* u, vec3* v, vec3* out) {
	if (u && v && out) {
		out->x = u->x + v->x;
		out->y = u->y + v->y;
		out->z = u->z + v->z;
	}
	return out;
}

inline
vec3* scalar_mul(vec3* u, double t) {
	if (u) {
		u->x *= t;
		u->y *= t;
		u->z *= t;
	}
	return u;
}

inline
vec3* scalar_div(vec3* u, double t) {
	if (u && t) {
		u->x /= t;
		u->y /= t;
		u->z /= t;
	}
	return u;
}

/**
 * len_squared - computes the square of the magnitude of a vector u. If a NULL value is
 * provided, inf is returned from this function.
 * @u: pointer to a vector.
 * @Returns: |u|^2. Otherwise, `inf`.
 * */
inline
double len_squared(vec3* u) {
	double ret = 1.0 / 0.0;
	if (u) {
		ret = (u->x * u->x) + (u->y * u->y) + (u->z * u->z); 
	}
	return ret;
}

/**
 * len - computes the magnitude of a vector u. If a NULL value is provided, inf is
 * returned from this function.
 * @u: ponter to a vector.
 * @Returns: |u| or `inf`.
 */
inline
double len(vec3* u) {
	double ret = 1.0 / 0.0;
	if (u) {
		ret = sqrt(len_squared(u));
	}
	return ret;
}

inline
vec3* unit_vec3(vec3* u) {
	return u ? scalar_div(u, len(u)) : u;
}

#endif
