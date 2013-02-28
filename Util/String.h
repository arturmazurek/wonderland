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
    String(const char* str = nullptr) {
        if(str) {
            makeCopy(str);
        }
    }
    
    ~String() {
    }
    
    
    String(const String& other) : mStr(other.mStr) {
    }
    
    String& operator=(const String& other) {
        mStr = other.mStr;
        return *this;
    }
    
    String& operator=(const char* str) {
        makeCopy(str);
        return *this;
    }
    
    int size() const {
        if(!mStr) {
            return 0;
        }
        return (int)std::strlen(mStr.get());
    }
    
    bool empty() const {
        return size() == 0;
    }
    
    char operator[](int i) const {
        assert(i < std::strlen(mStr.get()));
        return mStr[i];
    }
    
    char& operator[](int i) {
        assert(i < std::strlen(mStr.get()));
        
        if(mStr.unique()) {
            return mStr[i];
        }
        
        makeCopy(mStr.get());
        
        return mStr[i];
    }
    
    const char* data() const {
        return mStr.get();
    }
    
    operator bool() const {
        return mStr.get() != nullptr;
    }
    
    String& operator+=(const String& other) {
        return *this += other.data();
    }

    String& operator+=(const char* str) {
        int strLen = (int)strlen(str);
        int len = size() + strLen;
        SharedArray<char> temp(new char[len + 1]);
        std::memcpy(temp.get(), data(), size());
        std::memcpy(temp.get() + (size_t)(size()), str, strLen);
        temp[len] = '\0';
        mStr = temp;
        
        return *this;
    }

private:
    void makeCopy(const char* buffer) {
        int len = (int)std::strlen(buffer);
        mStr.reset(new char[len + 1]);
        std::memcpy(mStr.get(), buffer, len);
        mStr[len] = '\0';
    }
    
private:
    SharedArray<char> mStr;
};

inline String operator+(const String& a, const String& b) {
    String result(a);
    result += b;
    return result;
}

inline String operator+(const char* a, const String& b) {
    return String(a) + b;
}

inline String operator+(const String& a, const char* b) {
    return a + String(b);
}

inline bool operator==(const String& a, const String& b) {
    return std::strcmp(a.data(), b.data());
}

inline bool operator==(const char* a, const String& b) {
    return String(a) == b;
}

inline bool operator==(const String& a, const char* b) {
    return a == String(b);
}

#endif
