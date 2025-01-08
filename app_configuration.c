#define APP_NAME "HFSTS"

// #define USE_VK
#define SDL_IMPLEMENTATION

/*----------------------MACRO-POST-PROCESSING-------------------------*/
#ifdef _WIN32
#define EXECUTABLE APP_NAME".exe"
#else
#define EXECUTABLE APP_NAME
#endif