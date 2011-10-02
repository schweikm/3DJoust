/*
 *  template.mm
 *  template
 *
 *  Created by SIO2 Interactive on 8/22/08.
 *  Copyright 2008 SIO2 Interactive. All rights reserved.
 *
 */

#include "template.h"

#include "../src/sio2/sio2.h"

#import "GameObject.h"
#import "ModelObject.h"
#import "TestState.h"
#import "PlayState.h"

GameState* gCurrentGameState = nil;

void templateRender( void )
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClearColor(0.2, 0.2, 1.0, 0); 
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	
	// Use the helper function sio2ResourceGet in order to get
	// the pointer to a specific resource within a specific
	// SIO2resource.
	SIO2camera *_SIO2camera = ( SIO2camera * )sio2ResourceGet( sio2->_SIO2resource,
															   SIO2_CAMERA,
															   "camera/Camera" );

	if(gCurrentGameState && gCurrentGameState->mDone) {
		[gCurrentGameState release];
		gCurrentGameState = [[PlayState alloc] init];
	}
	// Make sure that we found the camera
	if( _SIO2camera )
	{
		// Adjust the perspective, please take not
		// that this operation should only be done 
		// once everytime you are switching cameras.
		sio2CameraSetPerspective( _SIO2camera, sio2->_SIO2window );

		// Enter the 3D landscape mode
		sio2WindowEnterLandscape3D();
		{
			// Render our camera.
			
			
			[gCurrentGameState render];
			
			// Render all solid object in our scene, please
			// take not that the following types are available
			// for rendering (if you scene contain them)
			//
			//
			//	SIO2_RENDER_SOLID_OBJECT: Render all the solid objects.
			//
			//	SIO2_RENDER_ALPHA_OBJECT: Render all the alpha objects. Objects that contain
			//	alpha blending and that need to be sorted.
			//
			//	SIO2_RENDER_CLIPPED_OBJECT: Render all objects that are not currently
			//	in the frustum. In the case that physic is ON you should also render them
			//	to update the physic data of the object to create a realistic physic simulation.
			//
			//	SIO2_RENDER_LAMP: Render all the lights (only if sio2LampEnableLight have been toggled)
			//
			//	SIO2_RENDER_EMITTER: Render all the emitters (particle system)
			//
//			sio2ResourceRender( sio2->_SIO2resource,
//								sio2->_SIO2window,
//								_SIO2camera,
//								SIO2_RENDER_SOLID_OBJECT );
		}
		// Leave the landscape mode.
		sio2WindowLeaveLandscape3D();
	}
}


void templateLoading( void )
{
	unsigned int i = 0;
	
	// WARNING: Concerning the exporter please take 
	// note that ONLY the SELECTED objects that are
	// in layer #1 will be exported. Any other objects
	// located in other layers will be ignored. Please
	// make sure that the objects that you are trying
	// to export are in the layer #1 by:
	//
	// 1. Push 'a' twice to select everything
	// 2. Push 'm' + '1' to send the objects to layer #1
	// 3. Make your selection to export.
	// 4. Click 'Export'
	//
	// v1.2: The new fileformat is now using text
	// since alot of future problem immerse as I
	// was developing the second revision of 
	// ir. From now on the file format will be
	// backward and forward compatible. The following
	// line initalize the dictionary used by the
	// parser in order to dispatch the root tags etc...
	// to the appropriate load functions.
	sio2ResourceCreateDictionary( sio2->_SIO2resource );

	// Open the archive file bundled withing
	// the .app, pass 1 to the function in order
	// to specify to open this archive that is
	// relative to the executable. In order to 
	// integrate file and distribute them with
	// your application simply drag & drop them
	// into the resource directory.
	sio2ResourceOpen( sio2->_SIO2resource,

					  "joust_artwork.sio2", 1 );
//					 "cart_resBa.sio2", 1);
	// Loop into the archive extracting all the 
	// resources compressed within the fileformat.
	while( i != sio2->_SIO2resource->gi.number_entry )
	{
		// Extract the current file selected within
		// the archive package and put the pointer to 
		// the next one.
		sio2ResourceExtract( sio2->_SIO2resource, NULL );
		++i;
	}
	
	// We are done with the file so close the stream.
	sio2ResourceClose( sio2->_SIO2resource );

	sio2ResourceResetState();
	
	sio2ResourceBindAllImages( sio2->_SIO2resource );
	
	sio2ResourceBindAllMaterials( sio2->_SIO2resource );

	// v1.2
	// It is now required to bind the initial matrix manually,
	// for optimization purpose and to avoid matrix scale
	// clash with Bullet.
	sio2ResourceBindAllMatrix( sio2->_SIO2resource );
	

	// Generate the geometry VBO.
	sio2ResourceGenId( sio2->_SIO2resource );
	
	// Reset all resource state pointer.
	sio2ResourceResetState();
	
	/****************************************************
	 * instantiate GameState in app delegate / playGame *
	 ****************************************************/
	
	// Set our rendering callback to the templateRender
	// function.
	sio2->_SIO2window->_SIO2windowrender = templateRender;
}


