#include "app_configuration.c"
#include "crossplatform_app/api.h"

#include "general_purpose_graph/api.h"

int main()
{
    setup();
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    int l,r,t,b;
    SDL_GetWindowBordersSize(window, &t, &l, &b, &r);
    SDL_SetWindowSize(window, dm.w, dm.h - t - b - 45/*????*/);
    SDL_SetWindowPosition(window,0,20);
    int window_w,window_h;
    SDL_GetWindowSize(window, &window_w, &window_h);

    //Graph init
    graph* main_graph = create_graph();

    if(!main_graph)
    {
        printf("Failure! Couldn't create graph.\n");
        return 0;
    }

    //Example graph
    add_graph_node(main_graph, create_node());
    add_new_node_component(main_graph->nodes[0]);
    main_graph->nodes[0]->x = 10;
    main_graph->nodes[0]->y = 10;

    main_graph->nodes[0]->width = 100;
    main_graph->nodes[0]->height = 100*(main_graph->nodes[0]->max_component_index + 1);

    // add_graph_node(main_graph, create_node());
    // main_graph->nodes[1]->x = 200;
    // main_graph->nodes[1]->y = 10;
    // main_graph->nodes[1]->width = 100;
    // main_graph->nodes[1]->height = 100;

    //Main Loop
    bool running = true;
    while(running)
    {
        //Input
        #include "event_handling.c"

        //GUI
        // #include "GUI_test.c"
        #include "GUI_loop.c"

        //Rendering
        SDL_SetRenderDrawColor(renderer, 0.15,0.4,0.15,1.0);
        SDL_RenderClear(renderer);

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        SDL_RenderPresent(renderer);
    }

    close();
}