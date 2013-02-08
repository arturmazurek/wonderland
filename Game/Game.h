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

    void update(float wallTimeInSeconds);

private:
    Game(const Game&);
    Game& operator=(const Game&);
    
private:
    GameClock   mGameClock;
    World*      mWorld;
};

#endif /* defined(__Wonderland__Game__) */