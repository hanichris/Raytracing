#include "../src/headers/vec3.h"
#include "test_main.h"

#define EPSILON 1E-9

static
bool float_equal(double a, double b) {
	return fabs(a - b) < EPSILON;
}

static
void test_tuple_is_a_point(tuple* t) {
	if (t) {
		assert(float_equal(t->w, 1.0));
		putchar('.');
	}
}

static
void test_tuple_is_a_vector(tuple* t) {
	if (t) {
		assert(float_equal(t->w, 0.0));
		putchar('.');
	}
}

static
void test_cross(void) {
	vec3 u = VECTOR(1, 2, 3);
	vec3 v = VECTOR(2, 3, 4);

	vec3* out = VEC3_CROSS(&u, &v);

	assert(float_equal(out->x, -1.0));
	assert(float_equal(out->y, 2.0));
	assert(float_equal(out->z, -1.0));

	out = VEC3_CROSS(&v, &u);

	assert(float_equal(out->x, 1.0));
	assert(float_equal(out->y, -2.0));
	assert(float_equal(out->z, 1.0));

	putchar('.');
}

static
void test_cross_null(void) {
	vec3 u = VECTOR(1, 2, 3);
	vec3 v = VECTOR(4, 5, 6);
	vec3 out;

	assert(cross(NULL, &v, &out) == NULL);
	assert(cross(&u, NULL, &out) == NULL);
	assert(cross(&u, &v, NULL) == NULL);

	putchar('.');
}

static
void test_dot(void) {
	vec3 u = VECTOR(1, 2, 3);
	vec3 v = VECTOR(4, 5, 6);

	double res = dot(&u, &v);

	assert(float_equal(res, 32.0));
	putchar('.');
}

static
void test_dot_null(void) {
	vec3 u = VECTOR(1, 2, 3);

	assert(isnan(dot(&u, NULL)));
	assert(isnan(dot(NULL, &u)));

	putchar('.');
}

static
void test_add_tuples(void) {
	tuple u = { .x=3, .y=-2, .z=5, .w=1 };
	tuple v = { .x=-2, .y=3, .z=1, .w=0 };

	tuple* out = VEC3_ADD(&u, &v);

	assert(float_equal(out->x, 1.0));
	assert(float_equal(out->y, 1.0));
	assert(float_equal(out->z, 6.0));
	assert(float_equal(out->w, 1.0));

	putchar('.');
}

static
void test_sub_a_vector_from_a_point(void) {
	point3 p = POINT(3, 2, 1);
	vec3 v = VECTOR(5, 6, 7);

	vec3* out = VEC3_SUB(&p, &v);

	assert(float_equal(out->x, -2.0));
	assert(float_equal(out->y, -4.0));
	assert(float_equal(out->z, -6.0));
	assert(float_equal(out->w, 1.0));

	putchar('.');
}

static
void test_sub_a_vector_from_zero_vector(void) {
	vec3 p = VECTOR(0, 0, 0);
	vec3 q = VECTOR(5, 6, 7);

	vec3* out = VEC3_SUB(&p, &q);

	assert(float_equal(out->x, -5.0));
	assert(float_equal(out->y, -6.0));
	assert(float_equal(out->z, -7.0));
	assert(float_equal(out->w, 0.0));

	putchar('.');
}

static
void test_sub_two_vectors(void) {
	vec3 p = VECTOR(3, 2, 1);
	vec3 q = VECTOR(5, 6, 7);

	vec3* out = VEC3_SUB(&p, &q);

	assert(float_equal(out->x, -2.0));
	assert(float_equal(out->y, -4.0));
	assert(float_equal(out->z, -6.0));
	assert(float_equal(out->w, 0.0));

	putchar('.');
}

static
void test_sub_two_points(void) {
	point3 p = POINT(3, 2, 1);
	point3 q = POINT(5, 6, 7);

	vec3* out = VEC3_SUB(&p, &q);

	assert(float_equal(out->x, -2.0));
	assert(float_equal(out->y, -4.0));
	assert(float_equal(out->z, -6.0));
	assert(float_equal(out->w, 0.0));

	putchar('.');
}

static
void test_negate_a_tuple(void) {
	tuple t = { .x=1, .y=-2, .z=3, .w=-4 };

	tuple* out = VEC3_NEGATE(&t);

	assert(float_equal(out->w, 4.0));
	assert(float_equal(out->x, -1.0));
	assert(float_equal(out->y, 2.0));
	assert(float_equal(out->z, -3.0));

	putchar('.');
}

