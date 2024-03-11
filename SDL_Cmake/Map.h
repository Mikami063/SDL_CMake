//
//  Map.hpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#pragma once
//#include "Game.h"
#include <string>


class Map{
public:
    Map();
    ~Map();
    //void LoadMap(int arr[20][25]);
    static void LoadMap(std::string path, int sizeX, int sizeY);//what about const char* here? and what about make int int& here, study
    //void DrawMap();
private:
    /*
    SDL_Rect src, dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;
    
    int map[20][25];
     */
    
};
