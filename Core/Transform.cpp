//
//  Transform.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Transform.h"

#include "Util/Log.h"

Transform::Transform(Transform* parent) : mChildren(nullptr), mDirty(true), mParent(parent), mSiblings(nullptr) {
    if(mParent) {
        mParent->addChild(this);
    }
}

Transform::~Transform() {
    removeFromParent();
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

void Transform::updateTransforms() {
    mFrame = Matrix::createIdentity();
    mFrame.setScale(mScale.x, mScale.y, mScale.z);
    mFrame.setTranslation(mPosition);
    
    // multiply by parent's transform
    
    Transform* child = mChildren;
    while(child) {
        child->updateTransforms();
        child = child->mSiblings;
    }
}

void Transform::registerChild(Transform* child) {
    child->mSiblings = mChildren;
    mChildren = child;
}

void Transform::unregisterChild(Transform* child) {
    Transform* node = mChildren;
    while(node) {
        if(node->mSiblings == child) {
            break;
        }
        node = node->mSiblings;
    }
    
    if(!node) {
        LOG("Trying to unregister an unknown child 0x%p from 0x%p", child, this);
        return;
    }
    
    node->mSiblings = child->mSiblings;
    child->mSiblings = nullptr;
}

void Transform::addChild(Transform* child) {
    registerChild(child);
    child->mDirty = true;
}

void Transform::removeFromParent() {
    if(mParent) {
        mParent->unregisterChild(this);
    }
}