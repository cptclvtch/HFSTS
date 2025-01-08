enum
{
    PLUS,

    NO_OF_ICONS
};

char* icon_names[NO_OF_ICONS] = 
{
    "plus",

};

SDL_Texture* icon_textures[NO_OF_ICONS];

void load_icons()
{
    printf("\tLoading icons.\n");

    uint8_t index = 0;
    char asset_path[256];
    for(;index < NO_OF_ICONS;index++)
    {
        sprintf(asset_path, "%s/assets/icons/%s.bmp", SDL_GetBasePath(), icon_names[index]);
        SDL_Surface* surf = SDL_LoadBMP(asset_path);
        if(surf != NULL)
        {
            icon_textures[index] = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
        }
        else
        {
            printf("\t\tCouldn't load %s, because: %s\n", asset_path, SDL_GetError());
        }
    }
}