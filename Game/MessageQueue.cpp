//
//  MessageQueue.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 28/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MessageQueue.h"

#include <cassert>

MessageQueue::MessageQueue() : mCurrentList(&mMessages1), mHandlers(MESSAGE_CATEGORY_ENUM_SIZE) {
    mHandlers.reserve(MESSAGE_CATEGORY_ENUM_SIZE);
}

MessageQueue::~MessageQueue() {
    mMessages1.DeleteAll();
    mMessages2.DeleteAll();
}

void MessageQueue::putMessage(UniquePtr<Message> message) {
    mCurrentList->InsertTail(message.release());
}

void MessageQueue::processMessages() {
    LIST_PTR(Message) toHandle = mCurrentList;
    mCurrentList = mCurrentList == &mMessages1 ? &mMessages2 : &mMessages1;
    
    Message* m = toHandle->Head();
    while(m) {
        if(mHandlers[m->category]) {
            mHandlers[m->category]->handleMessage(*m);
        }
        m = toHandle->Next(m);
    }
    toHandle->DeleteAll();
}

void MessageQueue::registerHandler(SharedPtr<MessageHandler> handler, MessageCategory forCategory) {
    assert(forCategory < MESSAGE_CATEGORY_ENUM_SIZE && forCategory >= 0);
    
    if(mHandlers[forCategory]) {
        LOG("Warning - a handler already registered for category %d", forCategory);
    }
    
    mHandlers[forCategory] = handler;
}