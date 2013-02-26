//
//  Material.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Material__
#define __Wonderland__Material__

#include <string>

#include "Util/Array.h"

enum ParamType {
    PARAM_TYPE_INVALID = -1,
    PARAM_TYPE_FLOAT,
    PARAM_TYPE_VEC2,
    PARAM_TYPE_VEC3,
    PARAM_TYPE_VEC4,
    PARAM_TYPE_MATRIX,
    
    PARAM_TYPE_ENUM_SIZE
};

struct MaterialParam {
    std::string name;
    int         handle;
    
    void*       value;
    int         size;
    ParamType   type;
    
    MaterialParam();
    ~MaterialParam();
    MaterialParam(const MaterialParam& other);
    MaterialParam& operator=(const MaterialParam& other);
};

/**
 * Material is a shader with associated parameters
 * There is one material per surface. Each has its own instance
 * and that allows to tweak material properies to be shown later on.
 */
class Material {
public:
    Material(const std::string& name);
    virtual ~Material();
    
    const std::string& name() const;
    
    virtual Array<MaterialParam> createParams() const = 0;
    virtual void apply(const Array<MaterialParam>& params) = 0;
    
    void setDefaults(Array<MaterialParam>& param);
    
private:
    std::string     mName;
};

#endif /* defined(__Wonderland__Material__) */
