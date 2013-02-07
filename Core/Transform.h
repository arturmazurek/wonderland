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
#include "Math/Vector.h"

class Transform {
public:
    Transform();
    ~Transform();
    
    const Vector& pos() const;
    void setPos(const Vector& pos);
    
    float scale() const;
    void setScale(float s);
    
    float scaleX() const;
    float scaleY() const;
    float scaleZ() const;
    
    void setScaleX(float sx);
    void setScaleY(float sy);
    void setScaleZ(float sz);
    
    bool dirty() const;
    void setDirty() const;
private:
    bool        mDirty;
    Matrix      mFrame;
    Vector      mPosition;
    Vector      mScale;
};

#endif /* defined(__Wonderland__Transform__) */
