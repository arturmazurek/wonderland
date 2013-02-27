//
//  MaterialCacheGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialCacheGL__
#define __Wonderland__MaterialCacheGL__

#include <string>

#include "Renderer/MaterialCache.h"

#include "Util/HashMap.h"

class MaterialGL;
class ShaderCacheGL;

class MaterialCacheGL : public MaterialCache {
public:
    MaterialCacheGL(const std::string& basePath);
    virtual ~MaterialCacheGL();
    
private:
    MaterialCacheGL(const MaterialCacheGL&);
    MaterialCacheGL& operator=(const MaterialCacheGL&);
    
    virtual Material* getMaterial(const std::string& name) override;
    MaterialGL* loadMaterial(const std::string& name);

private:
    const std::string       mBasePath;
    HashMap<MaterialGL*>    mMaterials;
    ShaderCacheGL*          mShaderCache;
};

#endif /* defined(__Wonderland__MaterialCacheGL__) */
