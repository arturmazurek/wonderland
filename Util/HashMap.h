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
    
private:
    google::dense_hash_map<const char*, DataT, std::hash<const char*> > mMap;
};

#endif
