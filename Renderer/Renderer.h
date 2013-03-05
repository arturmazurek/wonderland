//
//  Renderer.h
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Renderer__
#define __Wonderland__Renderer__

#include "Util/List.h"
#include "Util/String.h"
#include "Util/UniquePtr.h"

class GameObject;
class MaterialCache;
class MaterialInstance;
class StaticMesh;
class Surface;

class Renderer {
public:
    virtual ~Renderer();
    
    virtual void renderFrame() = 0;
    
    virtual UniquePtr<MaterialInstance> createMaterial(const String& name) = 0;
    
    virtual void drawStaticMesh(StaticMesh* mesh, GameObject* owner) = 0;
    virtual void dropStaticMesh(StaticMesh* mesh, GameObject* owner) = 0;
    
    virtual void viewResize(int width, int height) = 0;
    
protected:
    Renderer();
    
    virtual UniquePtr<MaterialCache> createMaterialCache() const = 0;
    
private:
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
    
private:
    UniquePtr<MaterialCache>  mMaterialCache;
    
    struct RenderInfo {
        Surface*                surface;
        MaterialInstance*       materialInstance;
        GameObject*             owner;
        StaticMesh*             sourceMesh;
        LIST_LINK(RenderInfo)   listLink;
    };
    LIST_DECLARE(RenderInfo, listLink) mRenderables;
};

#endif /* defined(__Wonderland__Renderer__) */
