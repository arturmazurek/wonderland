//
//  MaterialCache.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 27.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MaterialCache.h"

#include "Util/Log.h"

#include "Material.h"
#include "MaterialInstance.h"

MaterialCache::MaterialCache() {
    
}

MaterialCache::~MaterialCache() {
    HashMap<MaterialInstance*>::Iterator iterator = mMaterialInstances.iterator();
    while(iterator.hasNext()) {
        delete iterator.next();
    }
}

MaterialInstance* MaterialCache::getMaterialInstance(const String& name) {
    if(mMaterialInstances[name.data()]) {
        return mMaterialInstances[name.data()]->clone();
    }
    
    Material* m = getMaterial(name);
    if(!m) {
        LOG("Could not get material %s", name.data());
        return nullptr;
    }
    
    MaterialInstance* instance = new MaterialInstance(m);
    Array<MaterialParam> params = m->createParams();
    m->setDefaults(params);
    instance->assignParameters(params);
    
    mMaterialInstances[name.data()] = instance;
    return instance->clone();
}