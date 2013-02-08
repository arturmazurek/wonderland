//
//  GameClock.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "GameClock.h"

#include "Util/Log.h"

GameClock::GameClock() : mLastTickDuration(0), mTimeFlowSpeed(1), mTotalTime(0) {
    
}

GameClock::~GameClock() {
    
}

void GameClock::setTimeFlowSpeed(float k) {
    if(k < 0) {
        LOG("Can't set time flow speed lesser than 0 - %f", k);
        return;
    }
    mTimeFlowSpeed = k;
}

float GameClock::totalTime() const {
    return mTotalTime;
}

float GameClock::tickTime(float wallDtInSeconds) {
    wallDtInSeconds *= mTimeFlowSpeed;
    mTotalTime += mLastTickDuration;
    mLastTickDuration = wallDtInSeconds;
    return wallDtInSeconds;
}