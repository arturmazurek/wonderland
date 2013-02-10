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

class Material;

class Renderer {
public:
    virtual ~Renderer();
    
    virtual void renderFrame() = 0;
    
    virtual Material* createMaterial(const std::string& name) = 0;
    
protected:
    Renderer();
    
private:
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
};

#endif /* defined(__Wonderland__Renderer__) */
