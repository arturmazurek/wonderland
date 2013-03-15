//
//  Renderer.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Renderer.h"

#include "Util/Log.h"

#include "Camera.h"
#include "MaterialCache.h"
#include "MaterialInstance.h"
#include "StaticMesh.h"
#include "Surface.h"

Renderer::Renderer() {
    
}

Renderer::~Renderer() {
    
}

void Renderer::init() {
    mMaterialCache = createMaterialCache();
}

void Renderer::useCamera(SharedPtr<Camera> camera) {
    mCurrentCamera = camera;
}

const Camera* Renderer::camera() const {
    return mCurrentCamera.get();
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
    if(!mCurrentCamera) {
        LOG("Renderer doesn't have a camera");
        return;
    }
    
    RenderInfo* renderable = mRenderables.Head();
    while(renderable) {
        renderSurface(renderable->surface, renderable->materialInstance);
        renderable = mRenderables.Next(renderable);
    }
}

MaterialCache* Renderer::materialCache() {
    return mMaterialCache.get();
}