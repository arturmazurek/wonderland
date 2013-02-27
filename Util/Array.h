//
//  Array.h
//  Wonderland
//
//  Created by Artur Mazurek on 26/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Array_h
#define Wonderland_Array_h

#include <cassert>
#include <cstring>

template <typename T>
class Array {
public:
    Array(int size = 10, int grow = 10) : mGrow(grow), mObjs(nullptr), mUsed(0), mSize(size) {
        mObjs = new T[size];
    }
    
    Array(const Array& other) : mGrow(other.mGrow), mObjs(nullptr), mUsed(other.mUsed), mSize(other.mSize) {
        mObjs = new T[mSize];
        for(int i = 0; i < mUsed; ++i) {
            mObjs[i] = other.mObjs[i];
        }
    }
    
    Array& operator=(const Array& other) {
        delete[] mObjs;
        mGrow = other.mGrow;
        mSize = other.mSize;
        mUsed = other.mUsed;
        
        mObjs = new T[mSize];
        for(int i = 0; i < mUsed; ++i) {
            mObjs[i] = other.mObjs[i];
        }
    }
    
    ~Array() {
        delete[] mObjs;
    }
    
    T& operator[](int i) {
        assert(i < mSize);
        mUsed = i+1 > mUsed ? i+1 : mUsed;
        return mObjs[i];
    }
    
    const T& operator[](int i) const {
        return mObjs[i];
    }
    
    int size() const {
        return mSize;
    }
    
    void add(const T& t) {
        if(mUsed + 1 >= mSize) {
            mSize += mGrow;
            T* temp = new T[mSize];
            for(int i = 0; i < mUsed; ++i) {
                temp[i] = mObjs[i];
            }
            delete[] mObjs;
            mObjs = temp;
        }
        
        mObjs[mUsed] = t;
        ++mUsed;
    }
    
private:
    int mGrow;
    T*  mObjs;
    int mUsed;
    int mSize;
};

#endif
