#include "cvec.h"
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const double epsilon = 1.0e-3;

#define assert_equal(_expected, _value) \
    do { \
        double expected = (_expected); \
        double value = (_value); \
        if (fabs(expected - value) > epsilon) { \
            fprintf(stderr, "%s:%d expected %g, got %g\n", __FILE__, __LINE__, expected, value); \
            abort(); \
        } \
    } while (0)

static void test_vec2(void)
{
    {
        vec2 a = { 1, 2 };
        vec2 b = { 3, 4 };
        vec2 r = vec2_add(a, b);
        assert_equal(4, r.x);
        assert_equal(6, r.y);
    }

    {
        vec2 r = vec2_add(Vec2(1, 2), Vec2(3, 4));
        assert_equal(4, r.x);
        assert_equal(6, r.y);
    }

    {
        vec2 a = { 1, 2 };
        vec2 b = { 3, 4 };
        vec2 c = { 5, 6 };
        vec2 r = vec2_add(vec2_add(a, b), c);
        assert_equal(9, r.x);
        assert_equal(12, r.y);
    }

    {
        vec2 a = { 1, 2 };
        vec2 b = { 3, -4 };
        vec2 r = vec2_sub(a, b);
        assert_equal(-2, r.x);
        assert_equal(6, r.y);
    }

    {
        vec2 a = { 1, 2 };
        vec2 r = vec2_scale(a, 2);
        assert_equal(2, r.x);
        assert_equal(4, r.y);
    }

    {
        vec2 a = { 1, 2 };
        vec2 b = { 3, 4 };
        float r = vec2_dot(a, b);
        assert_equal(11, r);
    }

    {
        vec2 a = { 3, 4 };
        float r = vec2_length(a);
        assert_equal(5, r);
    }

    {
        vec2 a = { 1, 1 };
        vec2 b = { 4, 5 };
        float r = vec2_distance(a, b);
        assert_equal(5, r);
    }

    {
        vec2 a = { 3, 4 };
        vec2 r = vec2_normalize(a);
        assert_equal(0.6, r.x);
        assert_equal(0.8, r.y);
    }
}

static void test_mat2(void)
{
    {
        mat2 a[1];
        mat2_init_zero(a);
        assert_equal(0, mat2_get(a, 0, 0));
        assert_equal(0, mat2_get(a, 0, 1));
        assert_equal(0, mat2_get(a, 1, 0));
        assert_equal(0, mat2_get(a, 1, 1));
    }

    {
        mat2 a[1];
        mat2_init_identity(a);
        assert_equal(1, mat2_get(a, 0, 0));
        assert_equal(0, mat2_get(a, 0, 1));
        assert_equal(0, mat2_get(a, 1, 0));
        assert_equal(1, mat2_get(a, 1, 1));
    }

    {
        mat2 a[1];
        mat2_init_scale(a, 2);
        assert_equal(2, mat2_get(a, 0, 0));
        assert_equal(0, mat2_get(a, 0, 1));
        assert_equal(0, mat2_get(a, 1, 0));
        assert_equal(2, mat2_get(a, 1, 1));
    }

    {
        mat2 a[1];
        mat2_init_zero(a);
        mat2_set(a, 1, 0, 1);
        assert_equal(0, mat2_get(a, 0, 1));
        mat2_transpose(a);
        assert_equal(0, mat2_get(a, 1, 0));
        assert_equal(1, mat2_get(a, 0, 1));
    }

    {
        mat2 a[1];
        vec2 r;
        mat2_init_identity(a);
        r = mat2_transform(a, Vec2(2, 3));
        assert_equal(2, r.x);
        assert_equal(3, r.y);
    }

    {
        mat2 a[1];
        vec2 r;
        mat2_init(a, 5, 6,
                     7, 8);
        r = mat2_transform(a, Vec2(2, 3));
        assert_equal(2*5 + 3*6, r.x);
        assert_equal(2*7 + 3*8, r.y);
    }

    {
        mat2 a[1], b[1], r[1];
        mat2_init_identity(a);
        mat2_init_identity(b);
        mat2_mult(a, b, r);
        assert_equal(1, mat2_get(r, 0, 0));
        assert_equal(0, mat2_get(r, 0, 1));
        assert_equal(0, mat2_get(r, 1, 0));
        assert_equal(1, mat2_get(r, 1, 1));
    }

    {
        mat2 a[1], b[1], r[1];
        mat2_init(a, 1, 2,
                     3, 4);
        mat2_init(b, 5, 6,
                     7, 8);
        mat2_mult(a, b, r);
        assert_equal(1*5 + 2*7, mat2_get(r, 0, 0));
        assert_equal(1*6 + 2*8, mat2_get(r, 0, 1));
        assert_equal(3*5 + 4*7, mat2_get(r, 1, 0));
        assert_equal(3*6 + 4*8, mat2_get(r, 1, 1));
    }

    {
        mat2 a[1];
        vec2 r;
        mat2_init_rotate(a, M_PI/2);
        r = mat2_transform(a, Vec2(2, 3));
        assert_equal(-3, r.x);
        assert_equal(2, r.y);
    }
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    test_vec2();
    test_mat2();
    return 0;
}
