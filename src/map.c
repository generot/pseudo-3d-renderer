#include "../include/renderer.h"

map read_map(const char *filepath) {
    FILE *map_file = fopen(filepath, "r");

    map new_map = {0};
    line mobject = {0};

    fscanf(map_file, "%f %f", &new_map.map_size.x, &new_map.map_size.y);

    while(!feof(map_file)) {
        int is_player = 0;

        fscanf(map_file, "[%f|(%f %f)|(%f %f)]", 
                &is_player, 
                &mobject.p1.x, &mobject.p1.y, 
                &mobject.p2.x, &mobject.p2.y);

        if(is_player) new_map.player_init_pos = mobject.p1;   
        else new_map.walls[new_map.num_of_walls++] = mobject;

        mobject = (line){0};
    }

    new_map.num_of_walls--;
    fclose(map_file);

    return new_map;
}

void print_map(map m) {
    printf("%.2f %.2f\n", m.map_size.x, m.map_size.y);
    printf("Player: (%.2f, %.2f)\n", m.player_init_pos.x, m.player_init_pos.y);

    for(size_t i = 0; i < m.num_of_walls; i++) {
        line mobj = m.walls[i];

        printf("[(%.2f %.2f) | (%.2f %.2f)]\n",
                mobj.p1.x, mobj.p1.y,
                mobj.p2.x, mobj.p2.y);
    }
}