#include "../include/geometry.h"

vector vector_sum(vector v1, vector v2) {
    return (vector){
        .x = v1.x + v2.x,
        .y = v1.y + v2.y
    };
}

vector vector_diff(vector v1, vector v2) {
    return (vector){
        .x = v1.x - v2.x,
        .y = v1.y - v2.y
    };
}

line make_line(point p1, point p2) {
    return (line){ 
        .p1 = p1, 
        .p2 = p2 
    };
}

line line_from_angle(point origin, float angle, float ray_len) {
    point angled_line = {
        .x = cosf(RAD(angle)) * ray_len,
        .y = sinf(RAD(angle)) * ray_len
    };

    angled_line = vector_sum(angled_line, origin);
    
    return make_line(origin, angled_line);
}

point intersection(line l1, line l2, int flags) {
    point pts[] = { l1.p1, l1.p2, l2.p1, l2.p2 };

    float dm = (pts[0].x - pts[1].x) * (pts[2].y - pts[3].y) - (pts[0].y - pts[1].y) * (pts[2].x - pts[3].x);

    float t = ((pts[0].x - pts[2].x) * (pts[2].y - pts[3].y) - (pts[0].y - pts[2].y) * (pts[2].x - pts[3].x)) / dm;
    float u = ((pts[1].x - pts[0].x) * (pts[0].y - pts[2].y) - (pts[1].y - pts[0].y) * (pts[0].x - pts[2].x)) / dm;

    int t_cmp = 0.0f <= t && t <= 1.0f;
    int u_cmp = 0.0f <= u && u <= 1.0f;

    point intrs_t = {
        .x = pts[0].x + t * (pts[1].x - pts[0].x),
        .y = pts[0].y + t * (pts[1].y - pts[0].y),
        .is_valid = 1
    };

    if(t_cmp && u_cmp) return intrs_t;

    return (point){ .is_valid = 0 };
}

float vector_len_sq(vector v) {
    return SQ(v.x) + SQ(v.y);
}

float vector_len(vector v) {
    return sqrtf(vector_len_sq(v));
}

float dist_sq(point p1, point p2) {
    vector resulting_vec = vector_diff(p1, p2);

    return vector_len_sq(resulting_vec);
}

float dist(point p1, point p2) {
    return sqrt(dist_sq(p1, p2));
}
