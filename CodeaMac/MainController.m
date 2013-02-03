//
//  MainController.m
//  CodeaMac
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#import "MainController.h"
#import "OpenGLView.h"
//#import "Scene.h"

@implementation MainController

- (void) goFullScreen
{
	isInFullScreenMode = YES;
	
	// Pause the non-fullscreen view
	[openGLView stopAnimation];
	
	NSRect mainDisplayRect, viewRect;
	
	// Create a screen-sized window on the display you want to take over
	// Note, mainDisplayRect has a non-zero origin if the key window is on a secondary display
	mainDisplayRect = [[NSScreen mainScreen] frame];
	fullScreenWindow = [[NSWindow alloc] initWithContentRect:mainDisplayRect styleMask:NSBorderlessWindowMask
													 backing:NSBackingStoreBuffered defer:YES];
	
	// Set the window level to be above the menu bar
	[fullScreenWindow setLevel:NSMainMenuWindowLevel+1];
	
	// Perform any other window configuration you desire
	[fullScreenWindow setOpaque:YES];
	[fullScreenWindow setHidesOnDeactivate:YES];
	
	// Create a view with a double-buffered OpenGL context and attach it to the window
	// By specifying the non-fullscreen context as the shareContext, we automatically inherit the OpenGL objects (textures, etc) it has defined
	viewRect = NSMakeRect(0.0, 0.0, mainDisplayRect.size.width, mainDisplayRect.size.height);
	fullScreenView = [[OpenGLView alloc] initWithFrame:viewRect shareContext:[openGLView openGLContext]];
	[fullScreenWindow setContentView:fullScreenView];
	
	// Show the window
	[fullScreenWindow makeKeyAndOrderFront:self];
	
	// Set the scene with the full-screen viewport and viewing transformation
//	[scene setViewportRect:viewRect];
	
	// Assign the view's MainController to self
	[fullScreenView setMainController:self];
	
	if (!isAnimating) {
		// Mark the view as needing drawing to initalize its contents
		[fullScreenView setNeedsDisplay:YES];
	}
	else {
		// Start playing the animation
		[fullScreenView startAnimation];
	}
}

- (void) goWindow
{
	isInFullScreenMode = NO;
	
	// Release the screen-sized window and view
	[fullScreenWindow release];
	[fullScreenView release];
	
	// Switch to the non-fullscreen context
	[[openGLView openGLContext] makeCurrentContext];
	
	if (!isAnimating) {
		// Mark the view as needing drawing
		// The animation has advanced while we were in full-screen mode, so its current contents are stale
		[openGLView setNeedsDisplay:YES];
	}
	else {
		// Continue playing the animation
		[openGLView startAnimation];
	}
}

- (IBAction)toggleFullScreen:(id)sender {
    if(isInFullScreenMode) {
        [self goWindow];
    } else {
        [self goFullScreen];
    }
}

- (void) awakeFromNib
{
	// Allocate the scene object
//	scene = [[Scene alloc] init];
	
	// Assign the view's MainController to self
	[openGLView setMainController:self];
	
	// Activate the display link now
	[openGLView startAnimation];
	isAnimating = YES;
}

- (void) dealloc
{
//	[scene release];
	[super dealloc];
}

//- (Scene*) scene
//{
//	return scene;
//}

- (CFAbsoluteTime) renderTime
{
	return renderTime;
}

- (void) setRenderTime:(CFAbsoluteTime)time
{
	renderTime = time;
}

- (void) startAnimation
{
	if (!isAnimating)
	{
		if (!isInFullScreenMode)
			[openGLView startAnimation];
		else
			[fullScreenView startAnimation];

		isAnimating = YES;
	}
}

- (void) stopAnimation
{
	if (isAnimating)
	{
		if (!isInFullScreenMode)
			[openGLView stopAnimation];
		else
			[fullScreenView stopAnimation];

		isAnimating = NO;
	}
}

- (void) toggleAnimation
{
	if (isAnimating)
		[self stopAnimation];
	else
		[self startAnimation];
}

- (void) keyDown:(NSEvent *)event
{
//    unichar c = [[event charactersIgnoringModifiers] characterAtIndex:0];
//    switch (c) {
//			
//            // [Esc] exits full-screen mode
//        case 27:
//			if (isInFullScreenMode)
//				[self goWindow];
//            break;
//			
//        default:
//            break;
//    }
}

// Holding the mouse button and dragging the mouse changes the "roll" angle (y-axis) and the direction from which sunlight is coming (x-axis).
- (void)mouseDown:(NSEvent *)theEvent
{
//    BOOL dragging = YES;
//    NSPoint windowPoint;
//    NSPoint lastWindowPoint = [theEvent locationInWindow];
//    float dx, dy;
//	BOOL wasAnimating = isAnimating;
//	
//    if (wasAnimating) {
//        [self stopAnimation];
//    }
//	
//    while (dragging)
//	{
//        theEvent = [[openGLView window] nextEventMatchingMask:NSLeftMouseUpMask | NSLeftMouseDraggedMask];
//        windowPoint = [theEvent locationInWindow];
//        switch ([theEvent type])
//		{
//            case NSLeftMouseUp:
//                dragging = NO;
//                break;
//				
//            case NSLeftMouseDragged:
//                dx = windowPoint.x - lastWindowPoint.x;
//                dy = windowPoint.y - lastWindowPoint.y;
//                [scene setSunAngle:[scene sunAngle] - 1.0 * dx];
//                [scene setRollAngle:[scene rollAngle] - 0.5 * dy];
//                lastWindowPoint = windowPoint;
//				
//				if (isInFullScreenMode) {
//#if MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_5
//					[fullScreenView display];
//#else
//                    [scene render];
//                    CGLFlushDrawable(fullScreenContextObj);
//#endif
//                }
//				else {
//					[openGLView display];
//				}
//                break;
//				
//            default:
//                break;
//        }
//    }
//	
//    if (wasAnimating) {
//        [self startAnimation];
//        renderTime = CFAbsoluteTimeGetCurrent();
//    }
}

@end