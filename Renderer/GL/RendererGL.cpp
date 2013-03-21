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

#include "Renderer/Camera.h"
#include "Renderer/MaterialInstance.h"
#include "Renderer/StaticMesh.h"
#include "Renderer/Surface.h"
#include "Renderer/Vertex.h"

#include "Util/Constants.h"
#include "Util/File.h"
#include "Util/Log.h"

#include "MaterialCacheGL.h"
#include "MaterialGL.h"
#include "OpenGL.h"
#include "SurfaceDataGL.h"

static const int PARAMS_BUFFER_LENGTH = 256;

const String RendererGL::MODEL_VIEW_NAME("uModelView");
const String RendererGL::PROJECTION_NAME("uProjection");
const String RendererGL::COLOR_NAME("uColor");

RendererGL::RendererGL() {

}

RendererGL::~RendererGL() {

}

UniquePtr<MaterialCache> RendererGL::createMaterialCache() const {
    return UniquePtr<MaterialCache>(new MaterialCacheGL(File::basePath() + "/" + Constants::SHADERS_BASE));
}

void RendererGL::useMaterial(Material* m) {
    if(!m) {
        mCurrentMaterial = nullptr;
        return;
    }
    
    MaterialGL* material = static_cast<MaterialGL*>(m);
    if(!material->generated) {
        generateRendererData(material);
    }
    
    if(mCurrentMaterial == material) {
        return;
    }
    
    mCurrentMaterial = material;
    glUseProgram(mCurrentMaterial->program);
}

void RendererGL::useObjectTransform(const Matrix& transform) {
    if(!mCurrentMaterial) {
        return;
    }
    
    glUniformMatrix4fv(mCurrentMaterial->modelViewUniform, 1, GL_FALSE, transform.m);
}

void RendererGL::generateRendererData(MaterialGL* m) const {
    m->modelViewUniform = glGetUniformLocation(m->program, MODEL_VIEW_NAME.data());
    m->projectionUniform = glGetUniformLocation(m->program, PROJECTION_NAME.data());
    m->colorUniform = glGetUniformLocation(m->program, COLOR_NAME.data());
    
    m->generated = true;
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
    glUniformMatrix4fv(mCurrentMaterial->projectionUniform, 1, GL_FALSE, camera()->projection().m); // TODO: find a better place
    
    SurfaceDataGL* surfaceData = static_cast<SurfaceDataGL*>(surface->surfaceData.get());
    if(!surfaceData) {
        generateSurfaceData(surface);
        surfaceData = static_cast<SurfaceDataGL*>(surface->surfaceData.get());
    }

    glBindVertexArray(surfaceData->vao);
    glDrawArrays(GL_TRIANGLES, 0, surface->verticesCount());
    glBindVertexArray(0);
}

void RendererGL::viewResized(int width, int height) {
    glViewport(0, 0, width, height);
    
    Renderer::viewResized(width, height);
}
