//
//  Renderer.h
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Renderer__
#define __Wonderland__Renderer__

#include <string>

#include "Util/UniquePtr.h"

class GameObject;
class MaterialInstance;
class StaticMesh;

class Renderer {
public:
    virtual ~Renderer();
    
    virtual void renderFrame() = 0;
    
    virtual UniquePtr<MaterialInstance> createMaterial(const std::string& name) = 0;
    
    virtual void drawStaticMesh(StaticMesh* mesh, GameObject* owner) = 0;
    virtual void dropStaticMesh(StaticMesh* mesh, GameObject* owner) = 0;
    
protected:
    Renderer();
    
private:
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
};

#endif /* defined(__Wonderland__Renderer__) */
