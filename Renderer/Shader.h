//
//  Shader.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Shader__
#define __Wonderland__Shader__

class Material;

/**
 * There should be just one shader object of each name
 * existing in the engine. They are referenced by materials but not owned 
 * by them.
 */
class Shader {
public:
    void reference(Material* claimer);
    void release(Material* claimer);
    
protected:
    Shader();
    virtual ~Shader();
    
private:
    int mReferenceCount;
};

#endif /* defined(__Wonderland__Shader__) */
