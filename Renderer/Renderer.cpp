//
//  Renderer.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Renderer.h"

#include "MaterialCache.h"
#include "StaticMesh.h"

Renderer::Renderer() {
    
}

Renderer::~Renderer() {
    
}

void Renderer::init() {
    mMaterialCache = createMaterialCache();
}

UniquePtr<MaterialInstance> Renderer::createMaterial(const String& name) {
    return mMaterialCache->createMaterialInstance(name);
}

void Renderer::drawStaticMesh(StaticMesh* mesh, GameObject* owner) {
    StaticMesh::SurfacesIterator iterator = mesh->surfacesIterator();
    while(iterator.hasNext()) {
        RenderInfo *ri = new RenderInfo();
        StaticMesh::SurfaceInfo& si = iterator.next();
        
        ri->surface = si.surface.get();
        ri->materialInstance = si.material;
        ri->owner = owner;
        
        mRenderables.InsertTail(ri);
        
        usingSurface(ri->surface);
        usingMaterialInstance(ri->materialInstance);
    }
}

void Renderer::dropStaticMesh(StaticMesh* mesh, GameObject* owner) {
    RenderInfo* ri = mRenderables.Head();
    while(ri) {
        if(ri->sourceMesh == mesh && ri->owner == owner) {
            RenderInfo* temp = ri;
            ri = mRenderables.Next(ri);
            delete temp;
        }
    }
}

void Renderer::renderFrame() {
    RenderInfo* renderable = mRenderables.Head();
    while(renderable) {
        renderSurface(renderable->surface, renderable->materialInstance);
        renderable = mRenderables.Next(renderable);
    }
}

MaterialCache* Renderer::materialCache() {
    return mMaterialCache.get();
}