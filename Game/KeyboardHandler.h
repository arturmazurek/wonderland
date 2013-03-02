//
//  KeyboardHandler.h
//  Wonderland
//
//  Created by Artur Mazurek on 02.03.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__KeyboardHandler__
#define __Wonderland__KeyboardHandler__

#include "KeyCodes.h"
#include "MessageQueue.h"

// key codes go as param1

class KeyboardHandler : public MessageHandler {
public:
    enum TYPE {
        KEY_ACTION_PRESSED,
        KEY_ACTION_RELEASED
    };
    
    KeyboardHandler();
    ~KeyboardHandler();
    
    bool isPressed(KeyCode keyCode) const;
    
    virtual void handleMessage(const Message& message);
    
private:
    bool mKeys[KEY_ENUM_SIZE];
};

#endif /* defined(__Wonderland__KeyboardHandler__) */
