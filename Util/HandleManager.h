//
//  HandleManager.h
//  Wonderland
//
//  This file is taken from Scott Bilas's blog (scottbilas.com)
//

#ifndef Wonderland_HandleManager_h
#define Wonderland_HandleManager_h

#include <cassert>

#import "StaticAssert.h"


template <typename Tag>
class Handle {
public:
    Handle() : mHandle(0) {
        
    }
    
    void init(unsigned index) {
        assert(isNull());
        assert(index < MAX_INDEX);
        
        static unsigned sMagicCounter = 0;
        if(++sMagicCounter > MAX_MAGIC) {
            sMagicCounter = 1;
        }
        
        mIndex = index;
        mMagic = sMagicCounter;
    }
    
    bool isNull() const {
        return mHandle == 0;
    }
    
    unsigned index() const {
        return mIndex;
    }
    
    unsigned magic() const {
        return mMagic;
    }
    
    unsigned handle() const {
        return mHandle;
    }
    
private:
    enum {
        BITS_INDEX = 16,
        BITS_MAGIC = 16,
        
        MAX_INDEX = (1 << BITS_INDEX) - 1,
        MAX_MAGIC = (1 << BITS_MAGIC) - 1,
    };
    
    union {
        struct {
            unsigned mIndex : BITS_INDEX;
            unsigned mMagic : BITS_MAGIC;
        };
        unsigned mHandle;
    };
    
    StaticAssert(sizeof(unsigned) == 4, "We assume that unsigned int is 32 bits");
};

template <typename Tag>
static inline bool operator==(const Handle<Tag>& a, const Handle<Tag>& b) {
    return a.handle() == b.handle();
}

template <typename Tag>
static inline bool operator!=(const Handle<Tag>& a, const Handle<Tag>& b) {
    return a.handle() != b.handle();
}

template <typename HandleT, typename ManagedT>
class HandleManager {
public:
    HandleManager() {
        
    }
    
    ~HandleManager() {
        
    }
    
    ManagedT* acquire(const HandleT& handle) {
        return nullptr;
    }
    
    void release(const HandleT& handle) {
        
    }
    
    ManagedT* dereference(const HandleT& handle) {
        return nullptr;
    }
    
    const ManagedT* dereference(const HandleT& handle) const {
        return nullptr;
    }
};

#endif
