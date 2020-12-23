#include "yasl/yasl.h"
#include "yasl/yasl_aux.h"

#include "complex.h"

#include <stdio.h>

// TODO: fix this
#define T_COMPLEX 500
#define COMPLEX_PRE "complex"

static complex yasl_float *YASLX_checkcomplex(struct YASL_State *S, const char *name, int pos) {
	if (!YASL_isuserdata(S, T_COMPLEX)) {
        YASL_print_err(S, "TypeError: %s expected arg in position %d to be of type complex, got arg of type %s.",
				  name, pos, YASL_peektypestr(S));
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
    YASL_pushuserdata(S, allocate_complex(c), T_COMPLEX, free);
    YASL_loadmt(S, COMPLEX_PRE);
    YASL_setmt(S);
}

static void YASL_complex_new(struct YASL_State *S) {
    yasl_float real = YASLX_checkfloat(S, "complex", 0);
    yasl_float imag = YASLX_checkfloat(S, "complex", 1);

    YASL_pushcomplex(S, real + image * I);
}

void YASL_complex_tostr(struct YASL_State *S) {
    complex yasl_float c = *YASLX_checkcomplex(S, "complex.tostr", 0);
    yasl_float real = creal(c);
    yasl_float imag = cimag(c);

    size_t len = snprintf(NULL, 0, "%f + %fi", real, imag);
    char *buffer = malloc(len + 1);
    snprintf(buffer, len, "%f + %fi", real, imag);
    buffer[len] = '\0';

    YASL_pushszstring(S, buffer);
}


void YASL_complex___add(struct YASL_State *S) {
    complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
    complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

    YASL_pushcomplex(S, a + b);
}

void YASL_complex___sub(struct YASL_State *S) {
    complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
    complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

    YASL_pushcomplex(S, a - b);
}

void YASL_complex___mul(struct YASL_State *S) {
    complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
    complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

    YASL_pushcomplex(S, a * b);
}

void YASL_complex___div(struct YASL_State *S) {
    complex yasl_float b = *YASLX_checkcomplex(S, "complex.__add", 1);
    complex yasl_float a = *YASLX_checkcomplex(S, "complex.__add", 0);

    YASL_pushcomplex(S, a / b);
}

/*
void YASL_complex___eq(struct YASL_State *S) {

}

void YASL_complex___gt(struct YASL_State *S) {

}

void YASL_complex___ge(struct YASL_State *S) {

}

void YASL_complex___lt(struct YASL_State *S) {

}

void YASL_complex___le(struct YASL_State *S) {

}
*/

void YASL_load_dyn_lib(struct YASL_State *S) {
    YASL_pushtable(S);
    YASL_registermt(S, COMPLEX_PRE);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "tostr");
    YASL_pushcfunction(S, YASL_complex_tostr, 1);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__add");
    YASL_pushcfunction(S, YASL_complex___add, 2);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__sub");
    YASL_pushcfunction(S, YASL_complex___sub, 2);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__mul");
    YASL_pushcfunction(S, YASL_complex___mul, 2);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__div");
    YASL_pushcfunction(S, YASL_complex___div, 2);
    YASL_tableset(S);

/*
    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__eq");
    YASL_pushcfunction(S, YASL_complex___eq, 2);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__gt");
    YASL_pushcfunction(S, YASL_complex___gt, 2);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__ge");
    YASL_pushcfunction(S, YASL_complex___ge, 2);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__lt");
    YASL_pushcfunction(S, YASL_complex___lt, 2);
    YASL_tableset(S);

    YASL_loadmt(S, COMPLEX_PRE);
    YASL_pushlitszstring(S, "__le");
    YASL_pushcfunction(S, YASL_complex___le, 2);
    YASL_tableset(S);

    */
    YASL_pushcfunction(S, YASL_complex_new, 2);
}
