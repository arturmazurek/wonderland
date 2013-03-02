//
//  GameInterface.h
//  Wonderland
//
//  Created by Artur Mazurek on 01/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__GameInterface__
#define __Wonderland__GameInterface__

class MessageQueue;

class GameInterface {
public:
    GameInterface(MessageQueue* queue);
    ~GameInterface();
    
    void windowResized(int newWidth, int newHeight);
    
    void keyPressed(int keyCode);
    void keyReleased(int keyCode);
    
    void mouseMoved(int newWindowX, int newWindowY);
    void mousePressed(int mouseKey);
    void mouseReleased(int mouseKey);
    void mouseWheelScrolled(float amount);
    
private:
    GameInterface(const GameInterface&);
    GameInterface& operator=(const GameInterface&);
    
private:
    MessageQueue* mQueue;
};

#endif /* defined(__Wonderland__GameInterface__) */
