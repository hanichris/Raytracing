#ifndef MY_VEC3_H
#define MY_VEC3_H 1

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tuple tuple;
struct tuple {
	double x;
	double y;
	double z;
	double w;
};

typedef tuple point3;
typedef tuple vec3;

void print_vec3(vec3* u);

// Small and frequently used functions are statically inlined.

#define POINT(x, y, z) (point((x), (y), (z), (&(tuple){ })))
static
inline
tuple* point(double x, double y, double z, tuple* out) {
	if (out) {
		out->x = x;
		out->y = y;
		out->z = z;
		out->w = 1.0;
	}
	return out;
}

#define VECTOR(x, y, z) (vector((x), (y), (z), (&(tuple){ })))
static
inline
tuple* vector(double x, double y, double z, tuple* out) {
	if (out) {
		out->x = x;
		out->y = y;
		out->z = z;
		out->w = 0.0;
	}
	return out;
}

#define VEC3_NEGATE(t) (negate((t), (&(tuple){ })))
static
inline
tuple* negate(tuple* t, tuple* out) {
	if (t && out) {
		out->x = -t->x;
		out->y = -t->y;
		out->z = -t->z;
		out->w = -t->w;
		return out;
	}
	return nullptr;
}

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
	return (u && v) ? (u->x * v->x) + (u->y * v->y) + (u->z * v->z) + (u->w * v->w): NAN;
}

#define VEC3_MUL(a, b) (scalar_mul((a), (b), (&(tuple){ })))
/**
 * scalar_mul - computes the multiplication of a tuple `u` with a scalar `t`.
 * The result is stored in the output tuple `out`.
 * @u: pointer to the tuple (input).
 * @t: scalar multiplier of the tuple (input).
 * @out: pointer to the (output) tuple.
 * @Returns: `out` or null.
 */
static
inline
tuple* scalar_mul(tuple const* u, double t, tuple* out) {
	if (u && out) {
		out->x = u->x * t;
		out->y = u->y * t;
		out->z = u->z * t;
		out->w = u->w * t;
		return out;
	}
	return nullptr;
}

#define VEC3_DIV(a, b) (scalar_div((a), (b), (&(tuple){ })))
/**
 * scalar_div - computes the division of a tuple `u` with a scalar `t`.
 * The result is stored in the output tuple.
 * @u: pointer to the tuple (input).
 * @t: scalar divider of the tuple (input).
 * @out: pointer to the (output) tuple.
 * @Returns: `out` or null.
 */
static
inline
tuple* scalar_div(tuple const* u, double t, tuple* out) {
	if (u && out) {
		out->x = u->x / t;
		out->y = u->y / t;
		out->z = u->z / t;
		out->w = u->w / t;
		return out;
	}
	return nullptr;
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
	return u ? (u->x * u->x) + (u->y * u->y) + (u->z * u->z) + (u->w * u->w) : NAN;
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

#define VEC3_UNIT(a) (unit_vec3((a), (&(vec3){ })))
/**
 * unit_vec3 - normalises the vector `u`. This operation involves dividing
 * the vector with its length.
 * @u: pointer to the vector (input).
 * @out: pointer to the output vector.
 * @Returns: a normalised vector.
 */
vec3* unit_vec3(vec3 const* u, vec3* out); 

#define VEC3_SUB(a, b) (sub((a), (b), (&(tuple){ })))
/**
 * sub - computes the difference between two tuples `u` and `v`. The result
 * is stored in the output tuple `out`.
 * @u: pointer to the first tuple (input).
 * @v: pointer to the second tuple (input).
 * @out: ponter to a stack allocated tuple (output).
 * @Returns: `out`.
 */
tuple* sub(tuple const* u, tuple const* t, tuple* out);

#define VEC3_ADD(a, b) (add((a), (b), (&(tuple){ })))
/**
 * add - computes the sum of two tuples `u` and `v`. The result
 * is stored in the output tuple `out`.
 * @u: pointer to the first tuple (input).
 * @v: pointer to the second tuple (input).
 * @out: ponter to a stack allocated tuple (output).
 * @Returns: `out`.
 */
tuple* add(tuple const* u, tuple const* v, tuple* out);

#define VEC3_CROSS(a, b) (cross((a), (b), (&(vec3){ })))
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
vec3* cross(vec3 const* u, vec3 const* v, vec3* out);


#ifdef __cplusplus
}
#endif

#endif
