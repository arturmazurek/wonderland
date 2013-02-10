//
//  Log.h
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_Log_h
#define Wonderland_Log_h

#include <cstdio>

#define LOG(...) { std::printf(__VA_ARGS__); std::printf("\n"); }

#endif
