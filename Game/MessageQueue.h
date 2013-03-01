//
//  MessageQueue.h
//  Wonderland
//
//  Created by Artur Mazurek on 28/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MessageQueue__
#define __Wonderland__MessageQueue__

#include <cstdint>

#include "Util/List.h"
#include "Util/UniquePtr.h"

enum MessageCategory {
    MESSAGE_CATEGORY_SYSTEM,
    MESSAGE_CATEGORY_KEYBOARD,
    MESSAGE_CATEGORY_MOUSE
};

typedef void(MessageCallback)();
struct Message {
    MessageCategory type;
    int param1;
    int param2;
    
    LIST_LINK(Message) messagesLink;
};

class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    
    void putMessage(UniquePtr<Message> message);
    
    void processMessages();
    
private:
    MessageQueue(const MessageQueue&);
    MessageQueue& operator=(const MessageQueue&);
    
private:
    LIST_DECLARE(Message, messagesLink) mMessages;
};

#endif /* defined(__Wonderland__MessageQueue__) */
