//
//  RendererFactory.h
//  Wonderland
//
//  Created by Artur Mazurek on 10.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__RendererFactory__
#define __Wonderland__RendererFactory__

class Renderer;

class RendererFactory {
public:
    enum RendererType {
        RENDERER_OPENGL
    };
    
    static Renderer* createRenderer(RendererType type);
    
private:
    RendererFactory() {}
    ~RendererFactory() {}
    
    static Renderer* createRendererGL();
};

#endif /* defined(__Wonderland__RendererFactory__) */
