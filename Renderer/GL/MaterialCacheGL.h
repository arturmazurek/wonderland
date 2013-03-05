//
//  MaterialCacheGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialCacheGL__
#define __Wonderland__MaterialCacheGL__

#include "Renderer/MaterialCache.h"

#include "Util/HashMap.h"
#include "Util/String.h"
#include "Util/UniquePtr.h"

class MaterialGL;
class ShaderCacheGL;

class MaterialCacheGL : public MaterialCache {
public:
    MaterialCacheGL(const String& basePath);
    virtual ~MaterialCacheGL();
    
private:
    MaterialCacheGL(const MaterialCacheGL&);
    MaterialCacheGL& operator=(const MaterialCacheGL&);
    
    virtual UniquePtr<Material> createMaterial(const String& name) override;
    MaterialGL loadMaterial(const String& name);

private:
    const String            mBasePath;
    ShaderCacheGL*          mShaderCache;
};

#endif /* defined(__Wonderland__MaterialCacheGL__) */
