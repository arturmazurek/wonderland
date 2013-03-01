//
//  SystemInterface.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 01/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "SystemInterface.h"

#include "MessageQueue.h"

SystemInterface::SystemInterface(MessageQueue* queue) : mQueue(queue) {
    
}

SystemInterface::~SystemInterface() {
    
}

void SystemInterface::windowResized(int newWidth, int newHeight) {
    
}

void SystemInterface::keyPressed(int keyCode) {
    
}

void SystemInterface::keyReleased(int keyCode) {
    
}

void SystemInterface::mouseMoved(int newWindowX, int newWindowY) {
    
}

void SystemInterface::mousePressed(int mouseKey) {
    
}

void SystemInterface::mouseReleased(int mouseKey) {
    
}

void SystemInterface::mouseWheelScrolled(float amount) {
    
}