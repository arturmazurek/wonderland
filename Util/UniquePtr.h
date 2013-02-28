//
//  UniquePtr.h
//  Wonderland
//
//  Created by Artur Mazurek on 24.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_UniquePtr_h
#define Wonderland_UniquePtr_h

#include "Log.h"

template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* obj = nullptr) : mPtr(obj) {
    }
    
    template <typename U>
    explicit UniquePtr(U* obj = nullptr) : mPtr(obj) { 
    }
    
    UniquePtr(const UniquePtr& other) : mPtr(const_cast<UniquePtr&>(other).release()) {
    }
    
    template <typename U>
    UniquePtr(const UniquePtr<U>& other) : mPtr(const_cast<UniquePtr&>(other).release())  {
    }
    
    UniquePtr& operator=(const UniquePtr& other) {
        mPtr = const_cast<UniquePtr&>(other).release();
        return *this;
    }
    
    template <typename U>
    UniquePtr& operator=(const UniquePtr<U>& other) {
        mPtr = const_cast<UniquePtr<U>&>(other).release();
        return *this;
    }
    
    ~UniquePtr() {
        delete mPtr;
    }
    
    void reset(T* obj = nullptr) {
        delete mPtr;
        mPtr = obj;
    }
    
    T* release() {
        T* temp = mPtr;
        mPtr = nullptr;
        return temp;
    }
    
    T* get() const {
        return mPtr;
    }
    
    operator bool() const {
        return mPtr != nullptr;
    }
    
    T* operator->() const {
        return mPtr;
    }
    
    T& operator*() {
        return *mPtr;
    }
    
    const T& operator*() const {
        return *mPtr;
    }
    
private:
    T *mPtr;
};

template <typename T1, typename T2>
inline bool operator==(const UniquePtr<T1>& p1, const UniquePtr<T2>& p2) {
    return p1.get() == p2.get();
}

template <typename T1, typename T2>
inline bool operator!=(const UniquePtr<T1>& p1, const UniquePtr<T2>& p2) {
    return !(p1 == p2);
}

#endif
