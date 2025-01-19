//Background
//nk_rgb(0.15*255,0.4*255,0.15*255);
//nk_rgb(1,77,78);
glClearColor(0.15,0.4,0.15 ,1);
glClear(GL_COLOR_BUFFER_BIT);

node_editor(ctx);

nk_sdl_render(NK_ANTI_ALIASING_ON, NK_MAX_VERTEX_MEMORY, NK_MAX_ELEMENT_MEMORY);

SDL_GL_SwapWindow(window);