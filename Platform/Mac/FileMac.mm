//
//  File.c
//  Wonderland
//
//  Created by Artur Mazurek on 11.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//
#ifdef __APPLE__

#include "File.h"

#import <Foundation/Foundation.h>

namespace File {
    
    std::string basePath() {
        NSString* bundlePath = [[NSBundle mainBundle] bundlePath];
        return std::string(bundlePath.UTF8String) + "/Contents/Resources";
    }
    
}

#endif // TARGET_OS_MAC
