//
//  Timer.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Timer.h"

#ifdef __APPLE__

#include <sys/time.h>

namespace Timer {
    
    float elapsedTime() {
        static bool firstRun = true;
        static timeval referenceTime = {0};
        
        if(firstRun) {
            gettimeofday(&referenceTime, NULL);
        }
        
        timeval timeNow = {0};
        gettimeofday(&timeNow, NULL);
        
        float timeDiff = timeNow.tv_sec - referenceTime.tv_sec;
        timeDiff += (timeNow.tv_usec - referenceTime.tv_usec) * 0.001f;
        
        return timeDiff;
    }
    
}

#endif
