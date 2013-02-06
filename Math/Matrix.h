//
//  Matrix.h
//  Wonderland
//
//  Created by Artur Mazurek on 06.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Matrix_h
#define Wonderland_Matrix_h

#include <cstring>

#include "Vector.h"

// m00 m01 m02 m03
// m10 m11 m12 m13
// m20 m21 m22 m23
// m30 m31 m32 m33
struct Matrix {
    // column-major ordering
    float m[4*4];
    
    Matrix() { memset(m, 0, sizeof(m)); }
    Matrix(const Matrix& other) { std::memcpy(m, other.m, sizeof(m)); }
    Matrix(float *elements) { std::memcpy(m, elements, sizeof(m)); }
    Matrix& operator=(const Matrix& other) { std::memcpy(m, other.m, sizeof(m)); return *this; }
    
    Matrix& operator*=(float k) {
        for(int i = 0; i < 16; ++i) {
            m[i] *= k;
        }
        return *this;
    }
    
    Matrix& operator-=(float k) {
        return (*this) *= k;
    }
    
    static inline int index(int i, int j) {
        return 4*j + i;
    }
    
    Matrix& setTranslation(const Vector& v) {
        m[index(0, 3)] = v.x;
        m[index(1, 3)] = v.y;
        m[index(2, 3)] = v.z;
        return *this;
    }
    
    Matrix& translate(const Vector& v) {
        m[index(0, 3)] += v.x;
        m[index(1, 3)] += v.y;
        m[index(2, 3)] += v.z;
        return *this;
    }
    
    static Matrix identity() {
        Matrix result;
        result.m[0] = 1;
        result.m[index(1, 1)] = 1;
        result.m[index(2, 2)] = 1;
        result.m[index(3, 3)] = 1;
        return result;
    }
    
    static Matrix perspective(float fovy, float aspect, float nearZ, float farZ) {
        Matrix result;
        
        float f = 1.f / std::tanf( (M_PI * fovy /180) * 0.5f);
        result.m[0] = f / aspect;
        result.m[index(1, 1)] = f;
        result.m[index(2, 2)] = (farZ + nearZ) / (nearZ - farZ);
        result.m[index(3, 2)] = -1;
        result.m[index(2, 3)] = (2 * farZ * nearZ) / (nearZ - farZ);
        
        return result;
    }
    
    static Matrix ortho(float width, float height, float near, float far) {
        Matrix result = identity();
        
        result.m[index(0, 0)] = 2.0f / width;
        result.m[index(1, 1)] = 2.0f / height;
        result.m[index(2, 2)] = -1.0f;
        result.m[index(0, 3)] = -1.0f;
        result.m[index(1, 3)] = -1.0f;
        
        return result;
    }
};
    

#endif
