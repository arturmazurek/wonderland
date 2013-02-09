//
//  RendererGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__RendererGL__
#define __Wonderland__RendererGL__

#include "../Renderer.h"

class MaterialCacheGL;

class RendererGL : public Renderer {
public:
    RendererGL();
    virtual ~RendererGL();
    
    virtual void renderFrame() override;

    virtual Material* createMaterial(const std::string& name) override;
    
private:
    RendererGL(const RendererGL&);
    RendererGL& operator=(const RendererGL&);
    
private:
    MaterialCacheGL*  mMaterialCache;
};

#endif /* defined(__Wonderland__RendererGL__) */
