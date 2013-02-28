//
//  SharedArray.h
//  Wonderland
//
//  Created by Artur Mazurek on 24.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_SharedArray_h
#define Wonderland_SharedArray_h

template <typename T>
class SharedArray {
public:
    explicit SharedArray(T* ptr = nullptr) : mPtr(ptr), mCounter(nullptr) {
        if(mPtr) {
            mCounter = new Counter();
            increase();
        } 
    }
    
    ~SharedArray() {
        decrease();
    }
    
    SharedArray(const SharedArray& other) : mCounter(other.mCounter), mPtr(other.mPtr) {
        increase();
    }
    
    SharedArray& operator=(const SharedArray& other) {
        decrease();
        mPtr = other.mPtr;
        mCounter = other.mCounter;
        
        increase();
        
        return *this;
    }
    
    void reset(T* ptr = nullptr) {
        decrease();
        mPtr = ptr;
        if(mPtr) {
            mCounter = new Counter();
            increase();
        } else {
            mPtr = nullptr;
        }
    }
    
    T* get() const {
        return mPtr;
    }
    
    T* operator->() const {
        return mPtr;
    }
    
    T& operator*() const {
        return *mPtr;
    }
    
    unsigned short useCount() const {
        if(!mCounter) {
            return 0;
        } else {
            return mCounter->refs;
        }
    }
    
    bool unique() const {
        return useCount() == 1;
    }
    
    operator bool() const {
        return mPtr != nullptr;
    }
    
    T& operator[](unsigned i) {
        return mPtr[i];
    }
    
    const T& operator[](unsigned i) const {
        return mPtr[i];
    }
    
private:
    void decrease() {
        if(!mCounter) {
            return;
        }
        
        --mCounter->refs;
        
        if(mCounter->refs == 0) {
            delete mPtr;
            delete mCounter;
        }
    }
    
    void increase() {
        if(mCounter) {
            ++mCounter->refs;
        }
    }
    
    struct Counter {
        Counter() : refs(0) {}
        unsigned short refs;
    };
    
    Counter*    mCounter;
    T*          mPtr;
};

template <typename T1, typename T2>
inline bool operator==(const SharedArray<T1>& t1, const SharedArray<T2>& t2) {
    return t1.get() == t2.get();
}

template <typename T1, typename T2>
inline bool operator!=(const SharedArray<T1>& t1, const SharedArray<T2>& t2) {
    return !(t1 == t2);
}

#endif
