//
//  ServiceLocator.h
//  Wonderland
//
//  Created by Artur Mazurek on 28.03.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_ServiceLocator_h
#define Wonderland_ServiceLocator_h

class Renderer;

class ServiceLocator {
public:
    static Renderer* renderer;
    
private:
    ServiceLocator();
    ~ServiceLocator();
    ServiceLocator(const ServiceLocator&);
    ServiceLocator& operator=(const ServiceLocator&);
};

#endif
