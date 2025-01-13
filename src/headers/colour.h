#ifndef MY_COLOUR_H
#define MY_COLOUR_H 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct col3 col3;
struct col3 {
	float red;
	float green;
	float blue;
};


#define COLOUR(r, g, b) (colour((r), (g), (b), (&(col3){ })))
static
inline
col3* colour(float r, float g, float b, col3* out) {
	if (out) {
		out->red = r;
		out->green = g;
		out->blue = b;
	}
	return out;
}

#define COL3_ADD(u, v) (col_add((u), (v), (&(col3){ })))
static
inline
col3* col_add(col3 const* a, col3 const* b, col3* c) {
	if (a && b && c) {
		c->blue = a->blue + b->blue;
		c->green = a->green + b->green;
		c->red = a->red + b->red;
		return c;
	}
	return nullptr;
}

#define COL3_SUB(u, v) (col_sub((u), (v), (&(col3){ })))
static
inline
col3* col_sub(col3 const* a, col3 const* b, col3* c) {
	if (a && b && c) {
		c->blue = a->blue - b->blue;
		c->green = a->green - b->green;
		c->red = a->red - b->red;
		return c;
	}
	return nullptr;
}

#define COL3_MUL(u, v) (col_scalar_mul((u), (v), (&(col3){ })))
static
inline
col3* col_scalar_mul(col3 const* a, float b, col3* c) {
	if (a && c) {
		c->blue = a->blue * b;
		c->green = a->green * b;
		c->red = a->red * b;
		return c;
	}
	return nullptr;
}

#define COL3_HADAMARD(u, v) (col_hadamard_mul((u), (v), (&(col3){ })))
static
inline
col3* col_hadamard_mul(col3 const* a, col3 const* b, col3* c) {
	if (a && b && c) {
		c->red = a->red * b->red;
		c->green = a->green * b->green;
		c->blue = a->blue * b->blue;
		return c;
	}
	return nullptr;
}

#ifdef __cplusplus
}
#endif

#endif
