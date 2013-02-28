//
//  MaterialCache.h
//  Wonderland
//
//  Created by Artur Mazurek on 27.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialCache__
#define __Wonderland__MaterialCache__

#include "Util/HashMap.h"
#include "Util/String.h"

class Material;
class MaterialInstance;

class MaterialCache {
public:
    MaterialCache();
    virtual ~MaterialCache();

    MaterialInstance* getMaterialInstance(const String& name);

protected:
    virtual Material* getMaterial(const String& name) = 0;

private:
    MaterialCache(const MaterialCache&);
    MaterialCache& operator=(const MaterialCache&);

private:
    HashMap<MaterialInstance*> mMaterialInstances;
};

#endif /* defined(__Wonderland__MaterialCache__) */
