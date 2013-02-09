//
//  Renderer.h
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Renderer__
#define __Wonderland__Renderer__

class ShaderCache;

class Renderer {
public:
    static Renderer* instance();
    
    virtual void renderFrame() = 0;
    
    virtual ShaderCache* shaderCache() = 0;
    
protected:
    Renderer();
    virtual ~Renderer();
    
private:
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
};

#endif /* defined(__Wonderland__Renderer__) */
