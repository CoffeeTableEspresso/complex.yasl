#include "yasl/yasl.h"
#include "yasl/yasl_aux.h"

#include "complex.h"

#include <stdio.h>

#define COMPLEX_PRE "complex"

static const char *COMPLEX_NAME = "complex";

static complex yasl_float *YASLX_checkcomplex(struct YASL_State *S, const char *name, int pos) {
	if (!YASL_isuserdata(S, COMPLEX_NAME)) {
        YASL_print_err(S, "TypeError: %s expected arg in position %d to be of type complex, got arg of type %s.",
				  name, pos, YASL_peektypename(S));
		YASL_throw_err(S, YASL_TYPE_ERROR);
	}
	return (complex yasl_float *)YASL_popuserdata(S);
}

static complex yasl_float *allocate_complex(complex yasl_float c) {
    complex yasl_float *ptr = malloc(sizeof(complex yasl_float));
    *ptr = c;
    return ptr;
}

static void YASL_pushcomplex(struct YASL_State *S, complex yasl_float c) {
    YASL_pushuserdata(S, allocate_complex(c), COMPLEX_NAME, free);
    YASL_loadmt(S, COMPLEX_PRE);
    YASL_setmt(S);
}

static int YASL_complex_new(struct YASL_State *S) {
    yasl_float imag = YASLX_checknfloat(S, "complex", 1);
    yasl_float real = YASLX_checknfloat(S, "complex", 0);

    YASL_pushcomplex(S, real + imag * I);

    return 1;
}

static int YASL_complex_tostr(struct YASL_State *S) {
    complex yasl_float c = *YASLX_checkcomplex(S, "complex.tostr", 0);
    yasl_float real = creal(c);
    yasl_float imag = cimag(c);

    size_t len = snprintf(NULL, 0, "%f + %fi", real, imag);
    char *buffer = malloc(len + 1);
    snprintf(buffer, len + 1, "%f + %fi", real, imag);
    buffer[len] = '\0';

    YASL_pushzstr(S, buffer);

    return 1;
}

static int YASL_complex___pos(struct YASL_State *S) {
	complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);

	YASL_pushcomplex(S, b);
	return 1;
}

static int YASL_complex___neg(struct YASL_State *S) {
	complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);

	YASL_pushcomplex(S, -b);
	return 1;
}

static int YASL_complex___add(struct YASL_State *S) {
    complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
    complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

    YASL_pushcomplex(S, a + b);

    return 1;
}

static int YASL_complex___sub(struct YASL_State *S) {
    complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
    complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

    YASL_pushcomplex(S, a - b);

    return 1;
}

static int YASL_complex___mul(struct YASL_State *S) {
    complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
    complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

    YASL_pushcomplex(S, a * b);

    return 1;
}

static int YASL_complex___div(struct YASL_State *S) {
	complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
	complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

	if (b == 0) {
		YASL_print_err(S, "Cannot divide by 0");
		YASL_throw_err(S, YASL_DIVIDE_BY_ZERO_ERROR);
	}

	YASL_pushcomplex(S, a / b);

	return 1;
}

static int YASL_complex___eq(struct YASL_State *S) {
	complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
	complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

	YASL_pushbool(S, a == b);

	return 1;
}

static int YASL_complex_re(struct YASL_State *S) {
	complex yasl_float a = *YASLX_checkcomplex(S, "complex.re", 0);

	YASL_pushfloat(S, creal(a));
	return 1;
}

static int YASL_complex_im(struct YASL_State *S) {
	complex yasl_float a = *YASLX_checkcomplex(S, "complex.im", 0);

	YASL_pushfloat(S, cimag(a));
	return 1;
}

int YASL_load_dyn_lib(struct YASL_State *S) {
	YASL_pushtable(S);
	YASL_registermt(S, COMPLEX_PRE);

	YASL_loadmt(S, COMPLEX_PRE);

	YASL_pushlit(S, "tostr");
	YASL_pushcfunction(S, YASL_complex_tostr, 1);
	YASL_tableset(S);

	YASL_pushlit(S, "__pos");
	YASL_pushcfunction(S, YASL_complex___pos, 1);
	YASL_tableset(S);

	YASL_pushlit(S, "__neg");
	YASL_pushcfunction(S, YASL_complex___neg, 1);
	YASL_tableset(S);

	YASL_pushlit(S, "__add");
	YASL_pushcfunction(S, YASL_complex___add, 2);
	YASL_tableset(S);

	YASL_pushlit(S, "__sub");
	YASL_pushcfunction(S, YASL_complex___sub, 2);
	YASL_tableset(S);

	YASL_pushlit(S, "__mul");
	YASL_pushcfunction(S, YASL_complex___mul, 2);
	YASL_tableset(S);

	YASL_pushlit(S, "__div");
	YASL_pushcfunction(S, YASL_complex___div, 2);
	YASL_tableset(S);

	YASL_pushlit(S, "__eq");
	YASL_pushcfunction(S, YASL_complex___eq, 2);
	YASL_tableset(S);

	YASL_pushlit(S, "re");
	YASL_pushcfunction(S, YASL_complex_re, 1);
	YASL_tableset(S);

	YASL_pushlit(S, "im");
	YASL_pushcfunction(S, YASL_complex_im, 1);
	YASL_tableset(S);

	YASL_pushtable(S);

	YASL_pushlit(S, "__VERSION__");
	YASL_pushlit(S, "v0.1.0");
	YASL_tableset(S);

	YASL_pushtable(S);
	YASL_pushlit(S, "__call");
	YASL_pushcfunction(S, YASL_complex_new, 2);
	YASL_tableset(S);

	YASL_setmt(S);

	return 1;
}
