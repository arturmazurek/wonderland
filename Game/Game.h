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
#include "MessageQueue.h"

#include "Util/UniquePtr.h"

class GameInterface;
class Renderer;
class World;

class Game {
public:
    Game();
    ~Game();
    
    void doFrame();
    
    bool initializeGame();
    
    void setWorld(UniquePtr<World> world);
    
    GameInterface* gameInterface();

private:
    Game(const Game&);
    Game& operator=(const Game&);
    
    UniquePtr<World> createWorld() const;
    
private:
    bool                        mFirstFrame;
    GameClock                   mGameClock;
    float                       mLastFrameTime;
    MessageQueue                mMessageQueue;
    UniquePtr<GameInterface>    mGameInterface;
    UniquePtr<Renderer>         mRenderer;
    UniquePtr<World>            mWorld;
};

#endif /* defined(__Wonderland__Game__) */
