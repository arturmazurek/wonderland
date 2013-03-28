//
//  CameraComponent.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 18/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "CameraComponent.h"

#include "Core/GameObject.h"

#include "Renderer/Camera.h"
#include "Renderer/Renderer.h"

CameraComponent::CameraComponent(Renderer* renderer) : ComponentBase(), mRenderer(renderer), mCamera(new Camera()) {
    
}

CameraComponent::~CameraComponent() {
    
}

void CameraComponent::update(float dt) {
    if(!owner()->transformUpdated) {
        return;
    }
    
    updateViewTransform(owner()->transform);
}

void CameraComponent::useCamera() {
    mRenderer->useCamera(mCamera);
}

void CameraComponent::updateViewTransform(const Transform& transform) {  
    mCamera->setView(transform.getMatrix().inverted());
}

SharedPtr<Camera> CameraComponent::getCamera() {
    return mCamera;
}

void CameraComponent::lookAt(const Vector& position, const Vector& target, const Vector& up) {
    owner()->transform.setPos(position);
}