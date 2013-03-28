//
//  Rotator.h
//  Wonderland
//
//  Created by Artur Mazurek on 20/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Rotator_h
#define Wonderland_Rotator_h

#include <cmath>

#include "Math.h"
#include "Quaternion.h"
#include "Vector.h"

class Rotator {
public:
    Rotator() {};
    
    Rotator(float yaw, float pitch, float roll) {
        setEulerAngles(yaw, pitch, roll);
    }
    
    Rotator(const Vector& axis, const float angle) {
        setAxisRotation(axis, angle);
    }
    
    Rotator(const Quaternion& q) : mQ(q) {        
    }
    
    void setRotation(const Quaternion& q) {
        mQ = q;
    }
    
    const Quaternion& quaternion() const {
        return mQ;
    }
    
    void setYaw(float y) {
        setEulerAngles(y, pitch(), roll());
    }
    
    void setPitch(float p) {
        setEulerAngles(yaw(), p, roll());
    }
    
    void setRoll(float r) {
        setEulerAngles(yaw(), pitch(), r);
    }
    
    float yaw() const {
        // yaw is psi
        return std::atan2(2*(mQ.w*mQ.z + mQ.x*mQ.y), 1.0f - 2*(mQ.y*mQ.y + mQ.z*mQ.z));
    }
    
    float pitch() const {
        // pitch is theta
        return std::asin(2*(mQ.w*mQ.y - mQ.x*mQ.z));
    }
    
    float roll() const {
        // roll is phi
        return std::atan2(2*(mQ.w*mQ.x + mQ.y*mQ.z), 1.0f - 2*(mQ.x*mQ.x + mQ.y*mQ.y));
    }
    
    void setEulerAngles(float yaw, float pitch, float roll) {
        using namespace std;
        
        const float cTheta = cos(pitch * 0.5f);
        const float sTheta = sin(pitch * 0.5f);
        const float cPhi = cos(roll * 0.5f);
        const float sPhi = sin(roll * 0.5f);
        const float cPsi = cos(yaw * 0.5f);
        const float sPsi = sin(yaw * 0.5f);
        
        mQ.w = cPhi*cTheta*cPsi + sPhi*sTheta*sPsi;
        mQ.x = sPhi*cTheta*cPsi - cPhi*sTheta*sPsi;
        mQ.y = cPhi*sTheta*cPsi + sPhi*cTheta*sPsi;
        mQ.z = cPhi*cTheta*sPsi - sPhi*sTheta*cPsi;
        
        mQ.normalize();
    }
    
    void eulerAngles(float& y, float& p, float& r) const {
        y = yaw();
        p = pitch();
        r = roll();
    }
    
    void setAxisRotation(Vector axis, float angle) {
        axis.normalize();
        axis *= std::sin(angle * 0.5f);
        
        mQ.x = axis.x;
        mQ.y = axis.y;
        mQ.z = axis.z;
        mQ.w = std::cos(angle * 0.5f);
        
        mQ.normalize();
    }
    
    void axisRotation(Vector& axis, float& angle) {
        angle = std::acos(mQ.w);
        
        float s = std::sqrt(1 - mQ.w*mQ.w);
        if(s < Math::EPSILON) {
            axis = Vector(1, 0, 0);
        } else {
            s = 1.0f / s;
            axis = Vector(mQ.x*s, mQ.y*s, mQ.z*s);
        }
    }
    
    Matrix rotationMatrix() const {
        return Matrix::createRotation(mQ);
    }
    
    Rotator inverted() const {
        Rotator result(mQ.inverse());
        return result;
    }
    
    Rotator& inverse() {
        mQ = mQ.inverse();
        return *this;
    }
    
    static Rotator createLookAt(const Vector& newDirection, const Vector& up, const Vector& forward) {
        float angle = dot(newDirection, forward);
        angle = (angle < 0 ? -1.0f : 1.0f) * std::acos(angle);
        
        Vector axis(up);
        if(angle > Math::EPSILON) {
            axis = cross(newDirection, forward);
            axis.normalize();
        }
        
        return Rotator(axis, angle);
    }

private:
    Quaternion mQ;
};

#endif
