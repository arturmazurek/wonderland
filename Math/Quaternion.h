//
//  Quaternion.h
//  Wonderland
//
//  Created by Artur Mazurek on 19/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Quaternion_h
#define Wonderland_Quaternion_h

struct Quaternion {
    float x;
    float y;
    float z;
    float w;
    
    Quaternion() : x(0), y(0), z(0), w(0) {}
    Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
    Quaternion& operator=(const Quaternion& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        
        return *this;
    }
    
    Quaternion& operator+=(const Quaternion& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        
        return *this;
    }
    
    Quaternion& operator-=(const Quaternion& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        
        return *this;
    }
    
    Quaternion& operator*=(const Quaternion& other) {
        x = x*other.x - y*other.y - z*other.z - w*other.w;
        y = x*other.y + y*other.x + z*other.w - w*other.z;
        z = x*other.z - y*other.w + z*other.x + w*other.y;
        w = x*other.w + y*other.z + z*other.y + w*other.x;
        
        return *this;
    }
};
    
static inline Quaternion operator+(const Quaternion& a, const Quaternion& b) {
    Quaternion result(a);
    return result += b;
}
    
static inline Quaternion operator-(const Quaternion& a, const Quaternion& b) {
    Quaternion result(a);
    return result -= b;
}
    
static inline Quaternion operator*(const Quaternion& a, const Quaternion& b) {
    Quaternion result(a);
    return result *= a;
}

#endif
