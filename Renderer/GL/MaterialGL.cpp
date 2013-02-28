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
#include "Util/Util.h"

static const int BUF_SIZE = 512;

static inline ParamType _type2Type(GLenum glType) {
    switch (glType) {
        case GL_FLOAT:
            return PARAM_TYPE_FLOAT;
            
        case GL_FLOAT_VEC2:
            return PARAM_TYPE_VEC2;
            
        case GL_FLOAT_VEC3:
            return PARAM_TYPE_VEC3;
            
        case GL_FLOAT_VEC4:
            return PARAM_TYPE_VEC4;
            
        case GL_FLOAT_MAT4:
            return PARAM_TYPE_MATRIX;
            
        default:
            LOG("Type 0x%x unsupported", glType)
            return PARAM_TYPE_INVALID;
    }
}

// Must be the same order as the enum of elements in
// Vertex class
const String MaterialGL::ATTRIBUTE_NAMES[] = {
    "aPosition",
    "aNormal",
    "aUv"
};

const String MaterialGL::IGNORED_UNIFORMS[] = {
    "uModelView",
    "uProjection"
};

MaterialGL::MaterialGL(const String& name) : Material(name), program(0), generated(false),
modelViewUniform(0), projectionUniform(0), colorUniform(0), mLinked(false) {
    
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
        glBindAttribLocation(program, i, ATTRIBUTE_NAMES[i].data());
    }
    
    glLinkProgram(program);
    
    GLint linkSuccessful = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccessful);
    if(linkSuccessful == GL_FALSE) {
        LOG("Could not link program for material %s", name().data());
        
        GLsizei length = 0;
        GLchar buffer[BUF_SIZE] = {0};
        glGetProgramInfoLog(program, BUF_SIZE, &length, buffer);
        
        LOG("Program log:\n%s\n", buffer);
        
        return false;
    }
    
    mLinked = true;
    
    return true;
}

static inline bool _isIgnored(const String& uniformName) {
    for(int i = 0; i < ARRAY_SIZE(MaterialGL::IGNORED_UNIFORMS); ++i) {
        if(MaterialGL::IGNORED_UNIFORMS[i] == uniformName) {
            return true;
        }
    }
    return false;
}

Array<MaterialParam> MaterialGL::createParams() const {
    if(!mLinked) {
        LOG("Cannot get parameters from an unlinked program");
        return Array<MaterialParam>();
    }
    
    int count = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    
    // First count non-ignored uniforms
    int usedCount = 0;
    for(int i = 0; i < count; ++i) {
        GLenum type = GL_ZERO;
        int size = 0;
        char name[BUF_SIZE] = {0};
        
        glGetActiveUniform(program, i, BUF_SIZE-1, NULL, &size, &type, name);
        if(!_isIgnored(name)) {
            ++usedCount;
        }
    }
    
    // And then return only them
    Array<MaterialParam> result(usedCount);
    for(int i = 0, index = 0; index < usedCount; ++i) {
        GLenum type = GL_ZERO;
        int size = 0;
        char name[BUF_SIZE] = {0};
        
        glGetActiveUniform(program, i, BUF_SIZE-1, NULL, &size, &type, name);
        
        if(_isIgnored(name)) {
            continue;
        }
        
        MaterialParam param;
        param.handle = glGetUniformLocation(program, name);
        param.name = String(name);
        param.value = nullptr;
        param.type = _type2Type(type);
        
        result[index] = param;
        
        ++index;
    }
    
    return result;
}

void MaterialGL::apply(const Array<MaterialParam>& params) {
    for(int i = 0; i < params.size(); ++i ) {
        const MaterialParam& param = params[i];
        switch (param.type) {
            case PARAM_TYPE_FLOAT:
                glUniform1f(param.handle, *(float*)param.value);
                break;
                
            case PARAM_TYPE_VEC2:
                glUniform2fv(param.handle, 1, (float*)param.value);
                break;
                
            case PARAM_TYPE_VEC3:
                glUniform3fv(param.handle, 1, (float*)param.value);
                break;
                
            case PARAM_TYPE_VEC4:
                glUniform4fv(param.handle, 1, (float*)param.value);
                break;
                
            case PARAM_TYPE_MATRIX:
                glUniformMatrix4fv(param.handle, 1, GL_FALSE, (float*)param.value);
                break;
                
            default:
                LOG("Unknown parameter type %d", param.type);
                break;
        }
    }
}
