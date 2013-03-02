//
//  KeyboardHandler.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 02.03.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "KeyboardHandler.h"

#include <cstring>

#include "Util/Log.h"
#include "Util/Util.h"

KeyboardHandler::KeyboardHandler() {
    std::memset(mKeys, 0, ARRAY_SIZE(mKeys));
}

KeyboardHandler::~KeyboardHandler() {
    
}

void KeyboardHandler::handleMessage(const Message& message) {
    if(message.param1 >= KEY_ENUM_SIZE) {
        LOG("Key code unsupported yet - %d", message.param1);
        return;
    }
    
    if(message.type == KEY_ACTION_PRESSED) {
        LOG("Pressed key - %d", message.param1);
        mKeys[message.param1] = true;
    } else {
        LOG("Released key - %d", message.param1);
        mKeys[message.param1] = false;
    }
}

bool KeyboardHandler::isPressed(KeyCode keyCode) const {
    return mKeys[keyCode];
}