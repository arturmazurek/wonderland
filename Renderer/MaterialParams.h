//
//  MaterialParams.h
//  Wonderland
//
//  Created by Artur Mazurek on 05/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_MaterialParams_h
#define Wonderland_MaterialParams_h

#include "Util/Array.h"
#include "Util/String.h"

class MaterialParams {
public:
    struct Parameter {
        enum Type {
            TYPE_INVALID = -1,
            TYPE_FLOAT,
            TYPE_VEC2,
            TYPE_VEC3,
            TYPE_VEC4,
            TYPE_MATRIX,
            
            TYPE_ENUM_SIZE
        };
        
        String      name;
        int         handle;
        
        void*       value;
        int         size;
        Type        type;
    };
    
    MaterialParams();
    ~MaterialParams();
    MaterialParams(const MaterialParams& other);
    MaterialParams& operator=(const MaterialParams& other);
    
    void addParameter(const Parameter& parameter);
    
    Parameter& getParameter(int i);
    const Parameter& getParameter(int i) const;
    
    Parameter* getParameter(const String& name);
    const Parameter* getParameter(const String& name) const;
    
    int count() const;
    
private:
    Array<Parameter> mParams;
};

#endif
