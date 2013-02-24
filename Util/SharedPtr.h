//
//  SharedPtr.h
//  Wonderland
//
//  Created by Artur Mazurek on 24.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_SharedPtr_h
#define Wonderland_SharedPtr_h

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* ptr = nullptr) {
        
    }
    
private:
    struct Counter {
        unsigned short count;
    };
    
    T* mPtr;
    Counter* mCounter;
};

#endif
