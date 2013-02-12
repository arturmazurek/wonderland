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

const std::string RendererGL::POSITION_NAME("aPosition");

RendererGL::RendererGL() {
    mMaterialCache = new MaterialCacheGL(File::basePath() + "/" + Constants::SHADERS_BASE);
}

RendererGL::~RendererGL() {
    delete mMaterialCache;
}

void RendererGL::renderFrame() {
    RenderInfo* renderable = mRenderables.Head();
    while(renderable) {
        renderSurface(renderable->surface, renderable->material);
        renderable = mRenderables.Next(renderable);
    }
}

Material* RendererGL::createMaterial(const std::string& name) {
    MaterialGL* result = mMaterialCache->getMaterial(name);
    if(!result->rendererData) {
        generateRendererData(result);
    }
    return result;
}

void RendererGL::drawStaticMesh(StaticMesh* mesh, GameObject* owner) {
    StaticMesh::SurfacesIterator iterator = mesh->surfacesIterator();
    while(iterator.hasNext()) {
        RenderInfo *ri = new RenderInfo();
        StaticMesh::SurfaceInfo& si = iterator.next();
        
        if(!si.surface->surfaceData) {
            generateSurfaceData(si.surface);
        }
        
        ri->surface = si.surface;
        ri->material = static_cast<MaterialGL*>(si.material);
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
    
    LOG("0x%x", glGetError());
    LOG("0x%x", glGetError());
    
    data->modelViewUniform = glGetUniformLocation(m->program, MODEL_VIEW_NAME.c_str());
    LOG("0x%x - modelViewUniform", glGetError());
    data->projectionUniform = glGetUniformLocation(m->program, PROJECTION_NAME.c_str());
    LOG("0x%x - projectionUnifrom", glGetError());
    data->colorUniform = glGetUniformLocation(m->program, COLOR_NAME.c_str());
    LOG("0x%x - colorUniform", glGetError());
    
    data->positionIn = glGetAttribLocation(m->program, POSITION_NAME.c_str());
    LOG("0x%x - positionAttribute", glGetError());
    
    m->rendererData = data;
}

void RendererGL::generateSurfaceData(Surface* s) const {
    SurfaceDataGL* data = new SurfaceDataGL();
    
    glGenBuffers(1, &data->vbo);
    LOG("0x%x - glGenBuffers", glGetError());
    glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
    LOG("0x%x - glBindBuffer", glGetError());
    glBufferData(GL_ARRAY_BUFFER, sizeof(*s->vertices()) * s->verticesCount(), s->vertices(), GL_STATIC_DRAW);
    LOG("0x%x - glBufferData", glGetError());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    LOG("0x%x - glBindBuffer", glGetError());
    
    s->surfaceData = data;
}

void RendererGL::renderSurface(Surface* surface, MaterialGL* material) {
    Matrix m = Matrix::createIdentity();
    RendererDataGL* renderData = static_cast<RendererDataGL*>(material->rendererData);
    SurfaceDataGL* surfaceData = static_cast<SurfaceDataGL*>(surface->surfaceData);
    
    glUseProgram(material->program);
    
    LOG("\n");
    glUniformMatrix4fv(renderData->projectionUniform, 1, GL_FALSE, m.m);
    LOG("0x%x", glGetError());
    glUniformMatrix4fv(renderData->modelViewUniform, 1, GL_FALSE, m.m);
    LOG("0x%x", glGetError());
    glUniform4f(renderData->colorUniform, 1, 0, 0, 1);
    LOG("0x%x", glGetError());
    
    glBindBuffer(GL_ARRAY_BUFFER, surfaceData->vbo);
    LOG("0x%x - glBindBuffer", glGetError());
    glEnableClientState(GL_VERTEX_ARRAY);
    LOG("0x%x - glEnableClientState", glGetError());
    glEnableVertexAttribArray(renderData->positionIn);
    LOG("0x%x - glEnableVertexAttribArray", glGetError());
    glVertexAttribPointer(renderData->positionIn, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    LOG("0x%x - glVertexAttribPointer", glGetError());
    
    glDrawArrays(GL_TRIANGLES, 0, surface->verticesCount());
    LOG("0x%x - glDrawArrays", glGetError());
//    glDrawElements(GL_TRIANGLES, 3, GL, <#const GLvoid *indices#>)
    
}
