//
//  SystemInfo.h
//  Wonderland
//
//  Created by Artur Mazurek on 10.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__SystemInfo__
#define __Wonderland__SystemInfo__

class SystemInfo {
public:
    SystemInfo();
    ~SystemInfo();
    
    bool hasOpengGL() const;
    
private:
    SystemInfo(const SystemInfo&);
    SystemInfo& operator=(const SystemInfo&);
};

#endif /* defined(__Wonderland__SystemInfo__) */
