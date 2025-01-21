#include "../src/headers/mat.h"
#include "test_main.h"

#ifndef EPSILON
# define EPSILON 1E-5
#endif

static
bool float_equal(float a, float b) {
	return fabsf(a - b) < EPSILON;
}

static
void test_mat_create_4x4_matrix(void) {
	mat16 M = {
		.m00=1,   .m01=2,   .m02=3,   .m03=4,
		.m10=5.5, .m11=6.5, .m12=7.5, .m13=8.5,
		.m20=9,   .m21=10,  .m22=11,  .m23=12,
		.m30=13.5,.m31=14.5,.m32=15.5,.m33=16.5,
	};

	assert(float_equal(M.data[0], 1));
	assert(float_equal(M.data[3], 4));
	assert(float_equal(M.data[4], 5.5));
	assert(float_equal(M.data[6], 7.5));
	assert(float_equal(M.data[10], 11));
	assert(float_equal(M.data[12], 13.5));
	assert(float_equal(M.data[15], 16.5));

	putchar('.');
}

static
void test_mat_create_3x3_matrix(void) {
	mat9 M = {
		.m00=-3, .m01=5,  .m02=0,
		.m10=1,  .m11=-2, .m12=-7,
		.m20=0,  .m21=1,  .m22=1,
	};

	assert(float_equal(M.data[0], -3));
	assert(float_equal(M.data[4], -2));
	assert(float_equal(M.data[8], 1));

	putchar('.');
}

static
void test_mat_create_2x2_matrix(void) {
	mat4 M = {
		.m00=-3, .m01=5,
		.m10=1,  .m11=-2,
	};

	assert(float_equal(M.data[0], -3));
	assert(float_equal(M.data[1], 5));
	assert(float_equal(M.data[2], 1));
	assert(float_equal(M.data[3], -2));

	putchar('.');
}

static
void test_mat_equality_of_4x4_matrices(void) {
	mat16 A = {
		.m00=1, .m01=2, .m02=3, .m03=4,
		.m10=5, .m11=6, .m12=7, .m13=8,
		.m20=9, .m21=10,.m22=11,.m23=12,
		.m30=13,.m31=14,.m32=15,.m33=16,
	};

	mat16 B = {
		.m00=1, .m01=2, .m02=3, .m03=4,
		.m10=5, .m11=6, .m12=7, .m13=8,
		.m20=9, .m21=10,.m22=11,.m23=12,
		.m30=13,.m31=14,.m32=15,.m33=16,
	};

	assert(mat16_is_equal(&A, &B) == true);
	assert(mat16_is_equal(&A, &(mat16) {.m00=1, .m01=2, .m02=3, .m03=4 }) == false);

	putchar('.');
}

static
void test_mat_equality_of_4x4_matrix_to_nullptr(void) {
	mat16 A = {
		.m00=1, .m01=2, .m02=3, .m03=4,
		.m10=5, .m11=6, .m12=7, .m13=8,
		.m20=9, .m21=10,.m22=11,.m23=12,
		.m30=13,.m31=14,.m32=15,.m33=16,
	};

	assert(mat16_is_equal(&A, NULL) == false);
	assert(mat16_is_equal(NULL, &A) == false);

	putchar('.');
}

static
void test_mat_equality_of_4x4_matrix_to_itself(void) {
	mat16 A = {
		.m00=1, .m01=2, .m02=3, .m03=4,
		.m10=5, .m11=6, .m12=7, .m13=8,
		.m20=9, .m21=10,.m22=11,.m23=12,
		.m30=13,.m31=14,.m32=15,.m33=16,
	};

	assert(mat16_is_equal(&A, &A) == true);

	putchar('.');
}

static
void test_mat_multiply_two_4x4_matrices(void) {
	mat16 A = {
		.m00=1, .m01=2, .m02=3, .m03=4,
		.m10=5, .m11=6, .m12=7, .m13=8,
		.m20=9, .m21=8, .m22=7, .m23=6,
		.m30=5, .m31=4, .m32=3, .m33=2,
	};

	mat16 B = {
		.m00=-2, .m01=1, .m02=2, .m03=3,
		.m10=3,  .m11=2, .m12=1, .m13=-1,
		.m20=4,  .m21=3, .m22=6, .m23=5,
		.m30=1,  .m31=2, .m32=7, .m33=8,
	};

	mat16 res = {
		.m00=20, .m01=22, .m02=50, .m03=48,
		.m10=44, .m11=54, .m12=114,.m13=108,
		.m20=40, .m21=58, .m22=110,.m23=102,
		.m30=16, .m31=26, .m32=46, .m33=42,
	};

	mat16* C = MAT16_MUL(&A, &B);

	assert(mat16_is_equal(C, &res) == true);

	putchar('.');

}

