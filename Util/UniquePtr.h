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
    explicit UniquePtr(T* obj = nullptr) : mObj(obj) {
    }
    
    UniquePtr(const UniquePtr& other) : mObj(const_cast<UniquePtr&>(other).release()) {
    }
    
    template <typename U>
    UniquePtr(const UniquePtr<U>& other) : mObj(const_cast<UniquePtr&>(other).release())  {
    }
    
    UniquePtr& operator=(const UniquePtr& other) {
        mObj = const_cast<UniquePtr&>(other).release();
        return *this;
    }
    
    template <typename U>
    UniquePtr& operator=(const UniquePtr<U>& other) {
        mObj = const_cast<UniquePtr&>(other).release();
        return *this;
    }
    
    ~UniquePtr() {
        delete mObj;
    }
    
    void reset(T* obj = nullptr) {
        delete mObj;
        mObj = obj;
    }
    
    T* release() {
        T* temp = mObj;
        mObj = nullptr;
        return temp;
    }
    
    T* get() {
        return mObj;
    }
    
    void swap(UniquePtr& other) {
        T* temp = mObj;
        mObj = other.mObj;
        other.mObj = temp;
    }
    
    operator bool() const {
        return mObj != nullptr;
    }
    
    T* operator->() const {
        return mObj;
    }
    
    T& operator*() {
        return *mObj;
    }
    
    const T& operator*() const {
        return *mObj;
    }
    
private:
    T *mObj;
};

template <typename T1, typename T2>
bool operator==(const UniquePtr<T1>& p1, const UniquePtr<T2>& p2) {
    return p1.get() == p2.get();
}

template <typename T1, typename T2>
bool operator!=(const UniquePtr<T1>& p1, const UniquePtr<T2>& p2) {
    return !(p1 == p2);
}

#endif
