//
//  Renderer.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Renderer.h"

class Renderer {
public:
    static Renderer* instance();
    
    void renderFrame();
};