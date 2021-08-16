#include "../include/renderer.h"
#include "../include/camera.h"

void handle_ray(SDL_Renderer *rnd, line ray, map mp, point pos, int ray_ix, float angle) {
    distance closest_pt = get_closest_intr_pt(ray, mp, pos);
    if(!closest_pt.p.is_valid) return;

    float _dist = closest_pt.ds;

    float rect_w = (float)DEF_WND_WIDTH / (float)DEF_RAY_NUM;
    float rect_h = DEF_WND_HEIGHT / _dist;

    SDL_FRect rc = {
        .x = rect_w * (float)ray_ix,
        .y = (DEF_WND_HEIGHT - rect_h) / 2,
        .w = rect_w,
        .h = rect_h
    };

    Uint8 col = 255 / ((int)closest_pt.ds + 1);

    SDL_SetRenderDrawColor(rnd, 0, col, col, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(rnd, &rc);
}
                
int SDL_main(int argc, char *argv[]) {
    if(argc < 2)
        ISSUE_ERROR("Usage: ./pdr <map_file>");

    SDL_Init(SDL_INIT_VIDEO);

    map m = read_map(argv[1]);
    point screen_sz = { 
        .x = DEF_WND_WIDTH,
        .y = DEF_WND_HEIGHT    
    };

    SDL_Event event;
    SDL_Window *wnd = SDL_CreateWindow(
        "Pseudo-3D Renderer", 
        30, 30,
        screen_sz.x, screen_sz.y,
        SDL_WINDOW_OPENGL
    );

    SDL_FRect bottom = {
        .x = 0,
        .y = DEF_WND_HEIGHT / 2,
        .w = DEF_WND_WIDTH,
        .h = DEF_WND_HEIGHT / 2
    };

    SDL_Surface *icon = SDL_LoadBMP("../img/p3d2.bmp");
    SDL_SetWindowIcon(wnd, icon);

    SDL_ShowWindow(wnd);

    SDL_Renderer *rnd = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
    SDL_KeyCode pressed_key;

    point player_pos = m.player_init_pos;
    int angle_offset = 0;

    camera main_cam = make_camera(
        USE_DEF, USE_DEF,
        200 * 200,
        &player_pos, 
        &angle_offset, 
        handle_ray
    );

    angle_offset = 90 - main_cam.fov / 2;

    //Render the first frame.
    {
        SDL_SetRenderDrawColor(rnd, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRectF(rnd, NULL);

        SDL_SetRenderDrawColor(rnd, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRectF(rnd, &bottom);

        update_camera(&main_cam, m, rnd);
        SDL_RenderPresent(rnd);
    }
    
    //Show key bindings
    {
        char *msg =
        "W - Move forward\n"
        "S - Move backward\n"
        "F - Turn left\n"
        "E - Turn right\n";

        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_INFORMATION, 
            "Key bindings", 
            msg, 
            wnd
        );
    }
    
    while(SDL_TRUE) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                goto quit;
                break;
            case SDL_KEYDOWN:
                pressed_key = event.key.keysym.sym;
                double dir_angle = main_cam.fov / 2 + angle_offset;

                switch(pressed_key) {
                case SDLK_w:
                    translate(&player_pos, screen_sz, 1, dir_angle);
                    break;
                case SDLK_s:
                    translate(&player_pos, screen_sz, -1, dir_angle);
                    break;
                case SDLK_e:
                    if(angle_offset >= 360)
                        angle_offset = 0;

                    angle_offset += TURN_SPEED;
                    break;
                case SDLK_f:
                    if(angle_offset <= 0) {
                        angle_offset = 360;
                    }

                    angle_offset -= TURN_SPEED;
                    break;
                }
            }

            SDL_SetRenderDrawColor(rnd, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRectF(rnd, NULL);

            SDL_SetRenderDrawColor(rnd, 0, 0, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRectF(rnd, &bottom);

            update_camera(&main_cam, m, rnd);

            break;
        }

        SDL_RenderPresent(rnd);
    }

quit:
    SDL_DestroyWindow(wnd);
    SDL_DestroyRenderer(rnd);
    SDL_FreeSurface(icon);
    SDL_Quit();

    return 0;
}