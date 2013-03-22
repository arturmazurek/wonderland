//
//  Renderer.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Renderer.h"

#include "Core/GameObject.h"

#include "Util/Log.h"

#include "Camera.h"
#include "Material.h"
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

void Renderer::viewResized(int width, int height) {
    if(!mCurrentCamera->isPerspective()) {
        mCurrentCamera->setOrtho(width, height);
    } else {
        float aspect = static_cast<float>(width) / height;
        mCurrentCamera->setPerspective(mCurrentCamera->fov(), aspect);
    }
}

void Renderer::renderFrame() {
    if(!mCurrentCamera) {
        LOG("Renderer doesn't have a camera");
        return;
    }
    
    GameObject* obj = nullptr;
    RenderInfo* renderable = mRenderables.Head();
    while(renderable) {
        Material* m = mMaterialCache->getMaterial(renderable->materialInstance->parent());
        useMaterial(m);
        
        if(obj != renderable->owner) {
            obj = renderable->owner;
            useObjectTransform(mCurrentCamera->view() * obj->transform.getMatrix());
        }
        
        m->apply(renderable->materialInstance->getParams());
        
        renderSurface(renderable->surface, renderable->materialInstance);
        renderable = mRenderables.Next(renderable);
    }
}

MaterialCache* Renderer::materialCache() {
    return mMaterialCache.get();
}