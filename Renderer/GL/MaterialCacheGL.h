//
//  MaterialCacheGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialCacheGL__
#define __Wonderland__MaterialCacheGL__

#include "Util/HashMap.h"
#include "Util/String.h"

class MaterialGL;
class ShaderCacheGL;

class MaterialCacheGL {
public:
    MaterialCacheGL(const String& basePath);
    ~MaterialCacheGL();

    MaterialGL* getMaterial(const String& name);
    
private:
    MaterialCacheGL(const MaterialCacheGL&);
    MaterialCacheGL& operator=(const MaterialCacheGL&);
    
    MaterialGL* loadMaterial(const String& name);

private:
    const String            mBasePath;
    HashMap<MaterialGL*>    mMaterials;
    ShaderCacheGL*          mShaderCache;
};

#endif /* defined(__Wonderland__MaterialCacheGL__) */
