//
//  SpriteComponent.h
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-06.
//

#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent: public Component{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect,destRect;
    //bool active=true;
    
public:
    SpriteComponent()=default;
    SpriteComponent(const char* path){
        setTexture(path);
    }
    ~SpriteComponent(){
        SDL_DestroyTexture(texture);//should we need this manually set destructor?
        //yeah you should, the default one don't handle 3rd party library's own memory management
    }
    void setTexture(const char* path){
        texture=TextureManager::LoadTexture(path);
    }
    void init() override{
        transform=&entity->getComponent<TransformComponent>();
        
        srcRect.x=srcRect.y=0;
        srcRect.w=transform->width;
        srcRect.h=transform->height;
        
        //destRect.w=destRect.h=64;
    }
    void update() override{
        //destRect.x=(int)transform->position.x;
        destRect.x=static_cast<int>(transform->position.x);//more explicit, study
        destRect.y=static_cast<int>(transform->position.y);
        destRect.w=transform->width * transform->scale;
        destRect.h=transform->height * transform->scale;
    }
    void draw() override{
        TextureManager::Draw(texture, nullptr, &destRect);
    }
};
