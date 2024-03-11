//
//  PositionComponent.h
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-06.
//

#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent: public Component{
public:
    Vector2D position;
    Vector2D velocity;
    
    int height=32;
    int width=32;
    int scale=1;
    
    int speed =3;
    
    TransformComponent(){
        position.Zero();
    }
    TransformComponent(int scale){
        position.Zero();
        this->scale=scale;
    }
    TransformComponent(float x, float y){
        position.x=x;
        position.y=y;
    }
    TransformComponent(float x, float y,int h, int w, int scale){
        position.x=x;
        position.y=y;
        height=h;
        width=w;
        this->scale=scale;//study why this is a pointer
    }
    void init() override{//why can seperate like this, wtf is init and constructor in the same time, lame
        velocity.Zero();
    }
    void update() override{
        position.x+=velocity.x*speed;
        position.y+=velocity.y*speed;
    }

};
