//
//  StaticMeshComponent.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "StaticMeshComponent.h"

#include "StaticMesh.h"

StaticMeshComponent::StaticMeshComponent() {
    
}

StaticMeshComponent::~StaticMeshComponent() {
    
}

void StaticMeshComponent::update(float dt, GameObject* owner) {
    
}

StaticMesh* StaticMeshComponent::getMesh() {
    return mStaticMesh;
}

void StaticMeshComponent::setMesh(StaticMesh* mesh) {
    mStaticMesh = mesh;
}