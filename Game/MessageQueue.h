//
//  MessageQueue.h
//  Wonderland
//
//  Created by Artur Mazurek on 28/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MessageQueue__
#define __Wonderland__MessageQueue__

#include "Util/List.h"

typedef void(MessageCallback)();
struct Message {
    int type;
    MessageCallback callback;
    void* data;
    
    LIST_LINK(Message) messagesLink;
};

class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    
private:
    MessageQueue(const MessageQueue&);
    MessageQueue& operator=(const MessageQueue&);
    
private:
    LIST_DECLARE(Message, messagesLink) mMessages;
};

#endif /* defined(__Wonderland__MessageQueue__) */
