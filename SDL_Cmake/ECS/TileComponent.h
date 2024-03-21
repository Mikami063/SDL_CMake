//
//  TileComponent.h
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-07.
//

#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
#include <string>

class TileComponent: public Component{
public:
    /*
    TransformComponent* transform;
    SpriteComponent* sprite;
    */
    //why here we decide to save location without transform component, i mean to put it locally, why, will study

    SDL_Texture* texture;
    
    SDL_Rect srcRect, destRect;

    Vector2D position;// the real position of the tile
    //int tileID;
    //char* path;
    //std::string path;
    
    
    TileComponent()=default;

    ~TileComponent(){
        SDL_DestroyTexture(texture);
    };

    TileComponent(int srcX,int srcY,int xpos,int ypos,const char* path){
        texture=TextureManager::LoadTexture(path);

        position.x=xpos;
        position.y=ypos;

        srcRect.x=srcX;
        srcRect.y=srcY;
        srcRect.w=srcRect.h=32;

        destRect.x=xpos;
        destRect.y=ypos;
        destRect.w=destRect.h=64;

    }

    void update() override{
        destRect.x=position.x-Game::camera.x;
        destRect.y=position.y-Game::camera.y;
    }

    void draw() override{
        TextureManager::Draw(texture,&srcRect,&destRect,SDL_FLIP_NONE);
    }

    // TileComponent(int x, int y, int w, int h, int id){
    //     texture=TextureManager::LoadTexture(path);
    //     tileRect.x=x;
    //     tileRect.y=y;
    //     tileRect.w=w;
    //     tileRect.h=h;
    //     tileID=id;
        
    //     switch (tileID) {
    //         case 0:
    //             path= "assets/water.png";
    //             break;
    //         case 1:
    //             path= "assets/dirt.png";
    //             break;
    //         case 2:
    //             path= "assets/grass.png";
    //             break;
                
    //         default:
    //             break;
    //     }
    // }


    //the old init()
    /*
    void init() override{
        entity->addComponent<TransformComponent>(tileRect.x,tileRect.y,tileRect.w,tileRect.h,1);
        transform=&entity->getComponent<TransformComponent>();//save the quick ref
        
        entity->addComponent<SpriteComponent>(path);
        sprite=&entity->getComponent<SpriteComponent>();//save the quick ref
    }
    */
    
};
