//
//  Game.hpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <vector>

class ColliderComponent;//forward declaration, do we need this?
//we do need this

class Game{
public:
    Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running(){
        return isRunning;
    }
    
    static void AddTile(int srcX, int srcY, int xpos, int ypos);
    static SDL_Renderer* renderer;
    static SDL_Event event;//why don't use pointer here
    static std::vector<ColliderComponent*> colliders;
    static SDL_Rect camera;

private:
    int cnt=0;
    bool isRunning;
    SDL_Window* window;
    int width;
    int height;
    //SDL_Renderer* renderer;
};

#endif /* Game_hpp */
