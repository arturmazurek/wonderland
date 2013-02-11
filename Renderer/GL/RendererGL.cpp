//
//  RendererGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "RendererGL.h"

#include "Core/World.h"

#include "Renderer/StaticMesh.h"
#include "Renderer/Surface.h"
#include "Renderer/Vertex.h"

#include "Util/Constants.h"
#include "Util/File.h"
#include "Util/Log.h"

#include "MaterialCacheGL.h"
#include "MaterialGL.h"

RendererGL::RendererGL() {
    mMaterialCache = new MaterialCacheGL(File::basePath() + "/" + Constants::SHADERS_BASE);
}

RendererGL::~RendererGL() {
    delete mMaterialCache;
}

void RendererGL::renderFrame() {
    RenderInfo* renderable = mRenderables.Head();
    while(renderable) {
        render(renderable);
        renderable = mRenderables.Next(renderable);
    }
}

Material* RendererGL::createMaterial(const std::string& name) {
    return mMaterialCache->getMaterial(name);
}

void RendererGL::drawStaticMesh(StaticMesh* mesh, GameObject* owner) {
    RenderInfo *ri = new RenderInfo();
    ri->mesh = mesh;
    ri->owner = owner;
    mRenderables.InsertTail(ri);
}

void RendererGL::dropStaticMesh(StaticMesh* mesh, GameObject* owner) {
    RenderInfo* found = nullptr;
    RenderInfo* temp = mRenderables.Head();
    while(temp) {
        if(temp == found) {
            break;
        }
        temp = mRenderables.Next(temp);
    }
    
    if(!found) {
        LOG("Static mesh 0x%p not drawn for object - 0x%p (%u)", mesh, owner, owner->objectId());
        return;
    }
    
    delete found;
}

void RendererGL::render(RenderInfo* renderable) {    
    StaticMesh::SurfacesIterator iterator = renderable->mesh->surfacesIterator();
    while(iterator.hasNext()) {
        StaticMesh::SurfaceInfo& si = iterator.next();
        renderSurface(si.surface, si.material);
    }
}

void RendererGL::renderSurface(Surface* surface, Material* m) {
    MaterialGL* material = static_cast<MaterialGL*>(m);
    
    LOG("----- 0x%x ------", glGetError());
    glUseProgram(material->program);
    LOG("0x%x", glGetError());
    // TODO - it should be glVertexAttributePointer...
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), surface->vertices());
    LOG("0x%x", glGetError());
    glDrawArrays(GL_TRIANGLES, 0, surface->verticesCount());
    LOG("0x%x", glGetError());
}
