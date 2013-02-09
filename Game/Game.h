//
//  Game.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Game__
#define __Wonderland__Game__

#include "GameClock.h"

class World;

class Game {
public:
    Game();
    ~Game();
    
    void setWorld(World* world);

    void doFrame();

private:
    Game(const Game&);
    Game& operator=(const Game&);
    
private:
    bool        mFirstFrame;
    GameClock   mGameClock;
    float       mLastFrameTime;
    World*      mWorld;
};

#endif /* defined(__Wonderland__Game__) */
