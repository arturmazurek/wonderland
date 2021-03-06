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
    explicit SharedPtr(T* ptr = nullptr) : mPtr(ptr), mCounter(nullptr) {
        if(mPtr) {
            mCounter = new Counter();
            increase();
        }
    }
    
    ~SharedPtr() {
        decrease();
    }
    
    SharedPtr(const SharedPtr& other) : mCounter(other.mCounter), mPtr(other.mPtr) {
        increase();
    }
    
    template <typename U> friend class SharedPtr;
    
    template <typename U>
    SharedPtr(const SharedPtr<U>& other) : mCounter(reinterpret_cast<SharedPtr<T>::Counter*>(other.mCounter)), mPtr(other.mPtr) {
        increase();
    }
    
    SharedPtr& operator=(const SharedPtr& other) {
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
inline bool operator==(const SharedPtr<T1>& t1, const SharedPtr<T2>& t2) {
    return t1.get() == t2.get();
}

template <typename T1, typename T2>
inline bool operator!=(const SharedPtr<T1>& t1, const SharedPtr<T2>& t2) {
    return !(t1 == t2);
}

template <typename T>
bool operator==(const SharedPtr<T>& p1, T* p2) {
    return p1.get() == p2;
}

template <typename T>
bool operator==(T* p2, const SharedPtr<T>& p1) {
    return p1 == p2;
}

template <typename T>
bool operator!=(const SharedPtr<T>& p1, T* p2) {
    return !(p1 == p2);
}

template <typename T>
bool operator!=(T* p2, const SharedPtr<T>& p1) {
    return p1 != p2;
}

#endif
