//
//  GameObject.hpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#pragma once
#include "Game.h"

class GameObject{
public:
    GameObject(const char* textureSheet, int x, int y);
    void Update();
    void Render();
private:
    int xpos;
    int ypos;
    SDL_Texture* objTexture;
    SDL_Rect srcRect,destRect;
    //SDL_Renderer* renderer;
};
