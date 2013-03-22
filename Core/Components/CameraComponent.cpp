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

CameraComponent::CameraComponent(Renderer* renderer) : mRenderer(renderer), mCamera(new Camera()) {
    
}

CameraComponent::~CameraComponent() {
    
}

void CameraComponent::update(float dt, GameObject* owner) {
    if(!owner->transformUpdated) {
        return;
    }
    
    updateViewTransform(owner->transform);
}

void CameraComponent::useCamera() {
    mRenderer->useCamera(mCamera);
}

void CameraComponent::updateViewTransform(const Transform& transform) {
    Matrix m = Matrix::createTranslation(-transform.pos());
    
    mCamera->setView(m);
}