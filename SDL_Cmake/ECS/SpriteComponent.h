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

#include "Animation.h"
#include <map>

class SpriteComponent: public Component{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect,destRect;
    //bool active=true;

    bool animated=false;
    int frames=0;
    int speed=100;//delay time between frames
    
public:

    int animIndex=0;

    std::map<const char*, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent()=default;
    SpriteComponent(const char* path){
        setTexture(path);
    }
    SpriteComponent(const char* path, bool isAnimated){
        animated=isAnimated;

        Animation idle = Animation(0,7,100);
        Animation walk = Animation(1,6,100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        Play("Idle");
        //frames=nFrames;
        //speed=mSpeed;
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

        if(animated){
            srcRect.x= srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%frames);
            //srcRect.x= srcRect.w * 6;
            //SDL_Log("Animated srcRect.x: %d (srcRect.x: )", srcRect.x);
        }

        srcRect.y= animIndex * transform->height;

        destRect.x=static_cast<int>(transform->position.x)-Game::camera.x;//more explicit, study
        //and also interesting camera location value fix for player go ahead of the camera, likely only the sprite part is ahead, study
        destRect.y=static_cast<int>(transform->position.y)-Game::camera.y;
        destRect.w=transform->width * transform->scale;
        //SDL_Log("transform->width: %d",transform->width);
        //SDL_Log("transform->scale: %d",transform->scale);
        //SDL_Log("the width: %d",destRect.w);
        destRect.h=transform->height * transform->scale;
        
    }
    void draw() override{
        TextureManager::Draw(texture, &srcRect, &destRect, spriteFlip);
        //SDL_Log("Draw in sprite: %d (srcRect.x: )", srcRect.x);
    }
    void Play(const char* animName){
        frames=animations[animName].frames;
        animIndex=animations[animName].index;
        speed=animations[animName].speed;
    }
};
