//
//  MaterialGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MaterialGL.h"

#include "ShaderGL.h"

#include "Renderer/Vertex.h"

#include "Util/Log.h"

static const int INFO_LOG_SIZE = 512;

// Must be the same order as the enum of elements in
// Vertex class
const std::string MaterialGL::ATTRIBUTE_NAMES[] = {
    "aPosition",
    "aNormal",
    "aUv"
};

MaterialGL::MaterialGL(const std::string& name) : Material(name), program(0), generated(false),
modelViewUniform(0), projectionUniform(0), colorUniform(0) {
    
}

MaterialGL::~MaterialGL() {
    glDeleteProgram(program);
}

bool MaterialGL::buildMaterial(ShaderGL* vertexShader, ShaderGL* fragmentShader) {
    if(program) {
        glDeleteProgram(program);
    }
    
    program = glCreateProgram();
    
    if(vertexShader->type != ShaderGL::VERTEX_SHADER) {
        LOG("Given vertex shader 0x%p is not a vertex shader", vertexShader);
        return false;
    }
    
    if(fragmentShader->type != ShaderGL::FRAGMENT_SHADER) {
        LOG("Given fragment shadef 0x%p is not a fragment shader", fragmentShader);
        return false;
    }
    
    glAttachShader(program, vertexShader->shader);
    glAttachShader(program, fragmentShader->shader);
    
    for(int i = 0; i < Vertex::ATTR_ENUM_SIZE; ++i) {
        glBindAttribLocation(program, i, ATTRIBUTE_NAMES[i].c_str());
    }
    
    glLinkProgram(program);
    
    GLint linkSuccessful = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccessful);
    if(linkSuccessful == GL_FALSE) {
        LOG("Could not link program for material %s", name().c_str());
        
        GLsizei length = 0;
        GLchar buffer[INFO_LOG_SIZE] = {0};
        glGetProgramInfoLog(program, INFO_LOG_SIZE, &length, buffer);
        
        LOG("Program log:\n%s\n", buffer);
        
        return false;
    }
    
    return true;
}
