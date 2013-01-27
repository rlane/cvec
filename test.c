#include "cvec.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cvec_asserts.h"

static void test_vec2(void)
{
    {
        vec2 a = { 1, 2 };
        vec2 b = { 3, 4 };
        vec2 r = vec2_add(a, b);
        assert_vec2_equal(Vec2(4, 6), r);
    }

    {
        vec2 r = vec2_add(Vec2(1, 2), Vec2(3, 4));
        assert_vec2_equal(Vec2(4, 6), r);
    }

    {
        vec2 a = { 1, 2 };
        vec2 b = { 3, 4 };
        vec2 c = { 5, 6 };
        vec2 r = vec2_add(vec2_add(a, b), c);
        assert_vec2_equal(Vec2(9, 12), r);
    }

    {
        vec2 a = { 1, 2 };
        vec2 b = { 3, -4 };
        vec2 r = vec2_sub(a, b);
        assert_vec2_equal(Vec2(-2, 6), r);
    }

    {
        vec2 a = { 1, 2 };
        vec2 r = vec2_scale(a, 2);
        assert_vec2_equal(Vec2(2, 4), r);
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
        assert_vec2_equal(Vec2(0.6, 0.8), r);
    }
}

static void test_vec3(void)
{
    {
        vec3 a = { 1, 2, 3 };
        vec3 b = { 4, 5, 6 };
        vec3 r = vec3_add(a, b);
        assert_equal(5, r.x);
        assert_equal(7, r.y);
        assert_equal(9, r.z);
    }

    {
        vec3 r = vec3_add(Vec3(1, 2, 3), Vec3(4, 5, 6));
        assert_equal(5, r.x);
        assert_equal(7, r.y);
        assert_equal(9, r.z);
    }

    {
        vec3 a = { 1, 2, 3 };
        vec3 b = { 4, 5, 6 };
        vec3 c = { 7, 8, 9 };
        vec3 r = vec3_add(vec3_add(a, b), c);
        assert_equal(12, r.x);
        assert_equal(15, r.y);
        assert_equal(18, r.z);
    }

    {
        vec3 a = { 1, 2, 3 };
        vec3 b = { 4, -5, 6 };
        vec3 r = vec3_sub(a, b);
        assert_equal(-3, r.x);
        assert_equal(7, r.y);
        assert_equal(-3, r.z);
    }

    {
        vec3 a = { 1, 2, 3 };
        vec3 r = vec3_scale(a, 2);
        assert_equal(2, r.x);
        assert_equal(4, r.y);
        assert_equal(6, r.z);
    }

    {
        vec3 a = { 1, 2, 3 };
        vec3 b = { 4, 5, 6 };
        float r = vec3_dot(a, b);
        assert_equal(32, r);
    }

    {
        vec3 a = { 3, 4, 5 };
        float r = vec3_length(a);
        assert_equal(sqrt(50), r);
    }

    {
        vec3 a = { 1, 1, 1 };
        vec3 b = { 4, 5, 6 };
        float r = vec3_distance(a, b);
        assert_equal(sqrt(50), r);
    }

    {
        vec3 a = { 3, 4, 5 };
        vec3 r = vec3_normalize(a);
        assert_equal(3/sqrt(50), r.x);
        assert_equal(4/sqrt(50), r.y);
        assert_equal(5/sqrt(50), r.z);
    }
}