static
void test_scalar_mul_tuple_with_fraction(void) {
	tuple u = { .x=1.0, .y=-2.0, .z=3.0, .w=-4.0 };

	tuple* v = VEC3_MUL(&u, 0.5);

	assert(float_equal(v->x, 0.5));
	assert(float_equal(v->y, -1.0));
	assert(float_equal(v->z, 1.5));
	assert(float_equal(v->w, -2.0));

	putchar('.');
}

static
void test_scalar_mul_tuple(void) {
	tuple u = { .x=1.0, .y=-2.0, .z=3.0, .w=-4.0 };

	tuple* v = VEC3_MUL(&u, 3.5);

	assert(float_equal(v->x, 3.5));
	assert(float_equal(v->y, -7.0));
	assert(float_equal(v->z, 10.5));
	assert(float_equal(v->w, -14.0));

	putchar('.');
}

static
void test_scalar_div(void) {
	tuple t = { .x=1, .y=-2, .z=3, .w=-4 };

	tuple* v = VEC3_DIV(&t, 2.0);

	assert(float_equal(v->x, 0.5));
	assert(float_equal(v->y, -1.0));
	assert(float_equal(v->z, 1.5));
	assert(float_equal(v->w, -2.0));

	putchar('.');
}

static
void test_scalar_div_zero(void) {
	tuple t = { .x=1.0, .y=2.0, .z=3.0, .w=4.0 };

	tuple* v = VEC3_DIV(&t, 0.0);

	assert(isinf(v->x));
	assert(isinf(v->y));
	assert(isinf(v->z));
	assert(isinf(v->w));

	putchar('.');
}

static
void test_len_squared(void) {
	vec3 u = VECTOR(1, 0, 0);
	double result = len_squared(&u);
	assert(float_equal(result, 1.0));

	u = VECTOR(0, 1, 0);
	result = len_squared(&u);
	assert(float_equal(result, 1.0));

	u = VECTOR(0, 0, 1);
	result = len_squared(&u);
	assert(float_equal(result, 1.0));

	u = VECTOR(1, 2, 3);
	result = len_squared(&u);
	assert(float_equal(result, 14));

	u = VECTOR(-1, -2, -3);
	result = len_squared(&u);
	assert(float_equal(result, 14));

	putchar('.');
	
}

static
void test_len(void) {
	vec3 u = VECTOR(1, 0, 0);
	double result = len(&u);
	assert(float_equal(result, 1.0));

	u = VECTOR(0, 1, 0);
	result = len(&u);
	assert(float_equal(result, 1.0));

	u = VECTOR(0, 0, 1);
	result = len(&u);
	assert(float_equal(result, 1.0));

	u = VECTOR(1, 2, 3);
	result = len(&u);
	assert(float_equal(result, sqrt(14)));

	u = VECTOR(-1, -2, -3);
	result = len(&u);
	assert(float_equal(result, sqrt(14)));

	putchar('.');
}

static
void test_len_squared_null_pointer(void) {
	double result = len_squared(nullptr);
	assert(isnan(result));
}

static
void test_len_null_pointer(void) {
	double result = len(nullptr);
	assert(isnan(result));
}

static
void test_unit_vec3(void) {
	vec3 u = VECTOR(4, 0, 0);
	vec3* v = VEC3_UNIT(&u);
	assert(float_equal(v->x, 1.0));
	assert(float_equal(v->y, 0.0));
	assert(float_equal(v->z, 0.0));

	u = VECTOR(1, 2, 3);
	v = VEC3_UNIT(&u);
	assert(float_equal(v->x, 0.2672612419));
	assert(float_equal(v->y, 0.5345224838));
	assert(float_equal(v->z, 0.8017837257));

	putchar('.');
}

static
void test_magnitude_of_unit_vector(void) {
	vec3 u = VECTOR(1, 2, 3);

	vec3* norm = VEC3_UNIT(&u);
	double result = len(norm);

	assert(float_equal(result, 1.0));

	putchar('.');
}


void run_vec3_tests(void) {
	point3 p = POINT(4, -4, 3);
	vec3 v = VECTOR(4, -4, 3);
	test_tuple_is_a_point(&p);
	test_tuple_is_a_vector(&v);
	test_add_tuples();
	test_sub_a_vector_from_a_point();
	test_sub_two_points();
	test_sub_two_vectors();
	test_sub_a_vector_from_zero_vector();
	test_negate_a_tuple();
	test_scalar_mul_tuple();
	test_scalar_mul_tuple_with_fraction();
	test_scalar_div();
	test_scalar_div_zero();
	test_len();
	test_len_null_pointer();
	test_len_squared();
	test_len_squared_null_pointer();
	test_unit_vec3();
	test_magnitude_of_unit_vector();
	test_cross();
	test_cross_null();
	test_dot();
	test_dot_null();
}

