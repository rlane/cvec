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
 *
 * Angles are specified in radians. Rotation matrices produced by
 * mat*_init_rotate() are right-handed.
 *
 * The mat4 translate/rotate/scale functions are intended to be used with
 * homogeneous coordinates.
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

typedef struct vec4 {
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef struct mat2 {
    float data[4];
} mat2;

typedef struct mat3 {
    float data[9];
} mat3;

typedef struct mat4 {
    float data[16];
} mat4;


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


/* vec4 functions */

static inline vec4 Vec4(float x, float y, float z, float w)
{
    vec4 r;
    r.x = x;
    r.y = y;
    r.z = z;
    r.w = w;
    return r;
}

static inline vec4 vec4_add(vec4 a, vec4 b)
{
    return Vec4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
}

static inline vec4 vec4_sub(vec4 a, vec4 b)
{
    return Vec4(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
}

static inline vec4 vec4_scale(vec4 a, float c)
{
    return Vec4(a.x*c, a.y*c, a.z*c, a.w*c);
}

static inline float vec4_dot(vec4 a, vec4 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

static inline float vec4_length(vec4 a)
{
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w);
}

static inline float vec4_distance(vec4 a, vec4 b)
{
    return vec4_length(vec4_sub(a, b));
}

static inline vec4 vec4_normalize(vec4 a)
{
    float len = vec4_length(a);
    return Vec4(a.x/len, a.y/len, a.z/len, a.w/len);
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

static inline vec2 mat2_row(const mat2 *a, int i)
{
    return Vec2(mat2_get(a, i, 0), mat2_get(a, i, 1));
}

static inline vec2 mat2_col(const mat2 *a, int j)
{
    return Vec2(mat2_get(a, 0, j), mat2_get(a, 1, j));
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

static inline void mat2_init_rotate(mat2 *a, float angle)
{
    mat2_init(a, cos(angle), -sin(angle),
                 sin(angle), cos(angle));
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


/* mat3 functions */

static inline float mat3_get(const mat3 *a, int i, int j)
{
    return mat_get(a->data, i, j, 3);
}

static inline void mat3_set(mat3 *a, int i, int j, float value)
{
    mat_set(a->data, i, j, value, 3);
}

static inline vec3 mat3_row(const mat3 *a, int i)
{
    return Vec3(mat3_get(a, i, 0), mat3_get(a, i, 1), mat3_get(a, i, 2));
}

static inline vec3 mat3_col(const mat3 *a, int j)
{
    return Vec3(mat3_get(a, 0, j), mat3_get(a, 1, j), mat3_get(a, 2, j));
}

static inline void mat3_init(mat3 *a, float v00, float v01, float v02,
                                      float v10, float v11, float v12,
                                      float v20, float v21, float v22)
{
    mat3_set(a, 0, 0, v00);
    mat3_set(a, 0, 1, v01);
    mat3_set(a, 0, 2, v02);
    mat3_set(a, 1, 0, v10);
    mat3_set(a, 1, 1, v11);
    mat3_set(a, 1, 2, v12);
    mat3_set(a, 2, 0, v20);
    mat3_set(a, 2, 1, v21);
    mat3_set(a, 2, 2, v22);
}

static inline void mat3_init_zero(mat3 *a)
{
    mat_init_zero(a->data, 3);
}

static inline void mat3_init_identity(mat3 *a)
{
    mat_init_identity(a->data, 3);
}

static inline void mat3_init_scale(mat3 *a, float value)
{
    mat_init_scale(a->data, value, 3);
}

static inline void mat3_init_rotate(mat3 *a, vec3 axis, float angle)
{
    if (vec3_length(axis) == 0) {
        mat3_init_identity(a);
        return;
    }

    axis = vec3_normalize(axis);

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float s = sinf(angle);
    float c = cosf(angle);
    float t = 1.0f - c;

    mat3_init(a, t*x*x + c,   t*y*x - s*z, t*z*x + s*y,
                 t*x*y + s*z, t*y*y + c,   t*z*y - s*x,
                 t*x*z - s*y, t*y*z + s*x, t*z*z + c);
}

static inline void mat3_transpose(mat3 *a)
{
    mat_transpose(a->data, 3);
}

static inline vec3 mat3_transform(const mat3 *m, vec3 v)
{
    vec3 r;
    mat_transform(m->data, (float *)&v, (float *)&r, 3);
    return r;
}

static inline void mat3_mult(const mat3 *a, const mat3 *b, mat3 *r)
{
    mat_mult(a->data, b->data, r->data, 3);
}


/* mat4 functions */

static inline float mat4_get(const mat4 *a, int i, int j)
{
    return mat_get(a->data, i, j, 4);
}

static inline void mat4_set(mat4 *a, int i, int j, float value)
{
    mat_set(a->data, i, j, value, 4);
}

static inline vec4 mat4_row(const mat4 *a, int i)
{
    return Vec4(mat4_get(a, i, 0), mat4_get(a, i, 1), mat4_get(a, i, 2), mat4_get(a, i, 3));
}

static inline vec4 mat4_col(const mat4 *a, int j)
{
    return Vec4(mat4_get(a, 0, j), mat4_get(a, 1, j), mat4_get(a, 2, j), mat4_get(a, 3, j));
}

static inline void mat4_init(mat4 *a, float v00, float v01, float v02, float v03,
                                      float v10, float v11, float v12, float v13,
                                      float v20, float v21, float v22, float v23,
                                      float v30, float v31, float v32, float v33)
{
    mat4_set(a, 0, 0, v00);
    mat4_set(a, 0, 1, v01);
    mat4_set(a, 0, 2, v02);
    mat4_set(a, 0, 3, v03);
    mat4_set(a, 1, 0, v10);
    mat4_set(a, 1, 1, v11);
    mat4_set(a, 1, 2, v12);
    mat4_set(a, 1, 3, v13);
    mat4_set(a, 2, 0, v20);
    mat4_set(a, 2, 1, v21);
    mat4_set(a, 2, 2, v22);
    mat4_set(a, 2, 3, v23);
    mat4_set(a, 3, 0, v30);
    mat4_set(a, 3, 1, v31);
    mat4_set(a, 3, 2, v32);
    mat4_set(a, 3, 3, v33);
}

static inline void mat4_init_zero(mat4 *a)
{
    mat_init_zero(a->data, 4);
}

static inline void mat4_init_identity(mat4 *a)
{
    mat_init_identity(a->data, 4);
}

static inline void mat4_init_scale(mat4 *a, float value)
{
    mat_init_scale(a->data, value, 4);
    mat4_set(a, 3, 3, 1);
}

/* Only supports rotation in 3 dimensions, not 4. */
static inline void mat4_init_rotate(mat4 *a, vec3 axis, float angle)
{
    if (vec3_length(axis) == 0) {
        mat4_init_identity(a);
        return;
    }

    axis = vec3_normalize(axis);

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float s = sinf(angle);
    float c = cosf(angle);
    float t = 1.0f - c;

    mat4_init(a, t*x*x + c,   t*y*x - s*z, t*z*x + s*y, 0,
                 t*x*y + s*z, t*y*y + c,   t*z*y - s*x, 0,
                 t*x*z - s*y, t*y*z + s*x, t*z*z + c,   0,
                 0,           0,           0,           1);
}

static inline void mat4_init_translate(mat4 *m, vec3 v)
{
    mat4_init(m, 1, 0, 0, v.x,
                 0, 1, 0, v.y,
                 0, 0, 1, v.z,
                 0, 0, 0, 1);
}

static inline void mat4_transpose(mat4 *a)
{
    mat_transpose(a->data, 4);
}

static inline vec4 mat4_transform(const mat4 *m, vec4 v)
{
    vec4 r;
    mat_transform(m->data, (float *)&v, (float *)&r, 4);
    return r;
}

static inline void mat4_mult(const mat4 *a, const mat4 *b, mat4 *r)
{
    mat_mult(a->data, b->data, r->data, 4);
}

#endif
