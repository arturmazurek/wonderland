//
//  SystemHandler.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 02.03.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "SystemHandler.h"

#include <cassert>

#include "Renderer/Renderer.h"

#include "Util/Log.h"

SystemHandler::SystemHandler(Renderer* renderer) : mRenderer(renderer) {
    
}

SystemHandler::~SystemHandler() {
    
}

void SystemHandler::handleMessage(const Message& message) {
    switch(message.type) {
        case TYPE_SCREEN_RESIZE:
            mRenderer->viewResized(message.param1, message.param2);
            break;
            
        default:
            LOG("System handler - unknown message type - %d", message.type);
            break;
    }
}