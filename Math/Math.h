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

    static const float PI = 3.14159265359f;
    static const float PI_INV = 0.31830988618f;
    static const float PI2 = 9.86960440109f;
    static const float DEG_2_RAD = PI / 180.f;
    static const float RAD_2_DEG = 180.f / PI;
    static const float EPSILON = 0.00001;
    
    static inline float toDeg(float rad) {
        return rad * RAD_2_DEG;
    }
    
    static inline float toRad(float deg) {
        return deg * DEG_2_RAD;
    }
    
};

#endif
