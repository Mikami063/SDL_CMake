//
//  TextureManager.h
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#pragma once

#include "Game.h"

class TextureManager{
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    //static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
    static void Draw(SDL_Texture* tex, const SDL_Rect* src, const SDL_Rect* dest);
};
