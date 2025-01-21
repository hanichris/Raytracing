#ifndef MY_MAT_H
#define MY_MAT_H 1

#include <math.h>
#include <stdbool.h>

#include "vec3.h"

/**
 * mat16 - Matrix type (4 x 4 row-major representation.)
 * Has two coinciding representations to enforce readability
 * and ease of iteration on each matrix element.
 */
typedef struct mat16 mat16;
struct mat16 {
	union {
		struct {
			float m00, m01, m02, m03;  // Matrix first row (4-components).
			float m10, m11, m12, m13;  // Matrix second row (4-components).
			float m20, m21, m22, m23;  // Matrix third row (4-components).
			float m30, m31, m32, m33;  // Matrix fourth row (4-components).
		};
		float data[16];
	};
};

#define MAT16_IDENTITY ((mat16){ .m00=1, .m11=1, .m22=1, .m33=1 })

/**
 * mat9 - Matrix type (3 x 3 row-major representation.)
 * Has two coinciding representations to enforce readability
 * and ease of iteration on each matrix element.
 */
typedef struct mat9 mat9;
struct mat9 {
	union {
		struct {
			float m00, m01, m02;  // Matrix first row (3-components).
			float m10, m11, m12;  // Matrix second row (3-components).
			float m20, m21, m22;  // Matrix third row (3-components).
		};
		float data[9];
	};
};

/**
 * mat4 - Matrix type (2 x 2 row-major representation.)
 * Has two coinciding representations to enforce readability
 * and ease of iteration on each matrix element.
 */
typedef struct mat4 mat4;
struct mat4 {
	union {
		struct {
			float m00, m01;  // Matrix first row (2-components).
			float m10, m11;  // Matrix second row (2-components).
		};
		float data[4];
	};
};

/**
 * mat4_determinant - computest the determinant of a 2x2 matrix `a`.
 * @a: pointer to 2x2 matrix.
 * @Returns: determinant of the matrix.
 */
float mat4_determinant(mat4 const* a);

#define MAT16_SUBMATRIX(a, r, c) (mat16_submatrix((a), (r), (c), (&(mat9){ })))
/**
 * mat16_submatrix - create a 3x3 matrix from the 4x4 matrix `a` by eliminating
 * the entries in the provided row `r` and column `c`. The created 3x3 matrix
 * is then stored in the output matrix `out`.
 * @a: pointer to a 4x4 matrix (input).
 * @r: row to eliminate in the 4x4 matrix.
 * @c: column to eliminate in the 4x4 matrix.
 * @out: pointer to a 3x3 matrix (output).
 * @Returns: 3x3 submatrix of a 4x4 matrix if successful. Otherwise, nullptr
 * is returned.
 */
mat9* mat16_submatrix(mat16 const* a, unsigned r, unsigned c, mat9* out);

#define MAT9_SUBMATRIX(a, r, c) (mat9_submatrix((a), (r), (c), (&(mat4){ })))
/**
 * mat9_submatrix - create a 2x2 matrix from the 3x3 matrix `a` by eliminating
 * the entries in the provided row `r` and column `c`. The created 2x2 matrix
 * is then stored in the output matrix `out`.
 * @a: pointer to a 3x3 matrix (input).
 * @r: row to eliminate in the 3x3 matrix.
 * @c: column to eliminate in the 3x3 matrix.
 * @out: pointer to a 2x2 matrix (output).
 * @Returns: 2x2 submatrix of a 4x4 matrix if successful. Otherwise, nullptr
 * is returned.
 */
mat4* mat9_submatrix(mat9 const* a, unsigned r, unsigned c, mat4* out);

/**
 * mat9_minor - computes the minor of the element at a[r][c] within the 3x3
 * matrix a.
 * @a: pointer to a 3x3 matrix (input).
 * @r: row of the element of interest. Using 0-indexing.
 * @c: column of the element of interest. Using 0-indexing.
 * @Returns: The minor of the element at location of interest. NAN, otherwise.
 */
float mat9_minor(mat9 const* a, unsigned r, unsigned c);

/**
 * mat9_cofactor - computes the cofactor of the element at a[r][c] within the
 * 3x3 matrix a.
 * @a: pointer to a 3x3 matrix (input).
 * @r: row of the element of interest. Using 0-indexing.
 * @c: column of the element of interest. Using 0-indexing.
 * @ReturnsL The cofactor of the element at the specified location. NAN, otherwise.
 */
float mat9_cofactor(mat9 const* a, unsigned r, unsigned c);

/**
 * mat16_is_equal - tests the equality of two 4x4 matrices. If every
 * element of matrix `a` is equal to every element of matrix
 * `b`, then we can say that both matrices are equal. Otherwise,
 * they are not equal.
 * @a: pointer to a 4x4 matrix.
 * @b: pointer to a 4x4 matrix.
 * @Returns: true if they are equal. Otherwise, false.
 */
bool mat16_is_equal(mat16 const* a, mat16 const* b);

#define MAT16_MUL(a, b) (mat16_mul((a), (b), (&(mat16){ })))
/**
 * mat16_mul - multiplies two 4x4 matrices: matrix a and matrix b. The result of
 * the operation is stored in the output 4x4 matrix `c`.
 * @a: pointer to a 4x4 matrix (first input).
 * @b: pointer to a 4x4 matrix (second input).
 * @c: pointer to a 4x4 matrix (output).
 * @Returns: matrix c that holds the result of the multiplication. Otherwise, null.
 */
mat16* mat16_mul(mat16 const* a, mat16 const* b, mat16* c);

#define MAT16_MUL_TUPLE(a, b) (mat16_mul_by_tuple((a), (b), (&(tuple){ })))
/**
 * mat16_mul_by_tuple - multiples a 4x4 matrix `a` by tuple `b. The result of
 * the operation is a tuple that is stored in `out`.
 * @a: pointer to a 4x4 matrix (first input).
 * @b: pointer to a tuple (second input).
 * @c: pointer to a tuple (output).
 * @Returns: tuple c that holds the result of the operation. Otherwise, null.
 */
tuple* mat16_mul_by_tuple(mat16 const* a, tuple const* b, tuple* out);

/**
 * mat16_transpose - transposes a 4x4 matrix `a`. This involves turning the rows
 * of the matrix into the columns and the columns into the rows.
 * @a: pointer to 4x4 matrix (input).
 * @Returns: transpose of `a`. Otherwise, null.
 */
mat16* mat16_transpose(mat16* a);
#endif
