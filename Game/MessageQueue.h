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

#include "Util/Array.h"
#include "Util/List.h"
#include "Util/SharedPtr.h"
#include "Util/UniquePtr.h"

enum MessageCategory {
    MESSAGE_CATEGORY_SYSTEM,
    MESSAGE_CATEGORY_KEYBOARD,
    MESSAGE_CATEGORY_MOUSE,
    
    MESSAGE_CATEGORY_ENUM_SIZE
};

typedef void(MessageCallback)();
struct Message {
    MessageCategory category;
    int type;
    int param1;
    int param2;
    
    LIST_LINK(Message) messagesLink;
};

class MessageHandler {
public:
    virtual void handleMessage(const Message& m) = 0;
    
    virtual ~MessageHandler() {}
};

class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    
    void putMessage(UniquePtr<Message> message);
    
    void processMessages();
    
    void registerHandler(SharedPtr<MessageHandler> handler, MessageCategory forCategory);
    
private:
    MessageQueue(const MessageQueue&);
    MessageQueue& operator=(const MessageQueue&);
    
private:
    LIST_DECLARE(Message, messagesLink) mMessages1;
    LIST_DECLARE(Message, messagesLink) mMessages2;
    LIST_PTR(Message)                   mCurrentList;
    
    Array< SharedPtr<MessageHandler> >  mHandlers;
};

#endif /* defined(__Wonderland__MessageQueue__) */
