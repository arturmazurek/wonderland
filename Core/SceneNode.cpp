//
//  SceneNode.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "SceneNode.h"

#include "Util/Log.h"

SceneNode::SceneNode() : mDirty(false), mParent(nullptr) {

}

SceneNode::~SceneNode() {
    while(mFirstChild) {
        SceneNode* node = mFirstChild;
        mFirstChild = mFirstChild->mSiblings;
        delete node;
    }
}

void SceneNode::registerChild(SceneNode* child) {
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