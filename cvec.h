/* 
 * Copyright (c) 2013 Rich Lane
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef CVEC_H
#define CVEC_H

/*
 * Vectors are passed and returned by value while matrices are passed by
 * reference.
 *
 * Matrices are stored in column-major order. The parameters i, j used in
 * matrix functions have their normal meanings: row i and column j.
 */

#include <math.h>

#ifndef M_PI
/* C99 removed M_PI */
#define M_PI 3.14159265358979323846264338327
#endif

/* types */

typedef struct vec2 {
    float x;
    float y;
} vec2;

typedef struct vec3 {
    float x;
    float y;
    float z;
} vec3;

typedef struct mat2 {
    float data[4];
} mat2;


/* vec2 functions */

static inline vec2 Vec2(float x, float y)
{
    vec2 r;
    r.x = x;
    r.y = y;
    return r;
}

static inline vec2 vec2_add(vec2 a, vec2 b)
{
    return Vec2(a.x+b.x, a.y+b.y);
}

static inline vec2 vec2_sub(vec2 a, vec2 b)
{
    return Vec2(a.x-b.x, a.y-b.y);
}

static inline vec2 vec2_scale(vec2 a, float c)
{
    return Vec2(a.x*c, a.y*c);
}

static inline float vec2_dot(vec2 a, vec2 b)
{
    return a.x*b.x + a.y*b.y;
}

static inline float vec2_length(vec2 a)
{
    return sqrtf(a.x*a.x + a.y*a.y);
}

static inline float vec2_distance(vec2 a, vec2 b)
{
    return vec2_length(vec2_sub(a, b));
}

static inline vec2 vec2_normalize(vec2 a)
{
    float len = vec2_length(a);
    return Vec2(a.x/len, a.y/len);
}


/* vec3 functions */

static inline vec3 Vec3(float x, float y, float z)
{
    vec3 r;
    r.x = x;
    r.y = y;
    r.z = z;
    return r;
}

static inline vec3 vec3_add(vec3 a, vec3 b)
{
    return Vec3(a.x+b.x, a.y+b.y, a.z+b.z);
}

static inline vec3 vec3_sub(vec3 a, vec3 b)
{
    return Vec3(a.x-b.x, a.y-b.y, a.z-b.z);
}

static inline vec3 vec3_scale(vec3 a, float c)
{
    return Vec3(a.x*c, a.y*c, a.z*c);
}

static inline float vec3_dot(vec3 a, vec3 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

static inline float vec3_length(vec3 a)
{
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}

static inline float vec3_distance(vec3 a, vec3 b)
{
    return vec3_length(vec3_sub(a, b));
}

static inline vec3 vec3_normalize(vec3 a)
{
    float len = vec3_length(a);
    return Vec3(a.x/len, a.y/len, a.z/len);
}


/* 
 * Generic (square) matrix functions
 *
 * The compiler is expected to inline these into the caller and
 * optimize away the generic loops. Once the library is stable
 * we could inline and optimize them by hand to save the
 * compiler some work.
 */


static inline float mat_get(const float *a, int i, int j, int n)
{
    return a[i + n*j];
}

static inline void mat_set(float *a, int i, int j, float value, int n)
{
    a[i + n*j] = value;
}

static inline void mat_init_zero(float *a, int n)
{
    int i;
    for (i = 0; i < n*n; i++) {
        a[i] = 0.0f;
    }
}

static inline void mat_init_identity(float *a, int n)
{
    int i, j;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            float value = i == j ? 1.0f : 0.0f;
            mat_set(a, i, j, value, n);
        }
    }
}

static inline void mat_init_scale(float *a, float value, int n)
{
    int i, j;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            float _value = i == j ? value : 0.0f;
            mat_set(a, i, j, _value, n);
        }
    }
}

static inline void mat_transpose(float *a, int n)
{
    int i, j;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            if (i < j) {
                float value1 = mat_get(a, i, j, n);
                float value2 = mat_get(a, j, i, n);
                mat_set(a, i, j, value2, n);
                mat_set(a, j, i, value1, n);
            }
        }
    }
}

static inline void mat_transform(const float *m, const float *v, float *r, int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        float sum = 0.0f;
        for (j = 0; j < n; j++) {
            sum += v[j] * mat_get(m, i, j, n);
        }
        r[i] = sum;
    }
}

static inline void mat_mult(const float *a, const float *b, float *r, int n)
{
    int i, j, k;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            float sum = 0.0f;
            for (k = 0; k < n; k++) {
                sum += mat_get(a, i, k, n) * mat_get(b, k, j, n);
            }
            mat_set(r, i, j, sum, n);
        }
    }
}


/* mat2 functions */

static inline float mat2_get(const mat2 *a, int i, int j)
{
    return mat_get(a->data, i, j, 2);
}

static inline void mat2_set(mat2 *a, int i, int j, float value)
{
    mat_set(a->data, i, j, value, 2);
}

static inline void mat2_init(mat2 *a, float v00, float v01, float v10, float v11)
{
    mat2_set(a, 0, 0, v00);
    mat2_set(a, 0, 1, v01);
    mat2_set(a, 1, 0, v10);
    mat2_set(a, 1, 1, v11);
}

static inline void mat2_init_zero(mat2 *a)
{
    mat_init_zero(a->data, 2);
}

static inline void mat2_init_identity(mat2 *a)
{
    mat_init_identity(a->data, 2);
}

static inline void mat2_init_scale(mat2 *a, float value)
{
    mat_init_scale(a->data, value, 2);
}

static inline void mat2_init_rotate(mat2 *a, float radians)
{
    mat2_init(a, cos(radians), -sin(radians),
                 sin(radians), cos(radians));
}

static inline void mat2_transpose(mat2 *a)
{
    mat_transpose(a->data, 2);
}

static inline vec2 mat2_transform(const mat2 *m, vec2 v)
{
    vec2 r;
    mat_transform(m->data, (float *)&v, (float *)&r, 2);
    return r;
}

static inline void mat2_mult(const mat2 *a, const mat2 *b, mat2 *r)
{
    mat_mult(a->data, b->data, r->data, 2);
}

#endif
