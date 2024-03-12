//
//  TextureManager.cpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#include "TextureManager.h"
#include "SDL2_image/SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(const char *fileName){
    SDL_Surface* tmpSurface = IMG_Load(fileName);
    SDL_Texture* tex=SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    
    if (tex == NULL) {
        SDL_Log("Unable to load texture! SDL_Error: %s\n", SDL_GetError());
    }

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, const SDL_Rect* src, const SDL_Rect* dest){
    //SDL_Log("Draw in TexMan: %d (srcRect.x: )", src->x);
    SDL_RenderCopy(Game::renderer, tex, src, dest);
}
