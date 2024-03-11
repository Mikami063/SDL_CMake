//
//  ColliderComponent.h
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-06.
//

#pragma once

#include <string>
#include "SDL.h"
//#include "ECS.h"//should need this line, but work without this line, strange xcode behaviour
#include "Components.h"//is that circular include?

class ColliderComponent: public Component{
public:
    SDL_Rect collider;
    std::string tag;
    
    TransformComponent* transform;
    
    ColliderComponent(const std::string& t){
        tag=t;
    }
    
    void init() override{//is this been used? it is, how?
        if(!entity->hasComponent<TransformComponent>()){
            entity->addComponent<TransformComponent>();
        }
        transform=&entity->getComponent<TransformComponent>();//save as pointer intead of reference, because [transform] is a pointer and you can't assign ref to pointer
        //and because it's a ref(the entity), so we use -> instead of .
        Game::colliders.push_back(this);
        
    }
    void update() override{
        collider.x=static_cast<int>(transform->position.x);//why not check at autocompletion, the type error
        collider.y=static_cast<int>(transform->position.y);
        collider.w=transform->width*transform->scale;
        collider.h=transform->height*transform->scale;
    }
};

