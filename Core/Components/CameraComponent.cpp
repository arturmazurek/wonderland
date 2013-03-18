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

CameraComponent::CameraComponent() : mCamera(new Camera()) {
    
}

CameraComponent::~CameraComponent() {
    
}

void CameraComponent::update(float dt, GameObject* owner) {
    if(!owner->transform.dirty()) {
        return;
    }
    

}

Camera* CameraComponent::camera() {
    return mCamera.get();
}

const Camera* CameraComponent::camera() const {
    return mCamera.get();
}

