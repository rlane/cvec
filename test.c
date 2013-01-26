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

int main(int argc, char **argv)
{
    test_vec2();
    return 0;
}
