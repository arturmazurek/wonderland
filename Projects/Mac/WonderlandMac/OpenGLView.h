//
//  OpenGLView.h
//  CodeaMac
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

@class MainController;

class Game;

@interface OpenGLView : NSView {
	
	NSOpenGLContext *openGLContext;
	NSOpenGLPixelFormat *pixelFormat;
	
	MainController *controller;
	
	CVDisplayLinkRef displayLink;
	BOOL isAnimating;
}

- (id) initWithFrame:(NSRect)frameRect;
- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context;

- (NSOpenGLContext*) openGLContext;

- (void) setMainController:(MainController*)theController;

- (void) drawView;

- (void) startAnimation;
- (void) stopAnimation;

@property (nonatomic, readonly) Game* game;

@end
