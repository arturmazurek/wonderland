//
//  UniqueArray.h
//  Wonderland
//
//  Created by Artur Mazurek on 24.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_UniqueArray_h
#define Wonderland_UniqueArray_h

template <typename T>
class UniqueArray {
public:
    explicit UniqueArray(T* arr = nullptr) : mPtr(arr) {
    }
    
    UniqueArray(const UniqueArray& other) : mPtr(const_cast<UniqueArray&>(other).release()) {
    }
    
    template <typename U>
    UniqueArray(const UniqueArray<U>& other) : mPtr(const_cast<UniqueArray&>(other).release())  {
    }
    
    UniqueArray& operator=(const UniqueArray& other) {
        mPtr = const_cast<UniqueArray&>(other).release();
        return *this;
    }
    
    template <typename U>
    UniqueArray& operator=(const UniqueArray<U>& other) {
        mPtr = const_cast<UniqueArray&>(other).release();
        return *this;
    }
    
    ~UniqueArray() {
        delete[] mPtr;
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
    
    T& operator*() {
        return *mPtr;
    }
    
    const T& operator*() const {
        return *mPtr;
    }
    
    T& operator[](unsigned i) {
        return mPtr[i];
    }
    
    const T& operator[](unsigned i) const {
        return mPtr[i];
    }
    
private:
    T *mPtr;
};

template <typename T1, typename T2>
bool operator==(const UniqueArray<T1>& p1, const UniqueArray<T2>& p2) {
    return p1.get() == p2.get();
}

template <typename T1, typename T2>
bool operator!=(const UniqueArray<T1>& p1, const UniqueArray<T2>& p2) {
    return !(p1 == p2);
}

#endif
