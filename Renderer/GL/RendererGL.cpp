//
//  RendererGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "RendererGL.h"

#include "Core/World.h"

#include "Math/Matrix.h"

#include "Renderer/MaterialInstance.h"
#include "Renderer/StaticMesh.h"
#include "Renderer/Surface.h"
#include "Renderer/Vertex.h"

#include "Util/Constants.h"
#include "Util/File.h"
#include "Util/Log.h"

#include "MaterialCacheGL.h"
#include "MaterialGL.h"
#include "RendererDataGL.h"
#include "SurfaceDataGL.h"

static const int PARAMS_BUFFER_LENGTH = 256;

const std::string RendererGL::MODEL_VIEW_NAME("uModelView");
const std::string RendererGL::PROJECTION_NAME("uProjection");
const std::string RendererGL::COLOR_NAME("uColor");

RendererGL::RendererGL() {
    mMaterialCache = new MaterialCacheGL(File::basePath() + "/" + Constants::SHADERS_BASE);
}

RendererGL::~RendererGL() {
    delete mMaterialCache;
}

void RendererGL::renderFrame() {
    RenderInfo* renderable = mRenderables.Head();
    while(renderable) {
        renderSurface(renderable->surface, renderable->materialInstance);
        renderable = mRenderables.Next(renderable);
    }
}

UniquePtr<MaterialInstance> RendererGL::createMaterial(const std::string& name) {
    MaterialGL* material = mMaterialCache->getMaterial(name);
    MaterialInstance* result = new MaterialInstance(material);
    if(!material->rendererData) {
        generateRendererData(material);
    }
    return UniquePtr<MaterialInstance>(result);
}

void RendererGL::drawStaticMesh(StaticMesh* mesh, GameObject* owner) {
    StaticMesh::SurfacesIterator iterator = mesh->surfacesIterator();
    while(iterator.hasNext()) {
        RenderInfo *ri = new RenderInfo();
        StaticMesh::SurfaceInfo& si = iterator.next();
        
        if(!si.surface->surfaceData) {
            generateSurfaceData(si.surface.get());
        }
        
        ri->surface = si.surface.get();
        ri->materialInstance = si.material;
        ri->owner = owner;
        
        mRenderables.InsertTail(ri);
    }
}

void RendererGL::dropStaticMesh(StaticMesh* mesh, GameObject* owner) {
    RenderInfo* ri = mRenderables.Head();
    while(ri) {
        if(ri->sourceMesh == mesh && ri->owner == owner) {
            RenderInfo* temp = ri;
            ri = mRenderables.Next(ri);
            delete temp;
        }
    }
}

void RendererGL::generateRendererData(MaterialGL* m) const {
    RendererDataGL* data = new RendererDataGL();
    
    data->modelViewUniform = glGetUniformLocation(m->program, MODEL_VIEW_NAME.c_str());
    data->projectionUniform = glGetUniformLocation(m->program, PROJECTION_NAME.c_str());
    data->colorUniform = glGetUniformLocation(m->program, COLOR_NAME.c_str());
    
    m->rendererData = UniquePtr<RendererDataGL>(data);
}

void RendererGL::generateSurfaceData(Surface* s) const {
    UniquePtr<SurfaceDataGL> data(new SurfaceDataGL());
    
    glGenBuffers(1, &data->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * s->verticesCount(), s->vertices(), GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &data->vao);
    glBindVertexArray(data->vao);
    
    glVertexAttribPointer(Vertex::ATTR_POS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(Vertex::ATTR_POS);
    
    glVertexAttribPointer(Vertex::ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3*sizeof(float)));
    glEnableVertexAttribArray(Vertex::ATTR_NORMAL);
    
    glVertexAttribPointer(Vertex::ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6*sizeof(float)));
    glEnableVertexAttribArray(Vertex::ATTR_UV);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    s->surfaceData = data;
}

void RendererGL::renderSurface(Surface* surface, MaterialInstance* materialInstance) {
    Matrix m = Matrix::createIdentity();
    MaterialGL* material = static_cast<MaterialGL*>(materialInstance->parent());
    SurfaceDataGL* surfaceData = static_cast<SurfaceDataGL*>(surface->surfaceData.get());
    
    glUseProgram(material->program);
    
    glUniformMatrix4fv(material->rendererData->projectionUniform, 1, GL_FALSE, m.m);
    glUniformMatrix4fv(material->rendererData->modelViewUniform, 1, GL_FALSE, m.m);
    glUniform4f(material->rendererData->colorUniform, 0, 1, 0, 1);

    glBindVertexArray(surfaceData->vao);
    glDrawArrays(GL_TRIANGLES, 0, surface->verticesCount());
    glBindVertexArray(0);
}
