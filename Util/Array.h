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
        
        return *this;
    }
    
    ~Array() {
        delete[] mObjs;
    }
    
    void reserve(int n) {
        if(n <= mUsed) {
            return;
        }
        while(n > mSize) {
            grow();
        }
        
        mUsed = n;
        
        for(int i = 0; i < n; ++i) {
            mObjs[i] = T();
        }
    }
    
    T& operator[](int i) {
        assert(i < size());
        return mObjs[i];
    }
    
    const T& operator[](int i) const {
        assert(i < size());
        return mObjs[i];
    }
    
    T& last() {
        return (*this)[size()-1];
    }
    
    const T& last() const {
        return (*this)[size()-1];
    }
    
    bool empty() const {
        return size() == 0;
    }
    
    int size() const {
        return mUsed;
    }
    
    void add(const T& t) {
        if(mUsed + 1 >= mSize) {
            grow();
        }
        
        mObjs[mUsed] = t;
        ++mUsed;
    }
    
    void removeLast() {
        --mUsed;
    }
    
private:
    void grow() {
        mSize += mGrow;
        T* temp = new T[mSize];
        for(int i = 0; i < mUsed; ++i) {
            temp[i] = mObjs[i];
        }
        delete[] mObjs;
        mObjs = temp;
    }
    
private:
    int mGrow;
    T*  mObjs;
    int mUsed;
    int mSize;
};

#endif