void templateShutdown( void )
{
	[gCurrentGameState release];
	
	sio2ResourceUnloadAll( sio2->_SIO2resource );

	sio2->_SIO2resource = sio2ResourceFree( sio2->_SIO2resource );
	
	sio2->_SIO2window = sio2WindowFree( sio2->_SIO2window );

	sio2 = sio2Shutdown();

	printf("\nSIO2: shutdown...\n" );
}


vec2 start;
void templateScreenTap( void *_ptr, unsigned char _state )
{
	if( sio2->_SIO2window->n_touch )
	{
		start.x = sio2->_SIO2window->touch[ 0 ].x;
		start.y = sio2->_SIO2window->touch[ 0 ].y;
		[gCurrentGameState processTouchX:start.x Y:start.y];
	}
}


void templateScreenTouchMove( void *_ptr )
{
	if(gCurrentGameState) {
		float dx = sio2->_SIO2window->touch[ 0 ].x - start.x;
		float dy = sio2->_SIO2window->touch[ 0 ].y - start.y;
		start.x = sio2->_SIO2window->touch[ 0 ].x;
		start.y = sio2->_SIO2window->touch[ 0 ].y;
		[gCurrentGameState processTouchMoveX:dx Y:dy];
		[gCurrentGameState processTouchX:start.x Y:start.y];
	}
/*	
	if( sio2->_SIO2window->n_touch )
	{
		float d = sio2->_SIO2window->touch[ 0 ].x - start.x;
		
		// Get the object Suzanne located inside our resources.
		SIO2object *_SIO2object = ( SIO2object * )sio2ResourceGet( sio2->_SIO2resource,
																   SIO2_OBJECT,
																   "object/Suzanne" );
		// Check if we get a pointer.
		if( _SIO2object )
		{
			// Apply a rotation based on the
			// touch movement.
			if( d > 5.0f || d < -5.0f )
			{ _SIO2object->_SIO2transform->rot->z += ( d * 0.025f ); }
			
			// Update the OpenGL matrix and apply the
			// new rotation specified above.
			sio2TransformBindMatrix( _SIO2object->_SIO2transform );
		}
	}
 */
}


void templateScreenAccelerometer( void *_ptr )
{
#ifndef USE_SIMULATOR
	if(gCurrentGameState) {
		[gCurrentGameState processAccelX:sio2->_SIO2window->accel->x Y:sio2->_SIO2window->accel->y Z:sio2->_SIO2window->accel->z];
	}
	/*
 if( sio2->_SIO2window->accel->y > 0.1f || sio2->_SIO2window->accel->y < -0.1f )
	{
		// Use the Y axis of the accelerometer
		// for camera Z rotation.
		float tmp = sio2->_SIO2window->accel->y * SENSITIVITY;
		
		if( sio2->_SIO2window->accel->y > 0.0 )
		{ ROTZ_DIR = -1; }
		else if( sio2->_SIO2window->accel->y < 0.0 )
		{ ROTZ_DIR = 1; }
		
		if( abs( tmp ) > abs( SMOOTH_Z ) )
		{ SMOOTH_Z = abs( tmp ) * SMOOTH_FACTOR; }
		
		ROTZ -= tmp;
	}
*/	
#endif
	

}
