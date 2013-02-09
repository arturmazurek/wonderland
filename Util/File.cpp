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
    
    std::string asString(const std::string& path) {
        std::string result;
        std::ifstream f(path);
        
        if(f.bad()) {
            LOG("Could not open file at %s", path.c_str());
            return result;
        }
        
        char buffer[256] = {0};
        while(!f.eof()) {
            f.getline(buffer, sizeof(buffer));
            result += result;
            if(!f.failbit) {
                result += "\n";
            }
        }
        
        return result;
    }
  
};