static void test_mat2(void)
{
    {
        mat2 a[1];
        mat2_init(a, 1, 2,
                     3, 4);
        assert_equal(1, mat2_get(a, 0, 0));
        assert_equal(2, mat2_get(a, 0, 1));
        assert_equal(3, mat2_get(a, 1, 0));
        assert_equal(4, mat2_get(a, 1, 1));
        assert_vec2_equal(Vec2(1, 2), mat2_row(a, 0));
        assert_vec2_equal(Vec2(3, 4), mat2_row(a, 1));
        assert_vec2_equal(Vec2(1, 3), mat2_col(a, 0));
        assert_vec2_equal(Vec2(2, 4), mat2_col(a, 1));
    }

    {
        mat2 a[1], t[1];
        mat2_init_zero(a);
        mat2_init(t, 0, 0,
                     0, 0);
        assert_mat2_equal(t, a);
    }

    {
        mat2 a[1], t[1];
        mat2_init_identity(a);
        mat2_init(t, 1, 0,
                     0, 1);
        assert_mat2_equal(t, a);
    }

    {
        mat2 a[1], t[1];
        mat2_init_scale(a, 2);
        mat2_init(t, 2, 0,
                     0, 2);
        assert_mat2_equal(t, a);
    }

    {
        mat2 a[1], t[1];
        mat2_init(a, 1, 2,
                     3, 4);
        mat2_init(t, 1, 3,
                     2, 4);
        mat2_transpose(a);
        assert_mat2_equal(t, a);
    }

    {
        mat2 a[1];
        vec2 r;
        mat2_init_identity(a);
        r = mat2_transform(a, Vec2(2, 3));
        assert_vec2_equal(Vec2(2, 3), r);
    }

    {
        mat2 a[1];
        vec2 r;
        mat2_init(a, 5, 6,
                     7, 8);
        r = mat2_transform(a, Vec2(2, 3));
        assert_vec2_equal(Vec2(2*5 + 3*6, 2*7 + 3*8), r);
    }

    {
        mat2 a[1], b[1], r[1], t[1];
        mat2_init_identity(a);
        mat2_init_identity(b);
        mat2_init_identity(t);
        mat2_mult(a, b, r);
        assert_mat2_equal(t, r);
    }

    {
        mat2 a[1], b[1], r[1], t[1];
        mat2_init(a, 1, 2,
                     3, 4);
        mat2_init(b, 5, 6,
                     7, 8);
        mat2_init(t, 1*5 + 2*7, 1*6 + 2*8,
                     3*5 + 4*7, 3*6 + 4*8);
        mat2_mult(a, b, r);
        assert_mat2_equal(t, r);
    }

    {
        mat2 a[1];
        vec2 r;
        mat2_init_rotate(a, M_PI/2);
        r = mat2_transform(a, Vec2(2, 3));
        assert_vec2_equal(Vec2(-3, 2), r);
    }
}

