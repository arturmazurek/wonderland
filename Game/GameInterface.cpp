//
//  GameInterface.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 01/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "GameInterface.h"

#include "KeyboardHandler.h"
#include "KeyCodes.h"
#include "MessageQueue.h"
#include "SystemHandler.h"

GameInterface::GameInterface(MessageQueue* queue) : mQueue(queue) {
    
}

GameInterface::~GameInterface() {
    
}

void GameInterface::windowResized(int newWidth, int newHeight) {
    UniquePtr<Message> m(new Message());
    m->category = MESSAGE_CATEGORY_SYSTEM;
    m->type = SystemHandler::TYPE_SCREEN_RESIZE;
    m->param1 = newWidth;
    m->param2 = newHeight;
    
    mQueue->putMessage(m);
}

void GameInterface::keyPressed(int keyCode) {
    UniquePtr<Message> m(new Message());
    m->category = MESSAGE_CATEGORY_KEYBOARD;
    m->type = KeyboardHandler::KEY_ACTION_PRESSED;
    m->param1 = keyCode;
    
    mQueue->putMessage(m);
}

void GameInterface::keyReleased(int keyCode) {
    UniquePtr<Message> m(new Message());
    m->category = MESSAGE_CATEGORY_KEYBOARD;
    m->type = KeyboardHandler::KEY_ACTION_RELEASED;
    m->param1 = keyCode;
    
    mQueue->putMessage(m);
}

void GameInterface::mouseMoved(int newWindowX, int newWindowY) {
    
}

void GameInterface::mousePressed(int mouseKey) {
    
}

void GameInterface::mouseReleased(int mouseKey) {
    
}

void GameInterface::mouseWheelScrolled(float amount) {
    
}