//
//  SystemHandler.h
//  Wonderland
//
//  Created by Artur Mazurek on 02.03.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__SystemHandler__
#define __Wonderland__SystemHandler__

#include "MessageQueue.h"

class Renderer;

class SystemHandler : public MessageHandler {
public:
    enum Type {
        TYPE_SCREEN_RESIZE,
        
        TYPE_ENUM_SIZE
    };
    
    SystemHandler(Renderer* renderer);
    ~SystemHandler();
    
    virtual void handleMessage(const Message& m) override;
    
private:
    Renderer* mRenderer;
};

#endif /* defined(__Wonderland__SystemHandler__) */
