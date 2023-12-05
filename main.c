#include "app_configuration.c"
#include "crossplatform_app/api.h"

#include "general_purpose_graph/api.h"

int main()
{
    printf("-1\n");
    SDL_LogMessage(SDL_LogInfo,SDL_LogVerbose,"-1");
    setup();

    printf("0\n");

    //Graph init
    graph main_graph;
    create_graph(&main_graph);

    //Example graph
    add_graph_node(&main_graph, create_node());
    main_graph.nodes[0]->x = 10;
    main_graph.nodes[0]->y = 10;
    add_graph_node(&main_graph, create_node());
    //trying to find my segfault here
    if(main_graph.nodes[1] != NULL)
    {
        main_graph.nodes[1]->x = 200;
        main_graph.nodes[1]->y = 10;
    }
    
    printf("1\n");

    //Main Loop
    bool running = true;
    while(running)
    {
        //Input
        #include "event_handling.c"
        
        printf("2\n");

        //GUI
        // #include "GUI_test.c"
        #include "GUI_loop.c"
        
        printf("3\n");

        //Rendering
        SDL_SetRenderDrawColor(renderer, 0.15,0.4,0.15,1.0);
        SDL_RenderClear(renderer);

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        SDL_RenderPresent(renderer);
        
        printf("4\n");
    }

    close();
}