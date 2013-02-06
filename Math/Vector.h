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
    
    Vector operator-() {
        Vector result = *this;
        result.x *= -1; result.y *= -1; result.z *= -1;
        return result;
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
};
    
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
    
static inline float normalized(const Vector& a) {
    Vector result(a);
    return a.normalize();
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

#endif
