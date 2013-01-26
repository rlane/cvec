#ifndef CVEC_H
#define CVEC_H

#include <math.h>

/* types */

typedef struct vec2 {
    float x;
    float y;
} vec2;


/* vec2 functions */

static inline vec2 Vec2(float x, float y)
{
    vec2 r = { x, y };
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

#endif
