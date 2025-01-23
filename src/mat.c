#include "headers/mat.h"
#include <stdio.h>

#define EPSILON 1E-5

static
bool float_equal(float a, float b) {
	return fabsf(a - b) < EPSILON;
}

static
void swap(float* restrict a, float* restrict b) {
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

bool mat16_is_equal(mat16 const* a, mat16 const* b) {
	bool flag = false;
	if (a && b) {
		for (unsigned i = 0; i < 16; i++)
			if (!float_equal(a->data[i], b->data[i]))
				return flag;
		flag = true;
	}
	return flag;
}

mat16* mat16_mul(mat16 const* a, mat16 const* b, mat16* c) {
	if (a && b && c) {
		for (unsigned i = 0; i < 4; i++)
			for (unsigned j = 0; j < 4; j++) {
				float _a = a->data[i*4+0] * b->data[0*4+j];
				float _b = a->data[i*4+1] * b->data[1*4+j];
				float _c = a->data[i*4+2] * b->data[2*4+j];
				float _d = a->data[i*4+3] * b->data[3*4+j];

				c->data[i*4+j] = _a + _b + _c + _d;
			}
		return c;
	}
	return nullptr;
}

tuple* mat16_mul_by_tuple(mat16 const* a, tuple const* b, tuple* out) {
	if (a && b && out) {
		for (unsigned i = 0; i < 4; i++) {
			float _a = a->data[i*4+0] * b->x;
			float _b = a->data[i*4+1] * b->y;
			float _c = a->data[i*4+2] * b->z;
			float _d = a->data[i*4+3] * b->w;

			out->data[i] = _a + _b + _c + _d;
		}
		return out;
	}
	return nullptr;
}

mat16* mat16_transpose(mat16 *a) {
	if (a) {
		swap(&a->m01, &a->m10);
		swap(&a->m02, &a->m20);
		swap(&a->m03, &a->m30);
		swap(&a->m12, &a->m21);
		swap(&a->m13, &a->m31);
		swap(&a->m23, &a->m32);
	}
	return a;
}

float mat4_determinant(mat4 const* a) {
	if (a) {
		float first_diagonal = a->data[0] * a->data[3];
		float sec_diagonal = a->data[1] * a->data[2];
		return first_diagonal - sec_diagonal;
	}
	return NAN;
}


float mat9_minor(mat9 const* a, unsigned r, unsigned c) {
	return a ? mat4_determinant(MAT9_SUBMATRIX(a, r, c)): NAN;
}

float mat9_cofactor(mat9 const* a, unsigned r, unsigned c) {
	if (a) {
		float res = mat9_minor(a, r, c);
		return (r + c) & 1 ? -res: res; 
	}
	return NAN;
}

float mat9_determinant(const mat9 *a) {
	if (a) {
		float col0 = a->m00 * mat9_cofactor(a, 0, 0);
		float col1 = a->m01 * mat9_cofactor(a, 0, 1);
		float col2 = a->m02 * mat9_cofactor(a, 0, 2);
		return col0 + col1 + col2;
	}
	return NAN;
}

float mat16_minor(mat16 const* a, unsigned r, unsigned c) {
	return a ? mat9_determinant(MAT16_SUBMATRIX(a, r, c)) : NAN;
}

float mat16_cofactor(mat16 const* a, unsigned r, unsigned c) {
	if (a) {
		float res = mat16_minor(a, r, c);
		return (r + c) & 1 ? -res: res;
	}
	return NAN;
}

float mat16_determinant(const mat16 *a) {
	if (a) {
		float col0 = a->m00 * mat16_cofactor(a, 0, 0);
		float col1 = a->m01 * mat16_cofactor(a, 0, 1);
		float col2 = a->m02 * mat16_cofactor(a, 0, 2);
		float col3 = a->m03 * mat16_cofactor(a, 0, 3);
		return col0 + col1 + col2 + col3;
	}
	return NAN;
}

mat9* mat16_submatrix(mat16 const* a, unsigned r, unsigned c, mat9* out) {
	if (a && out) {
		if (r > 3 || c > 3)
			return nullptr;
		unsigned idx = 0; // iterator for `a`.
		unsigned jdx = 0; // iterator for `out`.
		unsigned row = r * 4; // Starting index of the row to eliminate.
		unsigned col = c; // Keeps track of the column elements to skip over.

		while (idx < 16) {
			if (idx >= row && idx < row + 4) {
				idx += 4; // Skip the entire row.
				col += 4; // Advance to the next column element to skip over.
				continue;
			}

			if (idx == col) {
				++idx; // Skip column element.
				col += 4; // Advance to the next column element to skip over.
				continue;
			}
			out->data[jdx++] = a->data[idx++];
		}
		return out;
	}
	return nullptr;
}

mat4* mat9_submatrix(mat9 const* a, unsigned r, unsigned c, mat4* out) {
	if (a && out) {
		if (r > 2 || c > 2)
			return nullptr;
		unsigned idx = 0; // iterator for `a`.
		unsigned jdx = 0; // iterator for `out`.
		unsigned row = r * 3; // Starting index of the row to eliminate.
		unsigned col = c; // Keeps track of the column elements to skip over.

		while (idx < 9) {
			if (idx >= row && idx < row + 3) {
				idx += 3; // Skip the entire row.
				col += 3; // Advance to the next column element to skip over.
				continue;
			}

			if (idx == col) {
				++idx; // Skip column element.
				col += 3; // Advance to the next column element to skip over.
				continue;
			}
			out->data[jdx++] = a->data[idx++];
		}
		return out;
	}
	return nullptr;
}

mat16* mat16_inverse(mat16 const* a, mat16* out) {
	if (a && out) {
		float det_a = mat16_determinant(a);
		if (float_equal(det_a, 0)) {
			fprintf(stderr, "Matrix is not invertible.\n");
			return nullptr;
		}
		for (unsigned r = 0; r < 4; r++)
			for (unsigned c = 0; c < 4; c++)
				out->data[c * 4 + r] = mat16_cofactor(a, r, c) / det_a;
		return out;

	}
	return nullptr;
}
#undef EPSILON
