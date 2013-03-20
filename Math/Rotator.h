//
//  Rotator.h
//  Wonderland
//
//  Created by Artur Mazurek on 20/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Rotator_h
#define Wonderland_Rotator_h

#include "Quaternion.h"

class Rotator {
public:
    Rotator() {};
    
    Rotator(float yaw, float pitch, float roll) {
        setEulerAngles(yaw, pitch, roll);
    }
    
    Rotator(const Vector& axis, const float angle) {
        setAxis(axis, angle);
    }
    
    Rotator(const Quaternion& q) : mQ(q) {
        
    }
    
    void setEulerAngles(float yaw, float pitch, float roll) {
        
    }
    
    void setAxis(const Vector& axis, float angle) {
        
    }
    
    void setRotation(const Quaternion& q) {
        mQ = q;
    }
    
    const Quaternion& quaternion() const {
        return mQ;
    }
    
    

private:
    Quaternion mQ;
};

#endif