static
void test_mat_multiply_a_matrix_with_nullptr(void) {
	mat16 B = {
		.m00=-2, .m01=1, .m02=2, .m03=3,
		.m10=3,  .m11=2, .m12=1, .m13=-1,
		.m20=4,  .m21=3, .m22=6, .m23=5,
		.m30=1,  .m31=2, .m32=7, .m33=8,
	};

	assert(MAT16_MUL(&B, NULL) == NULL);
	assert(MAT16_MUL(NULL, &B) == NULL);

	putchar('.');
}

static
void test_mat_multiply_a_matrix_with_tuple(void) {
	mat16 A = {
		.m00=1, .m01=2, .m02=3, .m03=4,
		.m10=2, .m11=4, .m12=4, .m13=2,
		.m20=8, .m21=6, .m22=4, .m23=1,
		.m30=0, .m31=0, .m32=0, .m33=1,
	};
	tuple b = { .x=1, .y=2, .z=3, .w=1 };

	tuple* out = MAT16_MUL_TUPLE(&A, &b);

	assert(float_equal(out->x, 18));
	assert(float_equal(out->y, 24));
	assert(float_equal(out->z, 33));
	assert(float_equal(out->w, 1));

	putchar('.');
}

static
void test_mat_multiply_a_matrix_by_NULL_tuple(void) {
	mat16 A = {
		.m00=1, .m01=2, .m02=3, .m03=4,
		.m10=2, .m11=4, .m12=4, .m13=2,
		.m20=8, .m21=6, .m22=4, .m23=1,
		.m30=0, .m31=0, .m32=0, .m33=1,
	};
	tuple b = { .x=1, .y=2, .z=3, .w=1 };

	assert(MAT16_MUL_TUPLE(&A, NULL) == NULL);
	assert(MAT16_MUL_TUPLE(NULL, &b) == NULL);

	putchar('.');
}

static
void test_mat_multiply_a_matrix_with_identity_matrix(void) {
	mat16 A = {
		.m00=0, .m01=1, .m02=2, .m03=4,
		.m10=1, .m11=2, .m12=4, .m13=8,
		.m20=2, .m21=4, .m22=8, .m23=16,
		.m30=4, .m31=8, .m32=16,.m33=32,
	};

	mat16 B = MAT16_IDENTITY;

	mat16* C = MAT16_MUL(&A, &B);

	assert(mat16_is_equal(C, &A) == true);

	putchar('.');
}

static
void test_mat_multiply_a_tuple_with_identity_matrix(void) {
	tuple a = { .x=1, .y=2, .z=3, .w=4 };

	tuple* c = MAT16_MUL_TUPLE(&MAT16_IDENTITY, &a);

	assert(float_equal(c->x, a.x));
	assert(float_equal(c->y, a.y));
	assert(float_equal(c->z, a.z));
	assert(float_equal(c->w, a.w));

	putchar('.');
}

static
void test_mat_transpose_4x4_matrix(void) {
	mat16 A = {
		.m00=0, .m01=9, .m02=3, .m03=0,
		.m10=9, .m11=8, .m12=0, .m13=8,
		.m20=1, .m21=8, .m22=5, .m23=3,
		.m30=0, .m31=0, .m32=5, .m33=8,
	};

	mat16 transpose_A = {
		.m00=0, .m01=9, .m02=1, .m03=0,
		.m10=9, .m11=8, .m12=8, .m13=0,
		.m20=3, .m21=0, .m22=5, .m23=5,
		.m30=0, .m31=8, .m32=3, .m33=8,
	};

	assert(mat16_is_equal(mat16_transpose(&A), &transpose_A) == true);

	putchar('.');
}

static
void test_mat_transpose_4x4_identity_matrix(void) {
	assert(mat16_is_equal(mat16_transpose(&MAT16_IDENTITY), &MAT16_IDENTITY));

	putchar('.');
}

static
void test_mat_2x2_determinant(void) {
	mat4 a = {
		.m00=1, .m01=5,
		.m10=-3,.m11=2,
	};

	assert(float_equal(mat4_determinant(&a), 17));

	putchar('.');
}


