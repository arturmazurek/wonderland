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
    float real;
    float i;
    float j;
    float k;
    
    Quaternion() : real(0), i(0), j(0), k(0) {}
    Quaternion(const Quaternion& other) : real(other.real), i(other.i), j(other.j), k(other.k) {}
    Quaternion& operator=(const Quaternion& other) {
        real = other.real;
        i = other.i;
        j = other.j;
        k = other.k;
        
        return *this;
    }
    
    Quaternion& operator+=(const Quaternion& other) {
        real += other.real;
        i += other.i;
        j += other.j;
        k += other.k;
        
        return *this;
    }
    
    Quaternion& operator-=(const Quaternion& other) {
        real -= other.real;
        i -= other.i;
        j -= other.j;
        k -= other.k;
        
        return *this;
    }
    
    Quaternion& operator*=(const Quaternion& other) {
        real = real*other.real - i*other.i - j*other.j - k*other.k;
        i = real*other.i + i*other.real + j*other.k - k*other.j;
        j = real*other.j - i*other.k + j*other.real + k*other.i;
        k = real*other.k + i*other.j + j*other.i + k*other.real;
        
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
