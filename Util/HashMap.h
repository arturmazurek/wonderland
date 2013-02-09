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

template <class DataT>
class HashMap {
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
        typedef typename google::dense_hash_map<const char *, T, std::hash<const char*> >::iterator IteratorType;
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
    google::dense_hash_map<const char*, DataT, std::hash<const char*> > mMap;
};

#endif