static
void test_mat_2x2_determinant_nullptr(void) {
	assert(isnan(mat4_determinant(NULL)));

	putchar('.');
}

static
void test_mat_create_3x3_submatrix_of_4x4_matrix(void) {
	mat16 a = {
		.m00=-6, .m01=1, .m02=1, .m03=6,
		.m10=-8, .m11=5, .m12=8, .m13=6,
		.m20=-1, .m21=0, .m22=8, .m23=2,
		.m30=-7, .m31=1, .m32=-1,.m33=1,
	};

	mat9* out = MAT16_SUBMATRIX(&a, 2, 1);
	
	assert(float_equal(out->m00, -6));
	assert(float_equal(out->m01, 1));
	assert(float_equal(out->m02, 6));
	assert(float_equal(out->m10, -8));
	assert(float_equal(out->m11, 8));
	assert(float_equal(out->m12, 6));
	assert(float_equal(out->m20, -7));
	assert(float_equal(out->m21, -1));
	assert(float_equal(out->m22, 1));

	putchar('.');

}

static
void test_mat_create_3x3_submatrix_of_4x4_matrix_outofboundsaccess(void) {
	mat16 a = {
		.m00=-6, .m01=1, .m02=1, .m03=6,
		.m10=-8, .m11=5, .m12=8, .m13=6,
		.m20=-1, .m21=0, .m22=8, .m23=2,
		.m30=-7, .m31=1, .m32=-1,.m33=1,
	};

	mat9* out = MAT16_SUBMATRIX(&a, 10, 1);

	assert(out == NULL);
	putchar('.');
}

static
void test_mat_create_3x3_submatrix_of_4x4_matrix_null(void) {
	assert(MAT16_SUBMATRIX(NULL, 10, 1) == NULL);

	putchar('.');
}

static
void test_mat_create_2x2_submatrix_of_3x3_matrix(void) {
	mat9 a = {
		.m00=1, .m01=5, .m02=0,
		.m10=-3,.m11=2, .m12=7,
		.m20=0, .m21=6, .m22=-3,
	};

	mat4* out = MAT9_SUBMATRIX(&a, 0, 2);

	assert(float_equal(out->m00, -3));
	assert(float_equal(out->m01, 2));
	assert(float_equal(out->m10, 0));
	assert(float_equal(out->m11, 6));

	putchar('.');
}

static
void test_mat_create_2x2_submatrix_of_3x3_matrix_outofboundsaccess(void) {
	mat9 a = {
		.m00=1, .m01=5, .m02=0,
		.m10=-3,.m11=2, .m12=7,
		.m20=0, .m21=6, .m22=-3,
	};

	mat4* out = MAT9_SUBMATRIX(&a, 1, -1);

	assert(out == NULL);
	putchar('.');
}

static
void test_mat_create_2x2_submatrix_of_3x3_matrix_null(void) {
	mat4* out = MAT9_SUBMATRIX(NULL, 0, 0);

	assert(out == NULL);
	putchar('.');
}

void run_mat_tests(void) {
	test_mat_create_4x4_matrix();
	test_mat_create_3x3_matrix();
	test_mat_create_2x2_matrix();
	test_mat_equality_of_4x4_matrices();
	test_mat_equality_of_4x4_matrix_to_itself();
	test_mat_equality_of_4x4_matrix_to_nullptr();
	test_mat_multiply_two_4x4_matrices();
	test_mat_multiply_a_matrix_with_nullptr();
	test_mat_multiply_a_matrix_with_tuple();
	test_mat_multiply_a_matrix_by_NULL_tuple();
	test_mat_multiply_a_matrix_with_identity_matrix();
	test_mat_multiply_a_tuple_with_identity_matrix();
	test_mat_transpose_4x4_matrix();
	test_mat_transpose_4x4_identity_matrix();
	test_mat_2x2_determinant();
	test_mat_2x2_determinant_nullptr();
	test_mat_create_3x3_submatrix_of_4x4_matrix();
	test_mat_create_2x2_submatrix_of_3x3_matrix();
	test_mat_create_3x3_submatrix_of_4x4_matrix_outofboundsaccess();
	test_mat_create_2x2_submatrix_of_3x3_matrix_outofboundsaccess();
	test_mat_create_3x3_submatrix_of_4x4_matrix_null();
	test_mat_create_2x2_submatrix_of_3x3_matrix_null();
}

#undef EPSILON
