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

#include <cmath>

#include "Quaternion.h"
#include "Vector.h"

// m00 m01 m02 m03
// m10 m11 m12 m13
// m20 m21 m22 m23
// m30 m31 m32 m33
struct Matrix {
    static const int N = 4;
    
    // column-major ordering
    float m[N*N];
    
    Matrix() { memset(m, 0, sizeof(m)); }
    Matrix(const Matrix& other) { std::memcpy(m, other.m, sizeof(m)); }
    Matrix(float *elements) { std::memcpy(m, elements, sizeof(m)); }
    Matrix& operator=(const Matrix& other) { std::memcpy(m, other.m, sizeof(m)); return *this; }
    
    static int index(int i, int j) {
        return 4*j + i;
    }
    
    Matrix& operator*=(float k) {
        for(int i = 0; i < 16; ++i) {
            m[i] *= k;
        }
        return *this;
    }
    
    Matrix& operator/=(float k) {
        return (*this) *= (1.0f / k);
    }
    
    Vector getColumn(int j) {
        return Vector(m[index(0, j)], m[index(1, j)], m[index(2, j)]);
    }
    
    void setColumn(int j, const Vector& v) {
        m[index(0, j)] = v.x;
        m[index(1, j)] = v.y;
        m[index(2, j)] = v.z;
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
    
    Matrix& setScale(float s) {
        return setScale(s, s, s);
    }
    
    Matrix& setScale(float sx, float sy, float sz) {
        float scales[] = {sx, sy, sz};
        
        for(int i = 0; i < 3; ++i) {
            Vector temp = getColumn(i);
            temp.normalize();
            temp *= scales[i];
            setColumn(i, temp);
        }
        
        return *this;
    }
    
    Matrix& scale(float s) {
        return scale(s, s, s);
    }
    
    Matrix& scale(float sx, float sy, float sz) {
        m[index(0, 0)] *= sx; m[index(1, 0)] *= sx; m[index(2, 0)] *= sx;
        m[index(0, 1)] *= sy; m[index(1, 1)] *= sy; m[index(2, 1)] *= sy;
        m[index(0, 2)] *= sz; m[index(1, 2)] *= sz; m[index(2, 2)] *= sz;
        
        return *this;
    }
    
    static Matrix createIdentity() {
        Matrix result;
        result.m[0] = 1;
        result.m[index(1, 1)] = 1;
        result.m[index(2, 2)] = 1;
        result.m[index(3, 3)] = 1;
        return result;
    }
    
    static Matrix createScale(float s) {
        return createScale(s, s, s);
    }
    
    static Matrix createScale(float sx, float sy, float sz) {
        Matrix result;
        result.m[index(0, 0)] = sx;
        result.m[index(1, 1)] = sy;
        result.m[index(2, 2)] = sz;
        result.m[index(3, 3)] = 1;
        
        return result;
    }
    
    static Matrix createTranslation(const Vector& v) {
        Matrix result = createIdentity();
        result.m[index(0, 3)] = v.x;
        result.m[index(1, 3)] = v.y;
        result.m[index(2, 3)] = v.z;
        
        return result;
    }
    
    static Matrix createPerspective(float fovy, float aspect, float nearZ, float farZ) {
        Matrix result;
        
        float f = 1.f / std::tanf( (M_PI * fovy /180) * 0.5f);
        result.m[0] = f / aspect;
        result.m[index(1, 1)] = f;
        result.m[index(2, 2)] = (farZ + nearZ) / (nearZ - farZ);
        result.m[index(3, 2)] = -1;
        result.m[index(2, 3)] = (2 * farZ * nearZ) / (nearZ - farZ);
        
        return result;
    }
    
    static Matrix createOrtho(float width, float height, float near, float far) {
        Matrix result = createIdentity();
        
        result.m[index(0, 0)] = 2.0f / width;
        result.m[index(1, 1)] = 2.0f / height;
        result.m[index(2, 2)] = -1.0f;
        
        result.m[index(0, 3)] = 0;
        result.m[index(1, 3)] = 0;
        result.m[index(2, 3)] = -1.0f * (far + near) / (far - near);
        
        return result;
    }
    
    // yaw is rotation around axis Y
    // pitch is rotation around axis Z
    // roll is rotation around axis X
    static Matrix createRotation(float yaw, float pitch, float roll) {
        using namespace std;
        
        Matrix result;
        
        const float theta = pitch;
        const float psi = yaw;
        const float phi = roll;
        
        // going in columns
        result.m[index(0,0)] = cos(theta) * cos(psi);
        result.m[index(1,0)] = cos(theta)*sin(psi);
        result.m[index(2,0)] = -sin(theta);
        
        result.m[index(0,1)] = -cos(phi)*sin(psi) + sin(phi)*sin(theta)*cos(psi);
        result.m[index(1,1)] = cos(phi)*cos(psi) + sin(phi)*sin(theta)*sin(psi);
        result.m[index(2,1)] = sin(phi)*cos(theta);
        
        result.m[index(0,2)] = sin(phi)*sin(psi) + cos(phi)*sin(theta)*cos(psi);
        result.m[index(1,2)] = -sin(phi)*cos(psi) + cos(phi)*sin(theta)*sin(psi);
        result.m[index(2,2)] = cos(phi)*cos(theta);
        
        result.m[index(3,3)] = 1.0f;
        
        return result;
    }
    
    // q must be normalised
    static Matrix createRotation(const Quaternion& q) {
        Matrix result;
        
        // going in columns
        result.m[index(0, 0)] = 1.0f - 2*(q.y*q.y + q.z*q.z);
        result.m[index(1, 0)] = 2*(q.x*q.y + q.w*q.z);
        result.m[index(2, 0)] = 2*(q.x*q.z - q.w*q.y);
        
        result.m[index(0, 1)] = 2*(q.x*q.y - q.w*q.z);
        result.m[index(1, 1)] = 1.0f - 2*(q.x*q.x + q.z*q.z);
        result.m[index(2, 1)] = 2*(q.y*q.z + q.w*q.x);
        
        result.m[index(0, 2)] = 2*(q.x*q.z + q.w*q.y);
        result.m[index(1, 2)] = 2*(q.y*q.z - q.w*q.x);
        result.m[index(2, 2)] = 1.0f - 2*(q.x*q.x + q.y*q.y);
        
        result.m[index(3, 3)] = 1.0f;
        
        return result;
    }
    
    // axis must be normalised
    static Matrix createRotation(const Vector& axis, float angle) {
        Matrix result;
        
        const float s = std::sin(angle);
        const float c = std::cos(angle);
        
        // going in columns
        result.m[index(0, 0)] = c + axis.x*axis.x*(1.0f - c);
        result.m[index(1, 0)] = axis.y*axis.x*(1.0f - c) + axis.z*s;
        result.m[index(2, 0)] = axis.z*axis.x*(1.0f - c) - axis.y*s;
        
        result.m[index(0, 1)] = axis.x*axis.y*(1.0f - c) - axis.z*s;
        result.m[index(1, 1)] = c + axis.y*axis.y*(1.0f - c);
        result.m[index(2, 1)] = axis.z*axis.y*(1.0f - c) + axis.x*s;
        
        result.m[index(0, 2)] = axis.x*axis.z*(1.0f - c) + axis.y*s;
        result.m[index(1, 2)] = axis.y*axis.z*(1.0f - c) - axis.x*s;
        result.m[index(2, 2)] = c + axis.z*axis.z*(1.0f - c);
        
        return result;
    }
    
};
    
static Matrix operator*(const Matrix& mA, const Matrix& mB) {
    Matrix result;
    
    const float* a = mA.m;
    const float* b = mB.m;
    
    result.m[0] = a[0]*b[0] + a[4]*b[1] + a[8]*b[2] + a[12]*b[3];
    result.m[1] = a[1]*b[0] + a[5]*b[1] + a[9]*b[2] + a[13]*b[3];
    result.m[2] = a[2]*b[0] + a[6]*b[1] + a[10]*b[2] + a[14]*b[3];
    result.m[3] = a[3]*b[0] + a[7]*b[1] + a[11]*b[2] + a[15]*b[3];
    
    result.m[4] = a[0]*b[4] + a[4]*b[5] + a[8]*b[6] + a[12]*b[7];
    result.m[5] = a[1]*b[4] + a[5]*b[5] + a[9]*b[6] + a[13]*b[7];
    result.m[6] = a[2]*b[4] + a[6]*b[5] + a[10]*b[6] + a[14]*b[7];
    result.m[7] = a[3]*b[4] + a[7]*b[5] + a[11]*b[6] + a[15]*b[7];
    
    result.m[8] = a[0]*b[8] + a[4]*b[9] + a[8]*b[10] + a[12]*b[11];
    result.m[9] = a[1]*b[8] + a[5]*b[9] + a[9]*b[10] + a[13]*b[11];
    result.m[10] = a[2]*b[8] + a[6]*b[9] + a[10]*b[10] + a[14]*b[11];
    result.m[11] = a[3]*b[8] + a[7]*b[9] + a[11]*b[10] + a[15]*b[11];
    
    result.m[12] = a[0]*b[12] + a[4]*b[13] + a[8]*b[14] + a[12]*b[15];
    result.m[13] = a[1]*b[12] + a[5]*b[13] + a[9]*b[14] + a[13]*b[15];
    result.m[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];
    result.m[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];
    
    return result;
}
    
// Implies w == 1
static Vector multiplyPoint(const Matrix& a, const Vector& v) {
    Vector result;
    
    float wInv = 1.0f / a.m[15];
    
    result.x = (a.m[0]*v.x + a.m[4]*v.y + a.m[8]*v.z + a.m[12]) * wInv;
    result.y = (a.m[1]*v.x + a.m[5]*v.y + a.m[9]*v.z + a.m[13]) * wInv;
    result.z = (a.m[2]*v.x + a.m[6]*v.y + a.m[10]*v.z + a.m[14]) * wInv;
    
    return result;
}
    
// Implies w == 0;
static Vector multiplyDirection(const Matrix& a, const Vector& v) {
    Vector result;
    
    result.x = a.m[0]*v.x + a.m[4]*v.y + a.m[8]*v.z;
    result.y = a.m[1]*v.x + a.m[5]*v.y + a.m[9]*v.z;
    result.z = a.m[2]*v.x + a.m[6]*v.y + a.m[10]*v.z;
    
    return result;
}
    
// assumes we're multiplying a point
static Vector operator*(const Matrix& m, const Vector& v) {
    return multiplyPoint(m, v);
}

#endif
