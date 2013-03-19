//
//  Math.h
//  Wonderland
//
//  Created by Artur Mazurek on 15/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Math_h
#define Wonderland_Math_h

// We're using a right-hand coordinate system.

namespace Math {

    static const float pi = 3.14159265359f;
    static const float piInv = 0.31830988618f;
    static const float pi2 = 9.86960440109f;
    static const float deg2Rad = 180.f / pi;
    static const float rad2Deg = pi / 180.f;
    
    static inline float toDeg(float rad) {
        return rad * rad2Deg;
    }
    
    static inline float toRad(float deg) {
        return deg * deg2Rad;
    }
    
};

#endif
