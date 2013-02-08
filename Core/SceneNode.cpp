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
    while(mFirstChild) {
        SceneNode* node = mFirstChild;
        mFirstChild = mFirstChild->mSiblings;
        delete node;
    }
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
    
    child->mSiblings = mFirstChild;
    mFirstChild = child;
}

void SceneNode::unregisterChild(SceneNode* child) {
    SceneNode* node = mFirstChild;
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

SceneNode* SceneNode::getParent() {
    return mParent;
}