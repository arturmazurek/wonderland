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

class MaterialCacheGL;
class Surface;

class RendererGL : public Renderer {
public:
    RendererGL();
    virtual ~RendererGL();
    
    virtual void renderFrame() override;

    virtual Material* createMaterial(const std::string& name) override;
    
    virtual void drawStaticMesh(StaticMesh* mesh, GameObject* owner) override;
    virtual void dropStaticMesh(StaticMesh* mesh, GameObject* owner) override;
    
private:
    RendererGL(const RendererGL&);
    RendererGL& operator=(const RendererGL&);
    
    void renderSurface(Surface* surface, Material* material);
    
private:
    MaterialCacheGL*  mMaterialCache;
    
    struct RenderInfo {
        Surface*    surface;
        Material*   material;
        GameObject* owner;
        StaticMesh* sourceMesh;
        LIST_LINK(RenderInfo) listLink;
    };
    LIST_DECLARE(RenderInfo, listLink) mRenderables;
};

#endif /* defined(__Wonderland__RendererGL__) */
