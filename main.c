#define APP_NAME "HFSTS"
#include "crossplatform_app/api.c"

#include "general_purpose_graph/api.h"

int main()
{
    setup();
    nk_bg.r = 0.15;
    nk_bg.g = 0.4;
    nk_bg.b = 0.15;
    nk_bg.a = 1.0;

    //Main Loop
    bool running = true;
    while(running)
    {
        //Input
        EVENT event;
        nk_input_begin(ctx);
        while(poll_event(&event))
        {
        if(event.type == SDL_QUIT)
        {
            running = false;
        }
        else
        if(event.type == SDL_KEYDOWN)
        {
            const char *key = SDL_GetKeyName(event.key.keysym.sym);
            if(strcmp(key, "Q") == 0)
            {
            running = false;
            }
        }
        nk_sdl_handle_event(&event);
        }
        nk_input_end(ctx);

        //GUI
        // #include "GUI_loop.c"

        SDL_SetRenderDrawColor(renderer, nk_bg.r * 255, nk_bg.g * 255, nk_bg.b * 255, nk_bg.a * 255);
        SDL_RenderClear(renderer);

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        SDL_RenderPresent(renderer);
    }

    close();
}