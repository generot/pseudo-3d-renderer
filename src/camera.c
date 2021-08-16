#include "../include/camera.h"

camera make_camera(int fov, int ray_n, float raylen, point *pos, int *offset_ang, ray_handler rfunc) {
    camera new_cam = {0};

    new_cam.fov = fov == USE_DEF ? DEF_FOV : fov;
    new_cam.ray_amount = ray_n == USE_DEF ? DEF_RAY_NUM : ray_n;
    new_cam.raylen = raylen;

    new_cam.pos = pos;
    new_cam.offset_angle = offset_ang;

    new_cam.rfunc = rfunc;

    return new_cam;
}

void update_camera(camera *cam, map mp, SDL_Renderer *rnd) {
    float angle_inc = (float)cam->fov / (float)cam->ray_amount;
    int ray_ix = 0;

    for(float ang = (float)cam->fov + (float)*cam->offset_angle; 
        ang >= (float)*cam->offset_angle; 
        ang -= angle_inc) 
    {
        line ray = line_from_angle(*cam->pos, ang, cam->raylen);
        cam->rfunc(rnd, ray, mp, *cam->pos, ray_ix, ang);

        ray_ix++;
    }
}

distance get_closest_intr_pt(line ray, map mp, point pos) {
    point closest_point = { .is_valid = 0 };
    float least_dist = mp.map_size.x + mp.map_size.y;

    for(size_t i = 0; i < mp.num_of_walls; i++) {
        point intrs = intersection(ray, mp.walls[i], INTR_FIRST_LSEG | INTR_SECOND_LSEG);

        if(intrs.x == -1 && intrs.y == -1)
            continue;

        float dist_to_player = dist_sq(intrs, pos);

        if(dist_to_player < least_dist) {
            closest_point = intrs;
            least_dist = dist_to_player;
        }
    }

    return (distance){ closest_point, sqrt(least_dist) };
}

void translate(point *p, point screen_dm, int inc, double direction_angle) {
    if(-screen_dm.y / 2 < p->y + inc && p->y + inc < screen_dm.y / 2) {
        p->x += cosf(RAD(direction_angle)) * SPEED * (float)inc;
        p->y += sinf(RAD(direction_angle)) * SPEED * (float)inc;
    }

    //SDL_Log("P(%.2f, %.2f)\r", p->x, p->y);
}