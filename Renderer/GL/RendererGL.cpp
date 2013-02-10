//
//  RendererGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "RendererGL.h"

#include "Core/World.h"

#include "Util/Constants.h"
#include "Util/Log.h"

#include "MaterialCacheGL.h"
#include "MaterialGL.h"

RendererGL::RendererGL() {
    mMaterialCache = new MaterialCacheGL(Constants::RESOURCES_BASE);
}

RendererGL::~RendererGL() {
    delete mMaterialCache;
}

void RendererGL::renderFrame() {
    
}

Material* RendererGL::createMaterial(const std::string& name) {
    return nullptr;
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