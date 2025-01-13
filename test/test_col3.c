#include "../src/headers/colour.h"
#include "test_main.h"

#define EPSILON 1E-5

static
bool float_equal(float x, float y) {
	return fabsf(x - y) < EPSILON;
}

static
void test_colour_creation(void) {
	col3* c = COLOUR(-0.5, 0.4, 1.7);

	assert(float_equal(c->red, -0.5));
	assert(float_equal(c->green, 0.4));
	assert(float_equal(c->blue, 1.7));

	putchar('.');
}

static
void test_colour_addition(void) {
	col3* c = COLOUR(0.9, 0.6, 0.75);
	col3* d = COLOUR(0.7, 0.1, 0.25);

	col3* out = COL3_ADD(c, d);
	assert(float_equal(out->red, 1.6));
	assert(float_equal(out->green, 0.7));
	assert(float_equal(out->blue, 1.0));
}

static
void test_colour_subtraction(void) {
	col3* c = COLOUR(0.9, 0.6, 0.75);
	col3* d = COLOUR(0.7, 0.1, 0.25);

	col3* out = COL3_SUB(c, d);
	assert(float_equal(out->red, 0.2));
	assert(float_equal(out->green, 0.5));
	assert(float_equal(out->blue, 0.5));
}

static
void test_colour_multiplication(void) {
	col3* c = COLOUR(0.9, 0.6, 0.75);

	col3* out = COL3_MUL(c, 2);
	assert(float_equal(out->red, 1.8));
	assert(float_equal(out->green, 1.2));
	assert(float_equal(out->blue, 1.5));
}


void run_col3_tests(void) {
	test_colour_creation();
	test_colour_addition();
	test_colour_subtraction();
	test_colour_multiplication();
}

