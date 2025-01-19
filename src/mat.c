#include "headers/mat.h"

#define EPSILON 1E-5

static
bool float_equal(float a, float b) {
	return fabsf(a - b) < EPSILON;
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

static
void swap(float* restrict a, float* restrict b) {
	float tmp = *a;
	*a = *b;
	*b = tmp;
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
#undef EPSILON
