//
//  Camera.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 15/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Camera.h"

#include "Math/Math.h"

static const float DEFAULT_NEAR = -1.f;
static const float DEFAULT_FAR = 10.f;
static const float DEFAULT_WIDTH = 100.f;
static const float DEFAULT_HEIGHT = 100.f;

Camera::Camera() :
mProjection(Matrix::createIdentity()), mView(Matrix::createIdentity()), mNear(DEFAULT_NEAR), mFar(DEFAULT_FAR), mPerspective(false), mFovY(Math::toRad(45.f)), mAspect(1), mWidth(DEFAULT_WIDTH), mHeight(DEFAULT_HEIGHT) {
    
    calculateProjection();
}

Camera::~Camera() {
    
}

void Camera::setClipPlanes(float near, float far) {
    mNear = near;
    mFar = far;
    
    calculateProjection();
}

void Camera::setPerspective(float fovY, float aspect) {
    mPerspective = true;
    
    mFovY = fovY;
    mAspect = aspect;
    
    calculateProjection();
}

void Camera::setOrtho(float width, float height) {
    mPerspective = false;
    
    mWidth = width;
    mHeight = height;
    
    calculateProjection();
}

void Camera::calculateProjection() {
    if(mPerspective) {
        mProjection = Matrix::createPerspective(mFovY, mAspect, mNear, mFar);
    } else {
        mProjection = Matrix::createOrtho(mWidth, mHeight, mNear, mFar);
    }
}

const Matrix& Camera::projection() const {
    return mProjection;
}

bool Camera::isPerspective() const {
    return mPerspective;
}

float Camera::fov() const {
    return mFovY;
}

const Matrix& Camera::view() const {
    return mView;
}

void Camera::setView(const Matrix& view) {
    mView = view;
}