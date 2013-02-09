//
//  Timer.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Timer.h"

#ifdef __APPLE__

#include <mach/mach_time.h>

namespace Timer {
    
    static float _machTimeToSeconds(uint64_t machTime) {
        mach_timebase_info_data_t timebase;
        mach_timebase_info(&timebase);
        return machTime * (float)timebase.numer / timebase.denom / 1e9;
    }
    
    float elapsedTime() {
        static uint64_t start = 0;
        uint64_t end = 0;
        
        if(start == 0) {
            start = mach_absolute_time();
        }
        end = mach_absolute_time();
        
        return _machTimeToSeconds(end - start);
    }
    
}

#endif
