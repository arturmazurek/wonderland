//
//  GameClock.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__GameClock__
#define __Wonderland__GameClock__

class GameClock {
public:
    GameClock();
    ~GameClock();
    
    void setTimeFlowSpeed(float k);
    
    float totalTime() const;
    float tickTime(float wallDtInSeconds);
    
private:
    GameClock(const GameClock&);
    GameClock& operator=(const GameClock&);
    
private:
    float mLastTickDuration;
    float mTimeFlowSpeed;
    float mTotalTime;
};

#endif /* defined(__Wonderland__GameClock__) */
