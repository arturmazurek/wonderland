//
//  GameObject.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "GameObject.h"

unsigned GameObject::sIdCounter(0);

GameObject::GameObject() : mId(sIdCounter++), toDelete(false) {
    
}

GameObject::~GameObject() {
    mComponents.DeleteAll();
}

unsigned GameObject::objectId() const {
    return mId;
}

void GameObject::addChild(GameObject* child) {
    registerChild(child);
    child->transform.setDirty();
}

void GameObject::removeFromParent() {
    mParent->unregisterChild(this);
}

void GameObject::update(float timeInSeconds) {
    ComponentBase* component = mComponents.Head();
    while(component) {
        component->update(timeInSeconds, this);
        component = mComponents.Next(component);
    }
}