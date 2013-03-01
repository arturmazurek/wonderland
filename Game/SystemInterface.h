//
//  SystemInterface.h
//  Wonderland
//
//  Created by Artur Mazurek on 01/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__SystemInterface__
#define __Wonderland__SystemInterface__

class MessageQueue;

class SystemInterface {
public:
    SystemInterface(MessageQueue* queue);
    ~SystemInterface();
    
    void windowResized(int newWidth, int newHeight);
    
    void keyPressed(int keyCode);
    void keyReleased(int keyCode);
    
    void mouseMoved(int newWindowX, int newWindowY);
    void mousePressed(int mouseKey);
    void mouseReleased(int mouseKey);
    void mouseWheelScrolled(float amount);
    
private:
    SystemInterface(const SystemInterface&);
    SystemInterface& operator=(const SystemInterface&);
    
private:
    MessageQueue* mQueue;
};

#endif /* defined(__Wonderland__SystemInterface__) */
