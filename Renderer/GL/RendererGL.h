//
//  RendererGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__RendererGL__
#define __Wonderland__RendererGL__

#include "Renderer/Renderer.h"

#include "Util/List.h"
#include "Util/String.h"

class MaterialGL;
class Surface;

class RendererGL : public Renderer {
public:
    RendererGL();
    virtual ~RendererGL();
    
    virtual UniquePtr<MaterialCache> createMaterialCache() const override;
    virtual void viewResized(int width, int height) override;
    
    virtual void renderSurface(Surface* surface, MaterialInstance* materialInstance) override;
    
    virtual void usingSurface(Surface* surface) override;
    virtual void usingMaterialInstance(MaterialInstance* materialInstance) override;
    
private:
    RendererGL(const RendererGL&);
    RendererGL& operator=(const RendererGL&);
    
    void generateRendererData(MaterialGL* m) const;
    void generateSurfaceData(Surface* s) const;
    
private:
    static const String MODEL_VIEW_NAME;
    static const String PROJECTION_NAME;
    static const String COLOR_NAME;
};

#endif /* defined(__Wonderland__RendererGL__) */
