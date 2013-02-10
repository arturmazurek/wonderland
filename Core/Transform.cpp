//
//  Transform.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Transform.h"

#include "Util/Log.h"

Transform::Transform() : mDirty(false), mFrame(Matrix::createIdentity()) {
}

Transform::~Transform() {

}

const Vector& Transform::pos() const {
    return mPosition;
}

void Transform::setPos(const Vector& pos) {
    mPosition = pos;
    mDirty = true;
}

float Transform::scale() const {
    if(mScale.x != mScale.y || mScale.x != mScale.z) {
        LOG("Different scales %f, %f, %f, returning x", mScale.x, mScale.y, mScale.z);
    }
    return mScale.x;
}

void Transform::setScale(float s) {
    mScale.x = mScale.y = mScale.z = s;
    mDirty = true;
}

float Transform::scaleX() const {
    return mScale.x;
}

float Transform::scaleY() const {
    return mScale.y;
}

float Transform::scaleZ() const {
    return mScale.z;
}

void Transform::setScaleX(float sx) {
    mScale.x = sx;
    mDirty = true;
}

void Transform::setScaleY(float sy) {
    mScale.y = sy;
    mDirty = true;
}

void Transform::setScaleZ(float sz) {
    mScale.z = sz;
    mDirty = true;
}

bool Transform::dirty() const {
    return mDirty;
}

void Transform::setDirty() {
    mDirty = true;
}

void Transform::update(const Transform& parentTransform) {
    mFrame = Matrix::createIdentity();
    mFrame.setScale(mScale.x, mScale.y, mScale.z);
    mFrame.setTranslation(mPosition);
    // also set rotation
    
    // multiply mFrame by parentTransform->mFrame
    
    mDirty = false;
}
