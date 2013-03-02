//
//  OpenGLView.m
//  CodeaMac
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#import "OpenGLView.h"
#import "MainController.h"

#include "Game.h"
#include "World.h"
#include "GameInterface.h"

@implementation OpenGLView

@synthesize game = _game;

- (Game*)game {
    if(!_game) {
        _game = new Game();
        if(!_game->initializeGame()) {
            NSLog(@"Couldn't initialize game");
            _game = nullptr;
        }
    }
    
    return _game;
}

- (NSOpenGLContext*) openGLContext
{
	return openGLContext;
}

- (NSOpenGLPixelFormat*) pixelFormat
{
	return pixelFormat;
}

- (void) setMainController:(MainController*)theController;
{
	controller = theController;
}

- (CVReturn) getFrameForTime:(const CVTimeStamp*)outputTime
{
	// There is no autorelease pool when this method is called because it will be called from a background thread
	// It's important to create one or you will leak objects
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	// Update the animation
	CFAbsoluteTime currentTime = CFAbsoluteTimeGetCurrent();
//	[[controller scene] advanceTimeBy:(currentTime - [controller renderTime])];
	[controller setRenderTime:currentTime];
	
	[self drawView];
	
	[pool release];
    return kCVReturnSuccess;
}

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    CVReturn result = [(OpenGLView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}

- (void) setupDisplayLink
{
	// Create a display link capable of being used with all active displays
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	
	// Set the renderer output callback function
	CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);
	
	// Set the display link for the current renderer
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
}

- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context
{
    NSOpenGLPixelFormatAttribute attribs[] =
    {
		kCGLPFAAccelerated,
		kCGLPFANoRecovery,
		kCGLPFADoubleBuffer,
		kCGLPFAColorSize, 24,
		kCGLPFADepthSize, 16,
        kCGLPFAOpenGLProfile, kCGLOGLPVersion_3_2_Core,
		0
    };
    
    pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
	
    if (!pixelFormat)
		NSLog(@"No OpenGL pixel format");
	
	// NSOpenGLView does not handle context sharing, so we draw to a custom NSView instead
	openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:context];
	
	if (self = [super initWithFrame:frameRect]) {
		[[self openGLContext] makeCurrentContext];
		
		// Synchronize buffer swaps with vertical refresh rate
		GLint swapInt = 1;
		[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
		
		[self setupDisplayLink];
		
		// Look for changes in view size
		// Note, -reshape will not be called automatically on size changes because NSView does not export it to override
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(reshape)
													 name:NSViewGlobalFrameDidChangeNotification
												   object:self];
	}
	
	return self;
}

- (id) initWithFrame:(NSRect)frameRect
{
	self = [self initWithFrame:frameRect shareContext:nil];
	return self;
}

- (void) lockFocus
{
	[super lockFocus];
	if ([[self openGLContext] view] != self)
		[[self openGLContext] setView:self];
}

- (void) reshape
{
	// This method will be called on the main thread when resizing, but we may be drawing on a secondary thread through the display link
	// Add a mutex around to avoid the threads accessing the context simultaneously
	CGLLockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
	
	// Delegate to the scene object to update for a change in the view size
//	[[controller scene] setViewportRect:[self bounds]];
    if(self.game) {
        self.game->gameInterface()->windowResized(self.bounds.size.width, self.bounds.size.height);
    }
	[[self openGLContext] update];
	
	CGLUnlockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (void) drawRect:(NSRect)dirtyRect
{
	// Ignore if the display link is still running
	if (!CVDisplayLinkIsRunning(displayLink))
		[self drawView];
}

- (void) drawView
{
	// This method will be called on both the main thread (through -drawRect:) and a secondary thread (through the display link rendering loop)
	// Also, when resizing the view, -reshape is called on the main thread, but we may be drawing on a secondary thread
	// Add a mutex around to avoid the threads accessing the context simultaneously
	CGLLockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
	
	// Make sure we draw to the right context
	[[self openGLContext] makeCurrentContext];
    
    glClearColor(0.f, 0.3f, 0.6f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    self.game->doFrame();
//
	// Delegate to the scene object for rendering
//    [[controller scene] render];
	[[self openGLContext] flushBuffer];
	
	CGLUnlockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (BOOL) acceptsFirstResponder
{
    // We want this view to be able to receive key events
    return YES;
}

- (void) keyDown:(NSEvent *)theEvent
{
    // Delegate to the controller object for handling key events
    [controller keyDown:theEvent];
}

- (void)mouseDown:(NSEvent *)theEvent
{
    // Delegate to the controller object for handling mouse events
    [controller mouseDown:theEvent];
}

- (void) startAnimation
{
	if (displayLink && !CVDisplayLinkIsRunning(displayLink))
		CVDisplayLinkStart(displayLink);
}

- (void) stopAnimation
{
	if (displayLink && CVDisplayLinkIsRunning(displayLink))
		CVDisplayLinkStop(displayLink);
}

- (void) dealloc
{
	// Stop and release the display link
	CVDisplayLinkStop(displayLink);
    CVDisplayLinkRelease(displayLink);
	
	// Destroy the context
	[openGLContext release];
	[pixelFormat release];
	
	[[NSNotificationCenter defaultCenter] removeObserver:self
													name:NSViewGlobalFrameDidChangeNotification
												  object:self];
    
    delete self.game;
    
	[super dealloc];
}

@end
