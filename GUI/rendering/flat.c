//Background
//nk_rgb(0.15*255,0.4*255,0.15*255);
//nk_rgb(1,77,78);
SDL_SetRenderDrawColor(renderer, 0.15*255,0.4*255,0.15*255 ,255);
SDL_RenderClear(renderer);

SDL_SetRenderDrawColor(renderer, 1,55,58 ,255);
uint8_t grid_size = 32;
uint16_t x = 0;
for(; x <= width; x += grid_size)
    SDL_RenderDrawLine(renderer, x + cam_x%grid_size, 0, x + cam_x%grid_size, height);
uint16_t y = 0;
for(; y <= height; y += grid_size)
    SDL_RenderDrawLine(renderer, 0, y + cam_y%grid_size, width, y + cam_y%grid_size);

//test + sign
SDL_Rect icon_location = {width/2 + cam_x, height/2 + cam_y, 32,32};
SDL_RenderCopy(renderer, icon_textures[PLUS], NULL, &icon_location);

//Context Groups (Nodes)
uint32_t node_index = 0;
for(; node_index < main_graph->max_node_index+1; node_index++)
{
    node* current_node = main_graph->nodes[node_index];
    if(current_node->context == CONTEXT_GROUP)
    {
        uint32_t* x_p = &current_node->data[0];
        uint32_t* y_p = &current_node->data[1];
        SDL_Rect node_rect = { *x_p + cam_x,
                                *y_p + cam_y,
                                100,100};

        SDL_SetRenderDrawColor(renderer, 25,25,25,255);
        SDL_RenderFillRect(renderer, &node_rect);
    }
}

SDL_RenderPresent(renderer);