//
//  HandleManager.h
//  Wonderland
//
//  This file is taken from Scott Bilas's blog (scottbilas.com)
//

#ifndef Wonderland_HandleManager_h
#define Wonderland_HandleManager_h

#include <cassert>

#include "Array.h"
#include "Log.h"
#include "StaticAssert.h"

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
    
    HandleT acquire(const ManagedT& managed) {
//    ManagedT* acquire(HandleT& handle) {
        unsigned index = 0;
        HandleT result;
        
        if(mFreeSlots.empty()) {
            index = mMagicNumbers.size();
            result.init(index);
            mUserData.add(managed);
            mMagicNumbers.add(result.magic());
        } else {
            index = mFreeSlots.last();
            result.init(index);
            mFreeSlots.removeLast();
            mMagicNumbers[index] = result.magic();
        }
        
        return result;
    }
    
    void release(const HandleT& handle) {
        unsigned index = handle.index();
        
        assert(index < mUserData.size());
        assert(mMagicNumbers[index] == handle.magic());
        
        mMagicNumbers[index] = 0;
        mFreeSlots.add(index);
    }
    
    ManagedT dereference(const HandleT& handle) {
        if(handle.isNull()) {
            return ManagedT();
        }
        
        unsigned index = handle.index();
        if(index >= mUserData.size() || mMagicNumbers[index] != handle.magic()) {
            LOG("Trying to dereference invalid handle");
            return ManagedT();
        }
        
        return mUserData[index];
    }
    
    const ManagedT* dereference(const HandleT& handle) const {
        return const_cast< HandleManager<HandleT, ManagedT>& >(*this).dereference(handle);
    }
    
private:
    Array<ManagedT> mUserData;
    Array<unsigned> mMagicNumbers;
    Array<unsigned> mFreeSlots;
};

#endif
