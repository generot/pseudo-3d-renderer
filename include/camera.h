#ifndef __CAMERA_H__
#define __CAMERA_H__

#define DEF_FOV 120
#define DEF_RAY_NUM 800

#define X_AXIS 0
#define Y_AXIS 1

#define SPEED 0.4
#define TURN_SPEED 3

#include "renderer.h"

typedef void (*ray_handler)(SDL_Renderer*, line, map, point, int, float);

typedef struct {
    int fov;
    int ray_amount;
    float raylen;

    int *offset_angle;
    point *pos;

    ray_handler rfunc;
} camera;

typedef struct {
    point p;
    float ds;
} distance;

camera make_camera(int fov, int ray_n, float raylen, point *pos, int *offset_ang, ray_handler rfunc);
void update_camera(camera *cam, map mp, SDL_Renderer *rnd);

distance get_closest_intr_pt(line ray, map mp, point pos);
void translate(point *p, point screen_dm, int inc, double direction_angle);

#endif //__CAMERA_H__