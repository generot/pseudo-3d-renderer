#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <math.h>

#define G_PI 3.1415926f
#define RAD(x) ((x) * G_PI / 180)
#define SQ(x) ((x) * (x))

//FLAGS//
#define INTR_FIRST_LSEG  0x01
#define INTR_SECOND_LSEG 0x02

typedef struct {
    float x, y;
    int is_valid;
} point, vector;

typedef struct {
    point p1, p2;
} line;

line make_line(point p1, point p2);
line line_from_angle(point origin, float angle, float ray_len);

vector vector_sum(vector v1, vector v2);
vector vector_diff(vector v1, vector v2);

float vector_len_sq(vector v);
float vector_len(vector v);
float dist_sq(point p1, point p2);
float dist(point p1, point p2);

point intersection(line l1, line l2, int flags);

#endif //__GEOMETRY_H__