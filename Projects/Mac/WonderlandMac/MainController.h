//
//  MainController.h
//  CodeaMac
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>

@class OpenGLView;
@class Scene;

@interface MainController : NSResponder {
    
	BOOL isInFullScreenMode;
	
	// full-screen mode
#if MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_5
	NSWindow *fullScreenWindow;
	OpenGLView *fullScreenView;
#else
	CGLContextObj fullScreenContextObj;
#endif
	
	// window mdoe
	IBOutlet OpenGLView *openGLView;
	
//	Scene *scene;
	BOOL isAnimating;
	CFAbsoluteTime renderTime;
}

- (IBAction)toggleFullScreen:(id)sender;

- (void) goFullScreen;
- (void) goWindow;

//- (Scene*) scene;

- (CFAbsoluteTime) renderTime;
- (void) setRenderTime:(CFAbsoluteTime)time;

@end