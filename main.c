#include "app_configuration.c"
#include "../crossplatform_app/api.c"

#include "general_purpose_graph/api.h"
// #include "../graph_c/graph_c.c"

graph* main_graph;
struct SDL_Renderer* renderer;
#include "GUI/api.c"

int main()
{
    setup();
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    CHECK_ERROR(renderer == NULL, SDL_GetError());

    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_GetWindowSize(window, &width, &height);

    load_ui();

    //Graph init
    main_graph = create_graph();
    if(!main_graph)
    {
        printf("Failure! Couldn't create graph.\n");
        return 0;
    }

    //Main Loop
    while(running)
    {
        #include "event_handling.c"

        //GUI
        render_ui();

        //FPS normalization
        past_reading += dt;
        dt = SDL_GetTicks() - past_reading;
        SDL_Delay((1000/target_fps - dt)*(dt < 1000/target_fps));
    }

    close();
    SDL_DestroyRenderer(renderer);
}