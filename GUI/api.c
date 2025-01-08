int32_t cam_x, cam_y;

#include "icons.c"

void load_ui()
{
    printf("Loading UI\n");
    load_icons();
    printf("Done.\n");
}

void render_ui()
{
    #ifndef VR_BUILD
    #include "rendering/flat.c"
    #else
    #include "rendering/stereo.c"
    #endif
}