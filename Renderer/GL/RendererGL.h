//
//  RendererGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__RendererGL__
#define __Wonderland__RendererGL__

#include "Renderer/Renderer.h"

#include "Util/List.h"
#include "Util/String.h"

#include "OpenGL.h"

class MaterialCacheGL;
class MaterialGL;
class Surface;

class RendererGL : public Renderer {
public:
    RendererGL();
    virtual ~RendererGL();
    
    virtual void renderFrame() override;

    virtual UniquePtr<MaterialInstance> createMaterial(const String& name) override;
    
    virtual void drawStaticMesh(StaticMesh* mesh, GameObject* owner) override;
    virtual void dropStaticMesh(StaticMesh* mesh, GameObject* owner) override;
    
private:
    RendererGL(const RendererGL&);
    RendererGL& operator=(const RendererGL&);
    
    void renderSurface(Surface* surface, MaterialInstance* materialInstance);
    
    void generateRendererData(MaterialGL* m) const;
    void generateSurfaceData(Surface* s) const;
    
private:
    static const String MODEL_VIEW_NAME;
    static const String PROJECTION_NAME;
    static const String COLOR_NAME;
    
    MaterialCacheGL*  mMaterialCache;
    
    struct RenderInfo {
        Surface*                surface;
        MaterialInstance*       materialInstance;
        GameObject*             owner;
        StaticMesh*             sourceMesh;
        LIST_LINK(RenderInfo)   listLink;
    };
    LIST_DECLARE(RenderInfo, listLink) mRenderables;
};

#endif /* defined(__Wonderland__RendererGL__) */
