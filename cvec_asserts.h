#ifndef _TEST_H
#define _TEST_H

#include <math.h>
#include "cvec.h"

static const double epsilon = 1.0e-6;

static inline bool approx_equal(double a, double b)
{
    return fabs(a - b) <= epsilon;
}

#define assert_equal(_expected, _value) \
    do { \
        double expected = (_expected); \
        double value = (_value); \
        if (!approx_equal(expected, value)) { \
            fprintf(stderr, "%s:%d expected %g, got %g\n", __FILE__, __LINE__, expected, value); \
            abort(); \
        } \
    } while (0)

static inline void _assert_vec2_equal(vec2 expected, vec2 value, const char *file, int line)
{
    if (!approx_equal(expected.x, value.x) ||
        !approx_equal(expected.y, value.y)) {
        fprintf(stderr, "%s:%d expected (%g, %g), got (%g, %g)\n", file, line, expected.x, expected.y, value.x, value.y);
        abort();
    }
}

#define assert_vec2_equal(expected, value) _assert_vec2_equal(expected, value, __FILE__, __LINE__)

static inline void _assert_vec3_equal(vec3 expected, vec3 value, const char *file, int line)
{
    if (!approx_equal(expected.x, value.x) ||
        !approx_equal(expected.y, value.y) ||
        !approx_equal(expected.z, value.z)) {
        fprintf(stderr, "%s:%d expected (%g, %g, %g), got (%g, %g, %g)\n", file, line, expected.x, expected.y, expected.z, value.x, value.y, value.z);
        abort();
    }
}

#define assert_vec3_equal(expected, value) _assert_vec3_equal(expected, value, __FILE__, __LINE__)

static inline void _assert_vec4_equal(vec4 expected, vec4 value, const char *file, int line)
{
    if (!approx_equal(expected.x, value.x) ||
        !approx_equal(expected.y, value.y) ||
        !approx_equal(expected.z, value.z) ||
        !approx_equal(expected.w, value.w)) {
        fprintf(stderr, "%s:%d expected (%g, %g, %g, %g), got (%g, %g, %g, %g)\n", file, line, expected.x, expected.y, expected.z, expected.w, value.x, value.y, value.z, value.w);
        abort();
    }
}

#define assert_vec4_equal(expected, value) _assert_vec4_equal(expected, value, __FILE__, __LINE__)

static inline void _assert_mat2_equal(const mat2 *expected, const mat2 *value, const char *file, int line)
{
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            double e = mat2_get(expected, i, j);
            double v = mat2_get(value, i, j);
            if (!approx_equal(e, v)) {
                fprintf(stderr, "%s:%d expected %g, got %g at (%d, %d)\n", file, line, e, v, i, j);
                abort();
            }
        }
    }
}

#define assert_mat2_equal(expected, value) _assert_mat2_equal(expected, value, __FILE__, __LINE__)

static inline void _assert_mat3_equal(const mat3 *expected, const mat3 *value, const char *file, int line)
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            double e = mat3_get(expected, i, j);
            double v = mat3_get(value, i, j);
            if (!approx_equal(e, v)) {
                fprintf(stderr, "%s:%d expected %g, got %g at (%d, %d)\n", file, line, e, v, i, j);
                abort();
            }
        }
    }
}

#define assert_mat3_equal(expected, value) _assert_mat3_equal(expected, value, __FILE__, __LINE__)

#endif
