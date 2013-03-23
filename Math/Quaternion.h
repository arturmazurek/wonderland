//
//  Quaternion.h
//  Wonderland
//
//  Created by Artur Mazurek on 19/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Quaternion_h
#define Wonderland_Quaternion_h

#include "Util/Log.h"

struct Quaternion {
    float x;
    float y;
    float z;
    float w;
    
    Quaternion() : x(0), y(0), z(0), w(0) {}
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
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
    
    Quaternion& operator*=(float k) {
        x *= k;
        y *= k;
        z *= k;
        w *= k;
        
        return *this;
    }
    
    Quaternion& operator/=(float k) {
        return (*this) *= (1.0f / k);
    }
    
    float normSqr() const {
        return x*x + y*y + z*z + w*w;
    }
    
    float norm() const {
        return std::sqrt(normSqr());
    }
    
    Quaternion normalized() const {
        Quaternion result(*this);
        result.normalize();
        
        return result;
    }
    
    Quaternion& normalize() {
        return (*this) /= norm();
    }
    
    Quaternion conjugate() const {
        Quaternion result(*this);
        result.x *= -1;
        result.y *= -1;
        result.z *= -1;
        
        return result;
    }
    
    Quaternion inverse() const {
        Quaternion result = conjugate();
        if(x == 0 && y == 0 && z == 0 && w == 0) {
            return result;
        }
    
        result /= norm();
        
        return result;
    }
};
    
static inline Quaternion operator+(const Quaternion& a, const Quaternion& b) {
    Quaternion result(a);
    result += b;
    return result;
}
    
static inline Quaternion operator-(const Quaternion& a, const Quaternion& b) {
    Quaternion result(a);
    result -= b;
    return result;
}
    
static inline Quaternion operator*(const Quaternion& a, const Quaternion& b) {
    Quaternion result(a);
    result *= a;
    return result;
}
    
static inline Quaternion operator*(const Quaternion& a, float k) {
    Quaternion result(a);
    result *= k;
    return result;
}
    
static inline Quaternion operator*(float k, const Quaternion& a) {
    return a * k;
}
    
static inline Quaternion operator/(const Quaternion& a, float k) {
    Quaternion result(a);
    result /= k;
    return result;
}

#endif
