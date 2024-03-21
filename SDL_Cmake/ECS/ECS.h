//
//  ECS.hpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

//inline ComponentID getComponentTypeID(){
inline ComponentID getNewComponentTypeID(){
//    static ComponentID lastID=0;
    static ComponentID lastID=0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept{
    static ComponentID typeID{getNewComponentTypeID()};// i think?
    return typeID;//will this work?
}

constexpr std::size_t maxComponents=32;
constexpr std::size_t maxGroups=32;

using ComponentBitSet= std::bitset<maxComponents>;//why is it like this
using GroupBitSet= std::bitset<maxGroups>;

using ComponentArray= std::array<Component*,maxComponents>;

class Component{
public:
    Entity* entity;
    virtual void init(){}
    virtual void update(){}
    virtual void draw(){}
};

class Entity{
public:
    Entity(Manager& mManager):manager(mManager){}// study this: manager(mManager)
    void update(){
        for(auto& c: components){
            c->update();
        }
    }
    void draw(){
        for(auto& c: components){
            c->draw();
        }
        //SDL_Log("should not use this method");
    }
    bool isActive() const{
        return active;
    }
    void destroy(){
        active=false;
    }
    
    bool hasGroup(Group mGroup){// group the index?
        return groupBitSet[mGroup];
    }
    
    void addGroup(Group mGroup);
    void delGroup(Group mGroup){
        groupBitSet[mGroup]=false;
    }
    
    template <typename T> bool hasComponent() const{
        return componentBitSet[getComponentTypeID<T>()];//will study that, from youtube lesson 11 author comment
    }
    
    template <typename T,typename... TArgs>//will study this afterwards
    T& addComponent(TArgs&&... mArgs){
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity=this;
        std::unique_ptr<Component>uPtr{c};
        components.emplace_back(std::move(uPtr));
        
        componentArray[getComponentTypeID<T>()]=c;
        componentBitSet[getComponentTypeID<T>()]=true;
        
        c->init();
        return *c;
    }
    
    template<typename T> T& getComponent() const{
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
    
private:
    bool active=true;
    std::vector<std::unique_ptr<Component>> components;
    
    Manager& manager;
    
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
};

class Manager{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>,maxGroups> groupedEntities;//the 1st parameter used to declare type of class working with
public:
    void update(){
        for(auto& e:entities) e->update();
    }
    void draw(){
        for(auto& e : entities) e->draw();
    }
    void refresh(){
        for (auto i(0u); i < maxGroups; i++)
                {
                    auto& v(groupedEntities[i]);
                    v.erase(
                        std::remove_if(std::begin(v), std::end(v),
                            [i](Entity* mEntity)
                    {
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }),
                        std::end(v));
                }
        
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity){
                return !mEntity->isActive();
            }),std::end(entities));
        
    }
    
    void AddToGroup(Entity* mEntity,Group mGroup){//why get pointer instead of ref here? maybe need nullptr in init...
        groupedEntities[mGroup].emplace_back(mEntity);
    }
    
    std::vector<Entity*>& getGroup(Group mGroup){
        return groupedEntities[mGroup];
    }
    
    Entity& addEntity(){
        Entity* e= new Entity(*this);//why here *this work for putting a manager ¿instance? inside, study
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};
