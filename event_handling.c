SDL_Event event;
float mouse_dx, mouse_dy;
while(SDL_PollEvent(&event))
{
    switch(event.type)
    {
        case SDL_QUIT: running = 0; break;
    
        case SDL_KEYDOWN:
        {
            const char* key;
            key = SDL_GetKeyName(event.key.keysym.sym); 
            if(strcmp(key, "Q") == 0) running = 0;
        }
        break;
        
        case SDL_MOUSEMOTION:
            mouse_dx = event.motion.xrel;
            mouse_dy = event.motion.yrel;
            if(mouse_dx == 1 || mouse_dx == -1) mouse_dx = 0;
            if(mouse_dy == 1 || mouse_dy == -1) mouse_dy = 0;
            // cam_x += mouse_dx;
            // cam_y += mouse_dy;
        break;

        case SDL_MOUSEBUTTONDOWN:
            if(add_new_graph_node(main_graph) == NODE_NO_ERROR)
            {
                main_graph->nodes[main_graph->max_node_index]->context = CONTEXT_GROUP;
                main_graph->nodes[main_graph->max_node_index]->data[0] = event.button.x + cam_x;
                main_graph->nodes[main_graph->max_node_index]->data[1] = event.button.y + cam_y;
            }
        break;

        case SDL_WINDOWEVENT:
            switch(event.window.event)
            {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_GetWindowSize(window, &width, &height);
            }
        break;
    }
}