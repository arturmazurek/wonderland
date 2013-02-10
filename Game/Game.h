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

class Renderer;
class World;

class Game {
public:
    Game();
    ~Game();
    
    void doFrame();
    
    bool initializeGame();
    
    void setWorld(World* world);

private:
    Game(const Game&);
    Game& operator=(const Game&);
    
    World* createWorld() const;
    
private:
    bool        mFirstFrame;
    GameClock   mGameClock;
    float       mLastFrameTime;
    Renderer*   mRenderer;
    World*      mWorld;
};

#endif /* defined(__Wonderland__Game__) */
