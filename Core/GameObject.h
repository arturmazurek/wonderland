//
//  GameObject.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__GameObject__
#define __Wonderland__GameObject__

#include "Transform.h"

class GameObject {
public:
    GameObject();
    ~GameObject();

    Transform& transform();
    
private:
    Transform mTransform;
};

#endif /* defined(__Wonderland__GameObject__) */
