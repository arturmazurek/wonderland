//
//  Renderer.h
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Renderer__
#define __Wonderland__Renderer__

#include "Math/Matrix.h"

#include "Util/List.h"
#include "Util/SharedPtr.h"
#include "Util/String.h"
#include "Util/UniquePtr.h"

class Camera;
class GameObject;
class Material;
class MaterialCache;
class MaterialInstance;
class StaticMesh;
class Surface;

class Renderer {
public:
    virtual ~Renderer();
    
    virtual void init();
    virtual void viewResized(int width, int height);
    
    void renderFrame();
    
    UniquePtr<MaterialInstance> createMaterial(const String& name);
    
    void useCamera(SharedPtr<Camera> camera);
    
    void drawStaticMesh(StaticMesh* mesh, GameObject* owner);
    void dropStaticMesh(StaticMesh* mesh, GameObject* owner);
    
protected:
    Renderer();
    
    virtual UniquePtr<MaterialCache> createMaterialCache() const = 0;
    virtual void renderSurface(Surface* surface, MaterialInstance* materialInstance) = 0;
    
    virtual void useMaterial(Material* material) = 0;
    virtual void useObjectTransform(const Matrix& transform) = 0;
    
    virtual void cullFaces(bool enabled) = 0;
    
    MaterialCache* materialCache();
    
    const Camera* camera() const;
    
private:
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
    
private:
    UniquePtr<MaterialCache>            mMaterialCache;
    
    struct RenderInfo {
        Surface*                surface;
        MaterialInstance*       materialInstance;
        GameObject*             owner;
        StaticMesh*             sourceMesh;
        LIST_LINK(RenderInfo)   listLink;
    };
    LIST_DECLARE(RenderInfo, listLink)  mRenderables;
    
    SharedPtr<Camera>                   mCurrentCamera;
};

#endif /* defined(__Wonderland__Renderer__) */
