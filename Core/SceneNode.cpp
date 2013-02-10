//
//  SceneNode.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "SceneNode.h"

#include "Util/Log.h"

SceneNode::SceneNode() : mParent(nullptr) {

}

SceneNode::~SceneNode() {
    if(mParent) {
        unregisterChild(this);
    }
}

void SceneNode::registerChild(SceneNode* child) {
    if(child->getParent()) {
        LOG("Warning - child 0x%p given to %s already has parent 0x%p", child, __PRETTY_FUNCTION__, child->getParent());
        child->getParent()->unregisterChild(child);
    }
    
    child->mParent = this;
    mChildren.add(child);

    child->transform.setDirty();
}

void SceneNode::unregisterChild(SceneNode* child) {
    mChildren.erase(child);
    child->mParent = nullptr;
}

SceneNode* SceneNode::getParent() {
    return mParent;
}