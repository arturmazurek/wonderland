//
//  GameInterface.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 01/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "GameInterface.h"

#include "MessageQueue.h"

GameInterface::GameInterface(MessageQueue* queue) : mQueue(queue) {
    
}

GameInterface::~GameInterface() {
    
}

void GameInterface::windowResized(int newWidth, int newHeight) {
    UniquePtr<Message> m(new Message());
    m->type = MESSAGE_CATEGORY_SYSTEM;
    m->param1 = newWidth;
    m->param2 = newHeight;
    
    mQueue->putMessage(m);
}

void GameInterface::keyPressed(int keyCode) {
    
}

void GameInterface::keyReleased(int keyCode) {
    
}

void GameInterface::mouseMoved(int newWindowX, int newWindowY) {
    
}

void GameInterface::mousePressed(int mouseKey) {
    
}

void GameInterface::mouseReleased(int mouseKey) {
    
}

void GameInterface::mouseWheelScrolled(float amount) {
    
}