static void test_mat3(void)
{
    {
        mat3 a[1];
        mat3_init(a, 1, 2, 3,
                     4, 5, 6,
                     7, 8, 9);
        assert_equal(1, mat3_get(a, 0, 0));
        assert_equal(2, mat3_get(a, 0, 1));
        assert_equal(3, mat3_get(a, 0, 2));
        assert_equal(4, mat3_get(a, 1, 0));
        assert_equal(5, mat3_get(a, 1, 1));
        assert_equal(6, mat3_get(a, 1, 2));
        assert_equal(7, mat3_get(a, 2, 0));
        assert_equal(8, mat3_get(a, 2, 1));
        assert_equal(9, mat3_get(a, 2, 2));
        assert_vec3_equal(Vec3(1, 2, 3), mat3_row(a, 0));
        assert_vec3_equal(Vec3(4, 5, 6), mat3_row(a, 1));
        assert_vec3_equal(Vec3(7, 8, 9), mat3_row(a, 2));
        assert_vec3_equal(Vec3(1, 4, 7), mat3_col(a, 0));
        assert_vec3_equal(Vec3(2, 5, 8), mat3_col(a, 1));
        assert_vec3_equal(Vec3(3, 6, 9), mat3_col(a, 2));
    }

    {
        mat3 a[1], t[1];
        mat3_init_zero(a);
        mat3_init(t, 0, 0, 0,
                     0, 0, 0,
                     0, 0, 0);
        assert_mat3_equal(t, a);
    }

    {
        mat3 a[1], t[1];
        mat3_init_identity(a);
        mat3_init(t, 1, 0, 0,
                     0, 1, 0,
                     0, 0, 1);
        assert_mat3_equal(t, a);
    }

    {
        mat3 a[1], t[1];
        mat3_init_scale(a, 2);
        mat3_init(t, 2, 0, 0,
                     0, 2, 0,
                     0, 0, 2);
        assert_mat3_equal(t, a);
    }

    {
        mat3 a[1], t[1];
        mat3_init(a, 1, 2, 3,
                     4, 5, 6,
                     7, 8, 9);
        mat3_init(t, 1, 4, 7,
                     2, 5, 8,
                     3, 6, 9);
        mat3_transpose(a);
        assert_mat3_equal(t, a);
    }

    {
        mat3 a[1];
        vec3 r;
        mat3_init_identity(a);
        r = mat3_transform(a, Vec3(2, 3, 4));
        assert_vec3_equal(Vec3(2, 3, 4), r);
    }

    {
        mat3 a[1];
        vec3 r;
        mat3_init(a,  5,  6,  7,
                      8,  9, 10,
                     11, 12, 13);
        r = mat3_transform(a, Vec3(2, 3, 4));
        assert_vec3_equal(Vec3(2*5 + 3*6 + 4*7,
                               2*8 + 3*9 + 4*10,
                               2*11 + 3*12 + 4*13), r);
    }

    {
        mat3 a[1], b[1], r[1], t[1];
        mat3_init_identity(a);
        mat3_init_identity(b);
        mat3_init_identity(t);
        mat3_mult(a, b, r);
        assert_mat3_equal(t, r);
    }

    {
        mat3 a[1], b[1], r[1], t[1];
        mat3_init(a, 1, 2, 3,
                     4, 5, 6,
                     7, 8, 9);
        mat3_init(b, 10, 11, 12,
                     13, 14, 15,
                     16, 17, 18);
        mat3_init(t,  84,  90,  96,
                     201, 216, 231,
                     318, 342, 366);
        mat3_mult(a, b, r);
        assert_mat3_equal(t, r);
    }

    {
        mat3 a[1], b[1], c[1], identity[1];
        mat3_init_rotate(a, Vec3(2, 3, 4), M_PI/6);

        assert_equal(1, vec3_length(mat3_row(a, 0)));
        assert_equal(1, vec3_length(mat3_row(a, 1)));
        assert_equal(1, vec3_length(mat3_row(a, 2)));
        assert_equal(1, vec3_length(mat3_col(a, 0)));
        assert_equal(1, vec3_length(mat3_col(a, 1)));
        assert_equal(1, vec3_length(mat3_col(a, 2)));

        assert_equal(0, vec3_dot(mat3_row(a, 0), mat3_row(a, 1)));
        assert_equal(0, vec3_dot(mat3_row(a, 0), mat3_row(a, 2)));
        assert_equal(0, vec3_dot(mat3_row(a, 1), mat3_row(a, 2)));
        assert_equal(0, vec3_dot(mat3_col(a, 0), mat3_col(a, 1)));
        assert_equal(0, vec3_dot(mat3_col(a, 0), mat3_col(a, 2)));
        assert_equal(0, vec3_dot(mat3_col(a, 1), mat3_col(a, 2)));

        mat3_init_rotate(b, Vec3(2, 3, 4), M_PI/6);
        mat3_init_identity(identity);
        mat3_transpose(b);
        mat3_mult(a, b, c);
        assert_mat3_equal(identity, c);
    }

    {
        mat3 a[1];
        vec3 r;
        mat3_init_rotate(a, Vec3(0, 0, 1), M_PI/2);
        r = mat3_transform(a, Vec3(2,3,4));
        assert_vec3_equal(Vec3(-3, 2, 4), r);
    }

    {
        mat3 a[1];
        vec3 r;
        mat3_init_rotate(a, Vec3(0, 1, 0), M_PI/2);
        r = mat3_transform(a, Vec3(2,3,4));
        assert_vec3_equal(Vec3(4, 3, -2), r);
    }

    {
        mat3 a[1];
        vec3 r;
        mat3_init_rotate(a, Vec3(1, 0, 0), M_PI/2);
        r = mat3_transform(a, Vec3(2,3,4));
        assert_vec3_equal(Vec3(2, -4, 3), r);
    }
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    test_vec2();
    test_vec3();
    test_mat2();
    test_mat3();
    return 0;
}
