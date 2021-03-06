//
//  ShaderGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "ShaderGL.h"

#include <cstring>

#include "Util/Log.h"

static const int MAX_ERROR_LOG_LENGTH = 256;

ShaderGL::ShaderGL() : shader(0), type(TYPE_INVALID) {
    
}

ShaderGL::~ShaderGL() {
    glDeleteShader(shader);
}

bool ShaderGL::compile(const GLchar* body, Type type) {
    shader = glCreateShader(type);
    
    const GLchar* source[] = {body};
    glShaderSource(shader, 1, source, NULL);
    
    glCompileShader(shader);
    
    GLint compileStatus = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    
    if(compileStatus == GL_TRUE) {
        this->type = type;
        return true;
    } else {
        LOG("Could not compile shader:\n***\n%s***", body);
        type = TYPE_INVALID;
        return false;
    }
}

std::string ShaderGL::getShaderError() const {
    GLchar errorLog[MAX_ERROR_LOG_LENGTH];
    glGetShaderInfoLog(shader, sizeof(errorLog), NULL, errorLog);
    return std::string(errorLog);
}