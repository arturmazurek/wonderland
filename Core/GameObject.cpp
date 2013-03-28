//
//  GameObject.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "GameObject.h"

#include "Util/Log.h"

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
        component->update(timeInSeconds);
        component = mComponents.Next(component);
    }
}

void GameObject::addComponent(ComponentBase* component) {
    if(hasComponent(component)) {
        LOG("Already added component 0x%p to object 0x%p (%u) of type %d", component, this, objectId(), component->type());
        return;
    }
    mComponents.InsertTail(component);
    component->setOwner(this);
}

bool GameObject::hasComponent(const ComponentBase* component) const {
    const ComponentBase* c = mComponents.Head();
    while(c) {
        if(c == component) {
            return true;
        }
        c = mComponents.Next(c);
    }
    return false;
}

void GameObject::getComponents(LinkedList<ComponentBase*>& result, ComponentBase::Type type) {
    ComponentBase* component = mComponents.Head();
    while(component) {
        if(component->type() == type) {
            result.add(component);
        }
        component = mComponents.Next(component);
    }
}