//
//  Transform.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Transform__
#define __Wonderland__Transform__

#include "Math/Matrix.h"

class Transform {
public:
    Transform();
    ~Transform();
    
    Vector translation() const;
    void setTranslation(const Vector& v);
    
    float scale() const;
    
private:
    Matrix      mFrame;
    Transform*  mParent;
};

#endif /* defined(__Wonderland__Transform__) */
