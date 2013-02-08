//
//  Material.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Material__
#define __Wonderland__Material__

class Shader;

class Material {
public:
    Material();
    virtual ~Material();
    
private:
    Shader* mShader;
};

#endif /* defined(__Wonderland__Material__) */
