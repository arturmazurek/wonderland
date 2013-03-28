//
//  Vector.h
//  Wonderland
//
//  Created by Artur Mazurek on 06.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Vector_h
#define Wonderland_Vector_h

#include <cmath>
#include <limits>

#include "Quaternion.h"

struct Vector {
    float x, y, z;
    
    Vector() : x(0), y(0), z(0) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector(const Vector& other) : x(other.x), y(other.y), z(other.z) {}
    Vector& operator=(const Vector& other) {
        x = other.x; y = other.y; z = other.z;
        return *this;
    }
    
    Vector& operator+=(const Vector& other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }
    
    Vector& operator-=(const Vector& other) {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }
    
    Vector& operator*=(float k) {
        x *= k; y *= k; z *= k;
        return *this;
    }
    
    Vector& operator/=(float k) {
        return (*this) *= (1.f / k);
    }
    
    float lengthSqr() const {
        return x*x + y*y + z*z;
    }
    
    float length() const {
        return sqrt(lengthSqr());
    }
    
    Vector& normalize() {
        (*this) /= length();
        return *this;
    }
    
    Vector& rotate(const Quaternion& q) {
        Quaternion v(x, y, z, 0);
        v *= q.conjugate();
        v = q*v;
        
        x = v.x;
        y = v.y;
        z = v.z;
        
        return *this;
    }
    
    static const Vector& zero() {
        static Vector result;
        return result;
    }
    
    static const Vector& unitX() {
        static Vector result(1.0f, 0.0f, 0.0f);
        return result;
    }
    
    static const Vector& unitY() {
        static Vector result(0.0f, 1.0f, 0.0f);
        return result;
    }
    
    static const Vector& unitZ() {
        static Vector result(0.0f, 0.0f, 1.0f);
        return result;
    }
};
    
static inline Vector operator-(const Vector& a) {
    Vector result;
    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    
    return result;
}
    
static inline Vector operator+(const Vector& a, const Vector& b) {
    Vector result(a);
    return result += b;
}
    
static inline Vector operator-(const Vector& a, const Vector& b) {
    Vector result(a);
    return result -= b;
}
    
static inline Vector operator*(const Vector& a, float k) {
    Vector result(a);
    return result *= k;
}
    
static inline Vector operator*(float k, const Vector& a) {
    return a * k;
}
    
static inline Vector operator/(const Vector& a, float k) {
    return a * (1.f / k);
}
    
static inline Vector normalized(const Vector& a) {
    Vector result(a);
    return result.normalize();
}
    
static inline float dot(const Vector& a, const Vector& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
    
static inline Vector cross(const Vector& a, const Vector& b) {
    Vector result;
    result.x = a.y*b.z - a.z*b.y;
    result.y = a.z*b.x - a.x*b.z;
    result.z = a.x*b.y - a.y*b.x;
    return result;
}
    
static inline bool equal(const Vector& a, const Vector& b, float epsilon = std::numeric_limits<float>::epsilon()) {
    using namespace std;
    return fabsf(a.x-b.x) <= epsilon && fabsf(a.y-b.y) <= epsilon && fabsf(a.z-b.z) <= epsilon;
}
    
#endif
