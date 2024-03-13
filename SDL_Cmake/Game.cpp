//
//  Game.cpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-05.
//

#include "Game.h"
#include "TextureManager.h"
//#include "GameObject.h"//GO1
#include "Map.h"

#include "ECS/ECS.h"//M1
#include "ECS/Components.h"
#include "Collision.h"


/*
SDL_Texture* playerTex;
SDL_Rect srcR, destR;
 */
//GameObject* player;
//GameObject* enemy;//GO2
//Map* map;

SDL_Renderer* Game::renderer=nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;//why should we declare things here, to make it global on this file? study

Manager manager;//M2
auto& player(manager.addEntity());//M3
auto& wall(manager.addEntity());//will study later

//auto& tile0(manager.addEntity());

enum groupLabels: std::size_t{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

Game::Game(){
    
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags=0;
    if(fullscreen){
        flags=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        std::cout<<"subsystem initialized"<<std::endl;
        
        window=SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            std::cout<<"window created"<<std::endl;
        }
        
        renderer=SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout<<"renderer created"<<std::endl;
        }
        isRunning=true;
    }else{
        isRunning=false;
    }
    
    /*
    SDL_Surface* tmpSurface =IMG_Load("assets/woman-idle/woman-idle-1.png");
    playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    */
    /*
    playerTex=TextureManager::LoadTexture("assets/woman-idle/woman-idle-1.png", renderer);
    */
    //player=new GameObject("assets/woman-idle/woman-idle-1.png", 0, 0);
    //enemy=new GameObject("assets/hat-man-idle/hat-man-idle-1.png", 50, 50);//GO3
    //map=new Map();
    
    //ECS system
    
    Map::LoadMap("assets/lv1.txt", 16, 16);
    
    //tile0.addComponent<TileComponent>(200,200,32,32,2);//T here only accept Components in Components.h, should be, study, and TArgs don't provide auto complete based on type, issue
    //tile0.addComponent<ColliderComponent>("grass");
    
    //newPlayer.addComponent<PositionComponent>();
    //newPlayer.getComponent<PositionComponent>().setPos(500,500);
    player.addComponent<TransformComponent>(0.0f,0.0f,46,37,2);//M4
    player.addComponent<SpriteComponent>("assets/woman.png",true);//M5
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    wall.addComponent<TransformComponent>(300.0f,300.0f,300,20,1);
    wall.addComponent<SpriteComponent>("assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(groupMap);
}
void Game::handleEvents(){
    
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning=false;
            break;
            
        default:
            break;
    }
}
void Game::update(){
    /*
    cnt++;
    destR.h=64;
    destR.w=64;
    destR.x=cnt;
    std::cout<<cnt<<std::endl;
    */
    //player->Update();
    //enemy->Update();//GO4
    
    manager.refresh();//M6
    manager.update();//M7
    
    for (auto cc: colliders){//so the cc is a reference? i mean it don't copy data right?
        if(Collision::AABB(player.getComponent<ColliderComponent>(), *cc)){//why deref cc and why not player.getComponent<ColliderComponent>.collider?, ok the ColliderComponent is the input type
            std::cout<< "Something Hits!"<< player.getComponent<ColliderComponent>().tag<< " -> Hits -> "<<cc->tag <<std::endl;
        }
    }
    /*
    if(Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)){
        player.getComponent<TransformComponent>().velocity*-1;//scale to -1
        std::cout<< "Wall Hits!" <<std::endl;
    }
     */
    /*player.getComponent<TransformComponent>().position.Add(Vector2D(5,0));
    if(player.getComponent<TransformComponent>().position.x>500){
        player.getComponent<SpriteComponent>().setTexture("assets/hat-man-idle/hat-man-idle-1.png");
    }
     */
    //std::cout<<player.getComponent<TransformComponent>().x()<<","<<player.getComponent<TransformComponent>().y()<<std::endl;
}

auto& tiles(manager.getGroup(groupMap));// the type is std::vector<Entity*>&
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render(){
    SDL_RenderClear(renderer);
    /*
    SDL_RenderCopy(renderer, playerTex, nullptr, &destR);
    */
    //map->DrawMap();//tmp disable map
    //player->Render();
    //enemy->Render();//GO5
    //manager.draw();//M8
    for(auto& t : tiles){
        t->draw();
    }
    for(auto& p : players){
        p->draw();
    }
    for(auto& e : enemies){
        e->draw();
    }
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Game cleared"<<std::endl;
}

void Game::AddTile(int id, int x, int y){
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x,y,32,32,id);
    tile.addGroup(groupMap);
}
