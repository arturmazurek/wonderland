//
//  Game.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Game.h"

#include "World.h"

Game::Game() : mWorld(nullptr) {
    
}

Game::~Game() {
    delete mWorld;
}

void Game::setWorld(World* world) {
    if(mWorld) {
        delete mWorld;
    }
    
    mWorld = world;
}

void Game::update(float wallTimeInSeconds) {
    if(!mWorld) {
        return;
    }
    
    mWorld->update(mGameClock.tickTime(wallTimeInSeconds));
}