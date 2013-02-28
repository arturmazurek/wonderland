//
//  String.h
//  Wonderland
//
//  Created by Artur Mazurek on 28/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_String_h
#define Wonderland_String_h

#include "SharedArray.h"

#include <cassert>
#include <cstring>

class String {
public:
    String() {
    }
    
    ~String() {
    }
    
    explicit String(const char* buf) {
        
    }
    
    String(const String& other) : mBuffer(other.mBuffer) {
    }
    
    String& operator=(const String& other) {
        mBuffer = other.mBuffer;
        return *this;
    }
    
    int size() const {
        if(!mBuffer) {
            return 0;
        }
        return std::strlen(mBuffer.get());
    }
    
    char operator[](int i) const {
        assert(i < std::strlen(mBuffer.get()));
        return mBuffer[i];
    }
    
    char& operator[](int i) {
        assert(i < std::strlen(mBuffer.get()));
        
        if(mBuffer.unique()) {
            return mBuffer[i];
        }
        
        makeCopy(mBuffer.get());
    }
    
    const char* data() const {
        return mBuffer.get();
    }
    
    operator bool() const {
        return mBuffer.get() != nullptr;
    }
    
    String& operator+=(const String& other) {
        int len = size() + other.size();
        SharedPtr<char> temp(new char[len + 1]);
        std::memcpy(temp.get(), data(), size());
        std::memcpy(temp.get() + (size_t)(size()), other.data(), other.size());
        temp[len] = '\0';
        mBuffer = temp;

        return *this;
    }

    String& operator+=(const char* data) {
        makeCopy(data);
        return *this;
    }

private:
    void makeCopy(const char* buffer) {
        int len = std::strlen(buffer);
        mBuffer.reset(new char[len + 1]);
        std::memcpy(mBuffer.get(), buf, len);
        mBuffer[len] = '\0';
    }
    
private:
    SharedArray<char> mBuffer;
};

inline String operator+(const String& a, const String& b) {
    String result(a);
    a += b;
    return a;
}

inline String operator+(const char* a, const String& b) {
    return String(a) + b;
}

inline String operator+(const String& a, const char* b) {
    return a + String(b);
}

inline bool operator==(const String& a, const String& b) {
    return std::strcmp(a.get(), b.get();
}

inline bool operator==(const char* a, const String& b) {
    return String(a) == b;
}

inline bool operator==(const String& a, const char* b) {
    return a == String(b);
}

#endif
