//
//  Map.cpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#include "Map.h"

#include "Game.h"
#include <fstream>
#include <iostream>

#include <sys/stat.h> // For stat
#include <unistd.h>
#include <dirent.h> // Directory entry

//#include "PathToolMacOS.h"

Map::Map(){}
    
Map::~Map(){}

// Function to check if a file exists
bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void printDirectoryTree(const char* basePath, const std::string& prefix = "") {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(basePath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // Skip the current and parent directory entries
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }
            std::cout << prefix << ent->d_name << std::endl;
            if (ent->d_type == DT_DIR) {
                // Construct new basePath for the directory
                std::string newBasePath = std::string(basePath) + "/" + std::string(ent->d_name);
                // Recursively print the directory contents with an updated prefix
                printDirectoryTree(newBasePath.c_str(), prefix + "    ");
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}

void printCurrentWorkingDirAndTree() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current working dir: " << cwd << std::endl;
        printDirectoryTree(cwd); // Now also prints the directory tree
    } else {
        perror("getcwd() error");
    }
}

void Map::LoadMap(std::string path, int sizeX, int sizeY){
    char c;
    
    //std::string path=PathToolMacOS::getResourcePath(pathArg);
    
    //printCurrentWorkingDirAndTree();//open of the evil path
    if (!fileExists(path)) {
            std::cerr << "File does not exist: " << path << std::endl;
            return;
    }
    
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    if (!mapFile) {
            std::cerr << "Failed to open map file: " << path << std::endl;
            return; // Exit the function if file opening fails
        }
    
    for(int y=0;y<sizeY;y++){
        for(int x=0;x<sizeX;x++){
            mapFile.get(c);//how this work, why can get(tile)
            srcY=atoi(&c)*32;
            mapFile.get(c);//this is to read the second character,can't delete
            srcX=atoi(&c)*32;
            //Game::AddTile(atoi(&tile), x*32, y*32);
            Game::AddTile(srcX,srcY,x*64,y*64);
            std::cout<<"location: "<<y<<":"<<x<<" [tile]: "<<srcY<<":"<<srcX<<std::endl;
            mapFile.ignore();
        }
    }
    
    mapFile.close();
}
/*
#include "TextureManager.h"

int lvl1[20][25]={{0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,2,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map(){
    dirt=TextureManager::LoadTexture("assets/dirt.png");
    grass=TextureManager::LoadTexture("assets/grass.png");
    water=TextureManager::LoadTexture("assets/water.png");
    
    LoadMap(lvl1);
    
    src.x=src.y=dest.x=dest.y=0;
    src.w=src.h=dest.w=dest.h=32;
}

Map::~Map(){
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(water);
}

void Map::LoadMap(int arr[20][25]){
    for(int row=0;row<20;row++){
        for(int col=0;col<25;col++){
            map[row][col]=arr[row][col];
        }
    }
}

void Map::DrawMap(){
    int type=0;
    
    for(int row=0;row<20;row++){
        for(int col=0;col<25;col++){
            type=map[row][col];
            dest.x=col*32;
            dest.y=row*32;
            
            switch (type) {
                case 0:
                    TextureManager::Draw(water, &src, &dest);
                    break;
                    
                case 1:
                    TextureManager::Draw(grass, &src, &dest);
                    break;
                    
                case 2:
                    TextureManager::Draw(dirt, &src, &dest);
                    break;
                    
                default:
                    break;
            }
        }
    }
}
*/
