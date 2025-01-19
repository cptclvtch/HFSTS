#define APP_NAME "HFSTS"

#define SDL_IMPLEMENTATION

#define NK_IMPLEMENTATION
    #define NK_SDL_GL3_IMPLEMENTATION
    // #define NK_SDL_RENDERER_IMPLEMENTATION

/*----------------------MACRO-POST-PROCESSING-------------------------*/
#ifdef _WIN32
#define EXECUTABLE APP_NAME".exe"
#else
#define EXECUTABLE APP_NAME
#endif