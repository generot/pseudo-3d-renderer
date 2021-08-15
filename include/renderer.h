#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"

#define MAX_WALLS 256
#define USE_DEF -1

#define DEF_WND_WIDTH 1200
#define DEF_WND_HEIGHT 800

#define ISSUE_ERROR(...) { \
    fprintf(stderr, __VA_ARGS__); \
    exit(-1); \
}

typedef struct _Map map;

struct _Map {
    point map_size, player_init_pos;
    line walls[MAX_WALLS];

    size_t num_of_walls;
};

map read_map(const char *filepath);
void print_map(map m);

#endif //__RENDERER_H__