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