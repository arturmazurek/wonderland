//
//  MaterialGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MaterialGL.h"

MaterialGL::MaterialGL() : program(0) {
    
}

MaterialGL::~MaterialGL() {
    glDeleteProgram(program);
}
