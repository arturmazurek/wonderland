//
//  Game.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Game.h"

#include "Util/Timer.h"

#include "World.h"

Game::Game() : mFirstFrame(true), mLastFrameTime(0), mWorld(nullptr) {
    
}

Game::~Game() {
    delete mWorld;
}

void Game::setWorld(World* world) {
    if(mWorld) {
        delete mWorld;
    }
    
    mWorld = world;
    mFirstFrame = true;
}

void Game::doFrame() {
    if(!mWorld) {
        return;
    }
    
    float frameTime = Timer::elapsedTime() - mLastFrameTime;
    if(mFirstFrame) {
        mFirstFrame = false;
        frameTime = 0;
    }
    
    mWorld->update(mGameClock.tickTime(frameTime));
    
    mLastFrameTime = frameTime;
}