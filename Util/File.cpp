//
//  File.c
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//
#include "File.h"

#include <fstream>

#include "Log.h"

namespace File {
    
    String asString(const String& path) {
        String result;
        std::ifstream f(path.data());
        
        if(!f.is_open()) {
            LOG("Could not open file at %s", path.data());
            return result;
        }
        
        char buffer[256] = {0};
        while(!f.eof()) {
            f.getline(buffer, sizeof(buffer));
            result += buffer;
            if(!f.fail()) {
                result += "\n";
            }
        }
        
        return result;
    }
  
};