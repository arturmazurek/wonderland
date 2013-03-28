//
//  HashMap.h
//  Wonderland
//
//  Created by Artur Mazurek on 08.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_HashMap_h
#define Wonderland_HashMap_h

#include "External/sparsehash/dense_hash_map"

#include "Log.h"
#include "String.h"



template <class DataT>
class HashMap {
private:
    struct HashString {
        size_t operator()(const char *s) const {
            if(!s) {
                return 0;
            }
            
            size_t hash = 0;
            for(int i = 0; s[i] != 0; ++i) {
                hash = 65599 * hash + s[i];
            }
            return hash ^ (hash >> 16);
        }
    };
    
public:
    HashMap() {
        mMap.set_empty_key(nullptr);
    }
    
    DataT& operator[](const char* key) {
        return mMap[key];
    }
    
    const DataT& operator[](const char* key) const {
        return mMap[key];
    }
    
    template <class T>
    class HashMapIterator {
    public:
        bool hasNext() {
            return mCurrent != mEnd;
        }
        
        T& next() {
            assert(mCurrent != mEnd && "This assert means you're out of bounds");
            if(mCurrent == mEnd) {
                static T empty;
                return empty;
            }
        
            IteratorType temp = mCurrent;
            ++mCurrent;
            return temp->second;
        }
        
    private:
        template <typename U> friend class HashMap;
        typedef typename google::dense_hash_map<const char *, T, HashString >::iterator IteratorType;
        IteratorType mCurrent;
        IteratorType mEnd;
    };
    
    typedef HashMapIterator<DataT> Iterator;
    
    Iterator iterator() {
        Iterator result;
        result.mCurrent = mMap.begin();
        result.mEnd = mMap.end();
        return result;
    }

private:
    google::dense_hash_map<const char*, DataT, HashString > mMap;
};

#endif
