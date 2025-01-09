#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "../src/headers/vec3.h"

#define EPSILON 1E-9

bool float_equal(double a, double b) {
	return fabs(a - b) < EPSILON;
}

void test_cross(void) {
	vec3 u = {1.0, 2.0, 3.0};
	vec3 v = {4.0, 5.0, 6.0};
	vec3 out = { };
	
	cross(&u, &v, &out);

	assert(float_equal(out.x, -3.0));
	assert(float_equal(out.y, 6.0));
	assert(float_equal(out.z, -3.0));
	//printf("'test_cross' passed.\n");
	putchar('.');
	
}

void test_cross_null(void) {
	vec3 u = {1.0, 2.0, 3.0};
	vec3 v = {4.0, 5.0, 6.0};
	vec3 out;

	assert(cross(NULL, &v, &out) == NULL);
	assert(cross(&u, NULL, &out) == NULL);
	assert(cross(&u, &v, NULL) == NULL);

	putchar('.');
	
	//printf("'test_cross_null' passed.\n");
}

void test_dot(void) {
	vec3 u = {1.0, 2.0, 3.0};
	vec3 v = {4.0, 5.0, 6.0};

	double res = dot(&u, &v);

	assert(float_equal(res, 32.0));
	putchar('.');
	
	//printf("'test_dot' passed.\n");
}

void test_dot_null(void) {
	vec3 u = {1.0, 2.0, 3.0};
	vec3 v = {4.0, 5.0, 6.0};

	assert(isnan(dot(&u, NULL)));
	assert(isnan(dot(&v, NULL)));

	putchar('.');
	
	//printf("'test_dot_null' passed.\n");
}

void test_add() {
	vec3 u = {1.0, 2.0, 3.0};
	vec3 v = {4.0, 5.0, 6.0};
	vec3 out;

	add(&u, &v, &out);

	assert(float_equal(out.x, 5.0));
	assert(float_equal(out.y, 7.0));
	assert(float_equal(out.z, 9.0));

	putchar('.');
	
	//printf("'test_add' passed\n");
}

void test_sub() {
	vec3 u = {1.0, 2.0, 3.0};
	vec3 v = {4.0, 5.0, 6.0};
	vec3 out;

	sub(&u, &v, &out);

	assert(float_equal(out.x, -3.0));
	assert(float_equal(out.y, -3.0));
	assert(float_equal(out.z, -3.0));

	putchar('.');
	
	//printf("'test_sub' passed\n");
}

void test_scalar_mul() {
	vec3 u = {1.0, 2.0, 3.0};

	scalar_mul(&u, 2.0);

	assert(float_equal(u.x, 2.0));
	assert(float_equal(u.y, 4.0));
	assert(float_equal(u.z, 6.0));

	putchar('.');
	
	//printf("'test_scalar_mul' passed\n");
}

void test_scalar_div() {
	vec3 u = {2.0, 4.0, 6.0};

	scalar_div(&u, 2.0);

	assert(float_equal(u.x, 1.0));
	assert(float_equal(u.y, 2.0));
	assert(float_equal(u.z, 3.0));

	putchar('.');
	
	//printf("'test_scalar_div' passed\n");
}

void test_scalar_div_zero() {
	vec3 u = {1.0, 2.0, 3.0};
	scalar_div(&u, 0.0);

	assert(isinf(u.x));
	assert(isinf(u.y));
	assert(isinf(u.z));

	putchar('.');
	
	//printf("test_scalar_div_zero passed\n");
}

void test_len_squared() {
	vec3 u = {1.0, 2.0, 3.0};

	double result = len_squared(&u);

	assert(float_equal(result, 14.0));

	putchar('.');
	
	//printf("'test_len_squared' passed\n");
}

void test_len() {
	vec3 u = {1.0, 2.0, 3.0};

	double result = len(&u);

	assert(float_equal(result, sqrt(14.0)));

	putchar('.');
	
	//printf("'test_len' passed\n");
}

void test_unit_vec3() {
	vec3 u = {3.0, 0.0, 4.0};

	unit_vec3(&u);

	assert(float_equal(u.x, 0.6));
	assert(float_equal(u.y, 0.0));
	assert(float_equal(u.z, 0.8));

	//printf("'test_unit_vec3' passed\n");
	putchar('.');
	
}


void run_tests(void) {
	test_cross();
	test_cross_null();
	test_dot();
	test_dot_null();
	test_add();
	test_sub();
	test_scalar_mul();
	test_scalar_div();
	test_scalar_div_zero();
	test_len_squared();
	test_len();
	test_unit_vec3();
	printf("\nAll tests run successfully.\n");
}

int main(void) {
	run_tests();

	return 0;
}
