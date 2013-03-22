//
//  Transform.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Transform.h"

#include "Util/Log.h"

Transform::Transform() : mDirty(false), mFrame(Matrix::createIdentity()), mScale(1, 1, 1) {
}

Transform::~Transform() {
}

const Vector& Transform::pos() const {
    return mPosition;
}

void Transform::setPos(const Vector& pos) {
    mPosition = pos;
    setDirty();
}

float Transform::scale() const {
    if(mScale.x != mScale.y || mScale.x != mScale.z) {
        LOG("Different scales %f, %f, %f, returning x", mScale.x, mScale.y, mScale.z);
    }
    return mScale.x;
}

void Transform::setScale(float s) {
    mScale.x = mScale.y = mScale.z = s;
    setDirty();
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
    setDirty();
}

void Transform::setScaleY(float sy) {
    mScale.y = sy;
    setDirty();
}

void Transform::setScaleZ(float sz) {
    mScale.z = sz;
    setDirty();
}

bool Transform::dirty() const {
    return mDirty;
}

void Transform::setDirty() {
    mDirty = true;
}

void Transform::setRotation(const Rotator& rot) {
    mRotation = rot;
    setDirty();
}

const Rotator& Transform::getRotation() const {
    return mRotation;
}

const Matrix& Transform::getMatrix() const {
    if(mDirty) {
        LOG("Asking a dirty transform for its matrix");
    }
    
    return mFrame;
}

void Transform::update(const Transform& parentTransform) {
    mFrame = mRotation.rotationMatrix();
    mFrame = Matrix::createTranslation(mPosition) * mFrame;
    mFrame = Matrix::createScale(mScale.x, mScale.y, mScale.z) * mFrame;

    mFrame = parentTransform.mFrame * mFrame;
    
    mDirty = false;
}
