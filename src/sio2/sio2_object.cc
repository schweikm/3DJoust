/*

[ EULA: Revision date: 2009/03/22 ]

SIO2 Engine 3D Game for iPhone & iPod Touch :: Free Edition

Copyright (C) 2009 SIO2 Interactive http://sio2interactive.com

This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use
of this software.

Permission is granted to anyone to use this software for any purpose, including
free or commercial applications, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software. 

If you are using the "Free Edition" of this software in a product (either free
or commercial), you are required to display a full-screen "Powered by SIO2 engine"
splash screen logo in the start up sequence of any product created and released
with the SIO2 Engine.

This screen shall be visible for no less than two (2) seconds, using one (1) of
the two (2) files provided with the SIO2 SDK:

(a) "/SIO2_SDK/src/poweredby_p.jpg" for portrait

(b) "/SIO2_SDK/src/poweredby_l.jpg" for landscape.

2. Altered source versions must be plainly marked as such (even for internal use),
and must not be misrepresented as being the original software. You are also invited
to post any modifications done to the SIO2 source, at the following email
address: sio2interactive@gmail.com, for review and possible addition to the SIO2
source tree to make them available to the community and to make SIO2 a better
software. But it is not required to do so.

3. This notice may not be removed or altered from any source distribution.

4. If your product using SIO2 Engine "Free Edition" is made available to the
public ( either in a free or commercial form ) you are required to let us know
by email (sio2interactive@gmail.com) the following information:

- The title of your product

- A short description of your product

- A valid URL and screenshot(s) of the product in order for us to put it on our
website (http://sio2interactive.com/GAMES.html) in order to help you promote
your creation(s) as well as promoting the SIO2 project.

If you have any questions or want more information concerning this agreement
please send us an email at: sio2interactive@gmail.com

SIO2 Engine is using other external library and source packages and their
respective license(s), as well as this one, can be found in the 
"/SIO2_SDK/src/LICENSE/" directory, please review all the licenses before
making your product available.




[ EULA: Revision date: 2009/03/23 ]

SIO2 Engine 3D Game for iPhone & iPod Touch :: Indie Edition

Copyright (C) 2009 SIO2 Interactive http://sio2interactive.com

This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use
of this software.

Permission is granted to anyone to use this software for free or commercial applications,
subject to the following restrictions:

1. By using the "SIO2 Indie Edition" you are required to use and include the "sio2.cert"
certificate within your application on a game basis. The certificate will be send to you to
the email that you provide within the purchase form in the next two (2) working days. Certificate
is restricted on a per application basis, you CANNOT reuse the certificate for multiple game
production.

2. By using the "SIO2 Indie Edition" you are entitled of a life time free upgrade to any
subsequent SIO2 versions on a game basis prior to the initial purchase date. Every time
a new version is made available you will receive notification by email within two (2) 
working days after its official release.

3. You must use an independent certificate for every game that you release, either free or
commercial.

4. By using the "SIO2 Indie Edition" you are NOT required to use any splash screen, or
mention of any kind of SIO2 Engine or SIO2 Interactive within your application.

5. By using the "SIO2 Indie Edition" you are entitled to receive customer support and
customer service within working hours (either on IM or by email at sio2interactive@gmail.com).
Every requests will be answered within 48 hours or two (2) working days.

6. You are required to NOT clear the console output and do not override the system log in
order to display at any time on the console prompt the information that your "sio2.cert"
hold, such as your "Game Studio" and "Game Title" as well as your unique certificate key
bundle within your ".app".

7. If your product using SIO2 Engine "Indie Edition" is made available to the public
( either in a free or commercial form ) you are invited to let us know by email
(sio2interactive@gmail.com) the following information:

- The title of your product

- A short description of your product

- A valid URL and screenshot(s) of the product in order for us to put it on our
website (http://sio2interactive.com/GAMES.html) in order to help you promote
your creation(s) as well as promoting the SIO2 project.

But it is NOT required to do so.

If you have any questions or want more information concerning this agreement
please send us an email at: sio2interactive@gmail.com

SIO2 Engine is using other external library and source packages and their
respective license(s), as well as this one, can be found in the 
"/SIO2_SDK/src/LICENSE/" directory, please review all the licenses before
making your product available.

*/

#include "sio2.h"


SIO2object *sio2ObjectInit( char *_name )
{
	SIO2object *_SIO2object = ( SIO2object * ) calloc( 1, sizeof( SIO2object ) );

	sio2StringCpy( _SIO2object->name, _name );
	
	_SIO2object->dim = sio2Vec3Init();
	
	_SIO2object->col = sio2Col4Init();
	_SIO2object->col->a = 255;
	
	_SIO2object->damp = 0.04f;
	
	_SIO2object->rotdamp = 0.1f;

	_SIO2object->dst = 1.0f;

	_SIO2object->_SIO2transform = sio2TransformInit();
	
	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_OBJECT,
					 ( void * )_SIO2object );
	
	return _SIO2object;
}


SIO2object *sio2ObjectFree( SIO2object *_SIO2object )
{
	unsigned int i = 0;

	_SIO2object->dim = sio2Vec3Free( _SIO2object->dim );	
	_SIO2object->col = sio2Col4Free( _SIO2object->col );
	
	_SIO2object->_SIO2transform = sio2TransformFree( _SIO2object->_SIO2transform );
				
	glDeleteBuffers( 1, &_SIO2object->vbo );


	while( i != _SIO2object->n_vgroup )
	{ 
		_SIO2object->_SIO2vertexgroup[ i ] = sio2VertexGroupFree( _SIO2object->_SIO2vertexgroup[ i ] );
		++i;
	}
	
	if( _SIO2object->_SIO2vertexgroup )
	{
		free( _SIO2object->_SIO2vertexgroup );
		_SIO2object->_SIO2vertexgroup = NULL;
	}
	

	i = 0;
	while( i != _SIO2object->n_sound )
	{
		_SIO2object->_SIO2sound[ i ] = sio2SoundFree( _SIO2object->_SIO2sound[ i ] );
		++i;
	}	

	
	if( _SIO2object->_SIO2sound )
	{
		free( _SIO2object->_SIO2sound );
		_SIO2object->_SIO2sound = NULL;
	}


	if( _SIO2object->_btTriangleMesh )
	{
		delete _SIO2object->_btTriangleMesh;
		_SIO2object->_btTriangleMesh = NULL;
	}


	i = 0;
	while( i != _SIO2object->n_frame )
	{
		_SIO2object->_SIO2frame[ i ] = sio2FrameFree( _SIO2object->_SIO2frame[ i ] );
	
		++i;
	}


	if( _SIO2object->_SIO2frame )
	{
		free( _SIO2object->_SIO2frame );
		_SIO2object->_SIO2frame = NULL;
	}
	
	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_OBJECT,
					 (void *)_SIO2object );


	free( _SIO2object );
	
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
	
	return NULL;
}


unsigned char sio2ObjectLoad( char *_root,
							  char *_tok,
							  char *_val )
{
	unsigned int i = 0;
	
	static int curr_vgp,
			   curr_fra;
	
	static unsigned int boffset,
						ioffset;
	
	static const unsigned int n_token = 32;

	static char *token[ n_token ] = { "vert"      , "vcol"      , "vnor"      , "uv0"       , "uv1"     ,
									  "ind"       , "vbo_offset", "n_vgroup"  , "vgroup"    , "mname"   ,
									  "n_ind"     , "loc"       , "rot"       , "scl"       , "rad"     ,
									  "flags"     , "bounds"    , "mass"      , "damp"      , "rotdamp" ,
									  "margin"    , "dim"	     , "instname"  , "iponame"  , "linstiff",
									  "shapematch", "bendconst" , "citeration", "piteration", "n_frame" ,
									  "frame"     , "fvert"  };

	if( !*_tok )
	{
		char name[ SIO2_MAX_CHAR ] = {""};
		sio2StringScanf( _val, "%s", name );
		sio2->_SIO2object = sio2ObjectInit( name );
		
		return 1;
	}
	

	while( i != n_token )
	{
		if( !sio2StringCmp( _tok, token[ i ] ) )
		{ break; }
		
		++i;
	}


	switch( i )
	{
		case 0:
		case 2:
		{
			vec3 v;
					
			sio2StringScanf( _val, "%f%f%f", &v.x,
											 &v.y,
											 &v.z );
			
			memcpy( &sio2->_SIO2object->buf[ boffset ], &v, 12 );
			boffset += 12;
			
			return 1;
		}
		
		case 1:
		{
			col4 c;
			
			c.a = 255;
			
			sio2StringScanf( _val, "%c%c%c", &c.r,
											 &c.g,
											 &c.b );
			
			memcpy( &sio2->_SIO2object->buf[ boffset ], &c, 4 );
			boffset += 4;
			
			return 1;
		}		

		case 3:
		case 4:
		{
			vec2 u;
					
			sio2StringScanf( _val, "%f%f", &u.x,
										   &u.y );
			
			memcpy( &sio2->_SIO2object->buf[ boffset ], &u, 8 );
			boffset += 8;
			
			return 1;
		}
		
		case 5:
		{
			ind3 e;
			
			sio2StringScanf( _val, "%h%h%h", &e.x,
											 &e.y,
											 &e.z );
			
			memcpy( &sio2->_SIO2object->_SIO2vertexgroup[ curr_vgp ]->ind[ ioffset ], &e, 6 );
			
			ioffset += 3;
			
			return 1;
		}		
		
		case 6:
		{
			sio2StringScanf( _val, "%d%d%d%d%d", &sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_SIZE    ],
												 &sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_VCOLOR  ],
												 &sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ],
												 &sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV0  ],
												 &sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV1  ] );
			
			sio2->_SIO2object->buf = ( unsigned char * ) malloc( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_SIZE ] );
			
			boffset = 0;
			
			return 1;
		}		
		
		case 7:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2object->n_vgroup );
			sio2->_SIO2object->_SIO2vertexgroup = ( SIO2vertexgroup ** ) malloc( sio2->_SIO2object->n_vgroup * sizeof( SIO2vertexgroup ) );
			
			curr_vgp = -1;
			
			return 1;
		}
		
		case 8:
		{
			char name[ SIO2_MAX_CHAR ] = {""};
			sio2StringScanf( _val, "%s", name );
				
			++curr_vgp;
			sio2->_SIO2object->_SIO2vertexgroup[ curr_vgp ] = sio2VertexGroupInit( name );
			
			return 1;
		}		

		case 9:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2object->_SIO2vertexgroup[ curr_vgp ]->mname );
			
			return 1;
		}
				
		case 10:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2object->_SIO2vertexgroup[ curr_vgp ]->n_ind );
			
			sio2->_SIO2object->_SIO2vertexgroup[ curr_vgp ]->ind = ( unsigned short * ) malloc( sio2->_SIO2object->_SIO2vertexgroup[ curr_vgp ]->n_ind << 1 );
			
			ioffset = 0;
			
			return 1;
		}		
		
		case 11:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2object->_SIO2transform->loc->x,
											 &sio2->_SIO2object->_SIO2transform->loc->y,
											 &sio2->_SIO2object->_SIO2transform->loc->z );
			return 1;
		}
		
		case 12:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2object->_SIO2transform->rot->x,
											 &sio2->_SIO2object->_SIO2transform->rot->y,
											 &sio2->_SIO2object->_SIO2transform->rot->z );		
			return 1;
		}
		
		case 13:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2object->_SIO2transform->scl->x,
											 &sio2->_SIO2object->_SIO2transform->scl->y,
											 &sio2->_SIO2object->_SIO2transform->scl->z );		
			return 1;
		}
		
		case 14:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2object->rad );		
			return 1;
		}
		
		case 15:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2object->flags );		
			return 1;
		}
		
		case 16:
		{
			sio2StringScanf( _val, "%c", &sio2->_SIO2object->bounds );		
			return 1;
		}
		
		case 17:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2object->mass );		
			return 1;
		}
		
		case 18:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2object->damp );		
			return 1;
		}

		case 19:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2object->rotdamp );		
			return 1;
		}

		case 20:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2object->margin );		
			return 1;
		}
				
		case 21:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2object->dim->x,
											 &sio2->_SIO2object->dim->y,
											 &sio2->_SIO2object->dim->z );		
			return 1;
		}

		case 22:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2object->instname );		
			return 1;
		}
		
		case 23:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2object->iponame );		
			return 1;
		}
		
		case 24:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2object->linstiff );		
			return 1;
		}

		case 25:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2object->shapematch );		
			return 1;
		}
		
		case 26:
		{
			sio2StringScanf( _val, "%c", &sio2->_SIO2object->bendconst );		
			return 1;
		}

		case 27:
		{
			sio2StringScanf( _val, "%c", &sio2->_SIO2object->citeration );		
			return 1;
		}
	
		case 28:
		{
			sio2StringScanf( _val, "%c", &sio2->_SIO2object->piteration );		
			return 1;
		}
		
		case 29:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2object->n_frame );
			
			sio2->_SIO2object->_SIO2frame = ( SIO2frame ** ) malloc( sio2->_SIO2object->n_frame * sizeof( SIO2frame ) );
			
			curr_fra = -1;

			return 1;
		}
		
		case 30:
		{
			char name[ SIO2_MAX_CHAR ] = {""};
			
			unsigned int frame = 0;
			
			unsigned int size = sio2ObjectGetNumVert( sio2->_SIO2object ) * 12;
			
			sio2StringScanf( _val, "%d%s", &frame, name );
				
			++curr_fra;
			sio2->_SIO2object->_SIO2frame[ curr_fra ] = sio2FrameInit( name, frame, size );
		
			boffset = 0;

			return 1;
		}
		
		case 31:
		{
			vec3 v;
			
			sio2StringScanf( _val, "%f%f%f", &v.x,
											 &v.y,
											 &v.z );
			
			memcpy( &sio2->_SIO2object->_SIO2frame[ curr_fra ]->buf[ boffset ], &v, 12 );
			boffset += 12;

			return 1;
		}
	}
	
	return 0;
}


void sio2ObjectGenId( SIO2object *_SIO2object )
{	
	if( _SIO2object->vbo_offset[ SIO2_OBJECT_SIZE ] )
	{
		int btype = sio2IsEnabled( _SIO2object->flags, SIO2_OBJECT_SOFTBODY ) || _SIO2object->n_frame ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
		
		glGenBuffers( 1, &_SIO2object->vbo );
		
		glBindBuffer( GL_ARRAY_BUFFER, _SIO2object->vbo );

		glBufferData( GL_ARRAY_BUFFER,
					  _SIO2object->vbo_offset[ SIO2_OBJECT_SIZE ],
					  &_SIO2object->buf[ 0 ],
					  btype );

		free( _SIO2object->buf );
		_SIO2object->buf = NULL;
	}
	
	
	sio2ObjectUpdateType( _SIO2object );	
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2ObjectBindSound( SIO2object *_SIO2object )
{
	unsigned int i = 0;
	
	SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object;
	
	while( i != tmp->n_vgroup )
	{
		if( tmp->_SIO2vertexgroup[ i ]->_SIO2material &&
			tmp->_SIO2vertexgroup[ i ]->_SIO2material->_SIO2soundbuffer )
		{
			char name[ SIO2_MAX_CHAR ] = {""};
			
			++_SIO2object->n_sound;
			_SIO2object->_SIO2sound = ( SIO2sound ** ) realloc( _SIO2object->_SIO2sound, _SIO2object->n_sound * sizeof( SIO2sound ) );
			
			sprintf( name, "%s%d", _SIO2object->name, ( _SIO2object->n_sound - 1 ) );
			
			_SIO2object->_SIO2sound[ _SIO2object->n_sound - 1 ] = sio2SoundInit( name );

			sio2SoundGenId( _SIO2object->_SIO2sound[ _SIO2object->n_sound - 1 ],
							_SIO2object->_SIO2vertexgroup[ i ]->_SIO2material->_SIO2soundbuffer,
							_SIO2object->_SIO2vertexgroup[ i ]->_SIO2material->sflags );
			
			if( sio2IsEnabled( _SIO2object->_SIO2sound[ _SIO2object->n_sound - 1 ]->flags, SIO2_SOUND_FX ) )
			{
				sio2SoundSetFx( _SIO2object->_SIO2sound[ _SIO2object->n_sound - 1 ],
								_SIO2object->_SIO2transform->loc,
								_SIO2object->rad );
			}


			if( sio2IsEnabled( _SIO2object->_SIO2sound[ _SIO2object->n_sound - 1 ]->flags, SIO2_SOUND_AUTOPLAY ) )
			{ sio2SoundPlay( _SIO2object->_SIO2sound[ _SIO2object->n_sound - 1 ] ); }
		}
		
		++i;
	}
}


unsigned char sio2ObjectRender( SIO2object    *_SIO2object,
								SIO2window	  *_SIO2window,
								SIO2camera    *_SIO2camera,
								unsigned char  _usematerial,
								unsigned char  _usematrix )
{
	unsigned int i = 0;


	if( _SIO2object->_SIO2ipo )
	{
		sio2TransformSetLoc( _SIO2object->_SIO2transform,
							 _SIO2object->_SIO2ipo->_SIO2transform->loc );

		sio2TransformSetRot( _SIO2object->_SIO2transform,
							 _SIO2object->_SIO2ipo->_SIO2transform->rot );

		sio2TransformSetScl( _SIO2object->_SIO2transform,
							 _SIO2object->_SIO2ipo->_SIO2transform->scl );
							 
		sio2TransformSetMat( _SIO2object->_SIO2transform,
							 _SIO2object->_SIO2ipo->_SIO2transform->mat );
		
		if( _SIO2object->_btRigidBody )
		{ _SIO2object->_btRigidBody->getWorldTransform().setFromOpenGLMatrix( _SIO2object->_SIO2transform->mat ); }
	}

	else if( _SIO2object->_btRigidBody || _SIO2object->_btSoftBody )
	{
		if( _SIO2object->_btSoftBody )
		{
			btSoftBody::tNodeArray &_tNodeArray( _SIO2object->_btSoftBody->m_nodes );

			_SIO2object->buf = ( unsigned char * )sio2MapBuffer( _SIO2object->vbo, GL_ARRAY_BUFFER );
			{
				while( i != _tNodeArray.size() )
				{
					memcpy( &_SIO2object->buf[ i * 12 ], _tNodeArray[ i ].m_x, 12 );
					++i;
				}
				
				
				if( _SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] )
				{
					i = 0;
					while( i != _tNodeArray.size() )
					{
						memcpy( &_SIO2object->buf[ _SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] + ( i * 12 ) ], _tNodeArray[ i ].m_n, 12 );
						++i;
					}
				}
			}
			sio2UnmapBuffer( GL_ARRAY_BUFFER );
			_SIO2object->buf = NULL;

			_SIO2object->_btSoftBody->getWorldTransform().getOpenGLMatrix( _SIO2object->_SIO2transform->mat );
			
			_SIO2object->_SIO2transform->loc->x += _tNodeArray[ 0 ].m_x.getX() - _tNodeArray[ 0 ].m_q.getX();
			_SIO2object->_SIO2transform->loc->y += _tNodeArray[ 0 ].m_x.getY() - _tNodeArray[ 0 ].m_q.getY();
			_SIO2object->_SIO2transform->loc->z += _tNodeArray[ 0 ].m_x.getZ() - _tNodeArray[ 0 ].m_q.getZ();
		}

		else if(  !_SIO2object->_btRigidBody->isStaticObject() &&
				 ( _SIO2object->_btRigidBody->getActivationState() == DISABLE_DEACTIVATION ||
				   _SIO2object->_btRigidBody->getActivationState() == ACTIVE_TAG ) )
		{
			_SIO2object->_btRigidBody->getWorldTransform().getOpenGLMatrix( _SIO2object->_SIO2transform->mat );

			_SIO2object->_SIO2transform->mat[ 0  ] *= _SIO2object->_SIO2transform->scl->x;
			_SIO2object->_SIO2transform->mat[ 1  ] *= _SIO2object->_SIO2transform->scl->x;
			_SIO2object->_SIO2transform->mat[ 2  ] *= _SIO2object->_SIO2transform->scl->x;

			_SIO2object->_SIO2transform->mat[ 4  ] *= _SIO2object->_SIO2transform->scl->y;
			_SIO2object->_SIO2transform->mat[ 5  ] *= _SIO2object->_SIO2transform->scl->y;
			_SIO2object->_SIO2transform->mat[ 6  ] *= _SIO2object->_SIO2transform->scl->y;
			
			_SIO2object->_SIO2transform->mat[ 8  ] *= _SIO2object->_SIO2transform->scl->z;
			_SIO2object->_SIO2transform->mat[ 9  ] *= _SIO2object->_SIO2transform->scl->z;
			_SIO2object->_SIO2transform->mat[ 10 ] *= _SIO2object->_SIO2transform->scl->z;

			_SIO2object->_SIO2transform->loc->x = _SIO2object->_SIO2transform->mat[ 12 ];
			_SIO2object->_SIO2transform->loc->y = _SIO2object->_SIO2transform->mat[ 13 ];
			_SIO2object->_SIO2transform->loc->z = _SIO2object->_SIO2transform->mat[ 14 ];
		}
	}


	if( _SIO2object->n_frame )
	{
		sio2ObjectRenderFrame( _SIO2object,
							   _SIO2window );
	}

	
	i = 0;
	while( i != _SIO2object->n_sound )
	{
		sio2SoundUpdateState( _SIO2object->_SIO2sound[ i ] );
		
		if( _SIO2object->_SIO2sound[ i ]->flags == SIO2_SOUND_PLAY && 
			sio2IsEnabled( _SIO2object->_SIO2sound[ i ]->flags, SIO2_SOUND_FX ) )
		{
			sio2SoundSetFx( _SIO2object->_SIO2sound[ i ],
							_SIO2object->_SIO2transform->loc,
							_SIO2object->rad );
		}
		
		++i;
	}


	if( sio2IsEnabled( _SIO2object->flags, SIO2_OBJECT_GHOST ) )
	{ return 0; }

	if( _SIO2object->dst < 0.0f )
	{ return 0; }


	glPushMatrix();
	{
		SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object;

		if( !_usematrix )
		{ sio2TransformApply( _SIO2object->_SIO2transform ); }
		
		else if( _usematrix == 1 )
		{ sio2TransformRender( _SIO2object->_SIO2transform ); }
		
		if( sio2IsEnabled( _SIO2object->flags, SIO2_OBJECT_BILLBOARD | SIO2_OBJECT_HALO ) )
		{
			sio2ObjectBillboard( _SIO2object,
								 _SIO2camera->_SIO2transform->loc );
		}
		
		
		if( sio2->_SIO2object != tmp )
		{
			sio2->_SIO2object = tmp;

			sio2ObjectBindVBO( tmp,
							   _usematerial );
		}
		
		
		i = 0;
		while( i != tmp->n_vgroup )
		{
			if( !sio2IsEnabled( tmp->flags, SIO2_OBJECT_TWOSIDE ) )
			{
				sio2VertexGroupRender( tmp->_SIO2vertexgroup[ i ],
									   _usematerial );		
			}
			else
			{
				glCullFace( GL_FRONT );
						
				sio2VertexGroupRender( tmp->_SIO2vertexgroup[ i ],
									   _usematerial );
									   
				glCullFace( GL_BACK );
				
				sio2VertexGroupRender( tmp->_SIO2vertexgroup[ i ],
									   _usematerial );
			}
			
			++i;
		}
	}
	glPopMatrix();

	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
	
	return 1;
}


void sio2ObjectRenderFrame( SIO2object *_SIO2object,
							SIO2window *_SIO2window )
{
	if( _SIO2object->state == SIO2_OBJECT_PLAY )
	{
		unsigned int i = 0;
	
		_SIO2object->d_time += _SIO2window->d_time;
		
		if( _SIO2object->d_time >= _SIO2object->t_ratio )
		{
			++_SIO2object->curr_frame;
			++_SIO2object->next_frame;
			
			
			if( _SIO2object->loop == 2 || _SIO2object->next_action )
			{
				_SIO2object->loop = 1;
				_SIO2object->next_action = 0;
				
				_SIO2object->curr_frame = _SIO2object->start_frame;
				_SIO2object->next_frame = _SIO2object->start_frame + 1;
			}
			
			else if( _SIO2object->curr_frame == _SIO2object->end_frame )
			{
				if( _SIO2object->loop )
				{
					_SIO2object->loop = 2;
					
					_SIO2object->next_frame = _SIO2object->start_frame;
				
					_SIO2object->t_ratio = _SIO2object->inter;
					
					_SIO2object->d_time = 0.0f;
					
					goto render;
				}
				else
				{
					--_SIO2object->curr_frame;
					--_SIO2object->next_frame;				
					
					sio2ObjectPause( _SIO2object );
					
					goto render;
				}
			}
			
			
			sio2ObjectUpdateTimeRatio( _SIO2object );
			_SIO2object->d_time = 0.0f;			
		}

		
render:
		
		_SIO2object->buf = ( unsigned char * )sio2MapBuffer( _SIO2object->vbo, GL_ARRAY_BUFFER );
		{
			SIO2frame *_SIO2frame1 = _SIO2object->_SIO2frame[ _SIO2object->curr_frame ],
					  *_SIO2frame2 = _SIO2object->_SIO2frame[ _SIO2object->next_frame ];
				
			vec3 c,
				 n;
			
			float v_ratio = _SIO2object->d_time / _SIO2object->t_ratio;
			
			unsigned int n_vert = sio2ObjectGetNumVert( _SIO2object );
			
			while( i != n_vert )
			{
				if( !_SIO2object->next_action )
				{ memcpy( &c, &_SIO2frame1->buf[ i * 12 ], 12 ); }
				else
				{ memcpy( &c, &_SIO2object->buf[ i * 12 ], 12 ); }
				
				
				memcpy( &n, &_SIO2frame2->buf[ i * 12 ], 12 );	
				
				c.x += v_ratio * ( n.x - c.x );
				c.y += v_ratio * ( n.y - c.y );
				c.z += v_ratio * ( n.z - c.z );				

				memcpy( &_SIO2object->buf[ i * 12 ], &c, 12 );
			
				++i;
			}
		}
		sio2UnmapBuffer( GL_ARRAY_BUFFER );
		
		_SIO2object->buf = NULL;
	}
}


void sio2ObjectBindVBO( SIO2object    *_SIO2object,
						unsigned char  _usematerial )
{
	glBindBuffer( GL_ARRAY_BUFFER,
				  _SIO2object->vbo );

	glVertexPointer( 3,
					 GL_FLOAT,
					 0,
					 (void *)NULL );
	
	if( _usematerial )
	{
		if( _SIO2object->vbo_offset[ SIO2_OBJECT_VCOLOR ] )
		{
			if( !glIsEnabled( GL_COLOR_ARRAY ) )
			{ glEnableClientState( GL_COLOR_ARRAY ); }
			
			glColorPointer( 4,
							GL_UNSIGNED_BYTE,
							0,
							(void *)SIO2_BUFFER_OFFSET( _SIO2object->vbo_offset[ SIO2_OBJECT_VCOLOR ] ) );
		}
		else
		{
			if( glIsEnabled( GL_COLOR_ARRAY ) )
			{ glDisableClientState( GL_COLOR_ARRAY ); }
		}


		if( glIsEnabled( GL_LIGHTING ) )
		{
			if( _SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] )
			{
				if( !glIsEnabled( GL_NORMAL_ARRAY ) )
				{ glEnableClientState( GL_NORMAL_ARRAY ); }
				
				glNormalPointer( GL_FLOAT,
								 0,
								 SIO2_BUFFER_OFFSET( _SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] ) );
			}
			else
			{
				if( glIsEnabled( GL_NORMAL_ARRAY ) )
				{ glDisableClientState( GL_NORMAL_ARRAY ); }	
			}
		}
		

		glClientActiveTexture( GL_TEXTURE0 );
		
		if( _SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV0 ] )
		{
			if( !glIsEnabled( GL_TEXTURE_COORD_ARRAY ) )
			{ glEnableClientState( GL_TEXTURE_COORD_ARRAY ); }
			
			glTexCoordPointer( 2,
							   GL_FLOAT,
							   0,
							   SIO2_BUFFER_OFFSET( _SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV0 ] ) );	
		}
		else
		{
			if( glIsEnabled( GL_TEXTURE_COORD_ARRAY ) )
			{ glDisableClientState( GL_TEXTURE_COORD_ARRAY ); }		
		}
		

		glClientActiveTexture( GL_TEXTURE1 );
		
		if( _SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV1 ] )
		{
			if( !glIsEnabled( GL_TEXTURE_COORD_ARRAY ) )
			{ glEnableClientState( GL_TEXTURE_COORD_ARRAY ); }
			
			glTexCoordPointer( 2,
							   GL_FLOAT,
							   0,
							   SIO2_BUFFER_OFFSET( _SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV1 ] ) );		
		}
		else
		{
			if( glIsEnabled( GL_TEXTURE_COORD_ARRAY ) )
			{ glDisableClientState( GL_TEXTURE_COORD_ARRAY ); }		
		}
	}
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2ObjectBillboard( SIO2object *_SIO2object,
						  vec3		 *_vec )
{
	float c_angle,
		  s_angle;
	
	vec3 dir,
		 objdir,
		 rot;

	dir.x = dir.z = objdir.z = 0.0f;
	dir.y = 1.0f;
	
	objdir.x = _vec->x - _SIO2object->_SIO2transform->loc->x;
	objdir.y = _vec->y - _SIO2object->_SIO2transform->loc->y;
	
	sio2Normalize( &dir, &dir );
	
	sio2Normalize( &objdir, &objdir );
	
	c_angle = sio2DotProductToDeg( &dir, &objdir );
	
	sio2CrossProduct( &dir,
					  &objdir,
					  &rot );

	glRotatef( c_angle, rot.x, rot.y, rot.z );
	
	if( sio2IsEnabled( _SIO2object->flags, SIO2_OBJECT_HALO ) )
	{
		vec3 objdir_proj;
		
		objdir_proj.x = objdir.x;
		objdir_proj.y = objdir.y;
		objdir_proj.z = _vec->z - _SIO2object->_SIO2transform->loc->z;
		
		sio2Normalize( &objdir_proj, &objdir_proj );
		
		s_angle = sio2DotProductToDeg( &objdir_proj,
									   &objdir );
		
		if( objdir.z < 0.0f )
		{ glRotatef( s_angle, -1.0f, 0.0f, 0.0f ); }
		else
		{ glRotatef( s_angle,  1.0f, 0.0f, 0.0f ); }
	}
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2ObjectReset( void )
{
	sio2->_SIO2object = NULL;
	
	sio2->_SIO2vertexgroup = NULL;

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	if( glIsEnabled( GL_COLOR_ARRAY ) )
	{ glDisableClientState( GL_COLOR_ARRAY ); }

	if( glIsEnabled( GL_NORMAL_ARRAY ) )
	{ glDisableClientState( GL_NORMAL_ARRAY ); }
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


unsigned int sio2ObjectGetNumVert( SIO2object *_SIO2object )
{
	SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object;

	if( tmp->vbo_offset[ SIO2_OBJECT_VCOLOR ] )
	{ return tmp->vbo_offset[ SIO2_OBJECT_VCOLOR ] / 12; } 

	else if( tmp->vbo_offset[ SIO2_OBJECT_NORMALS ] )
	{ return tmp->vbo_offset[ SIO2_OBJECT_NORMALS ] / 12; }
	
	else if( tmp->vbo_offset[ SIO2_OBJECT_TEXUV0 ] )
	{ return tmp->vbo_offset[ SIO2_OBJECT_TEXUV0 ] / 12; }

	else if( tmp->vbo_offset[ SIO2_OBJECT_TEXUV1 ] )
	{ return tmp->vbo_offset[ SIO2_OBJECT_TEXUV1 ] / 12; }

	return tmp->vbo_offset[ SIO2_OBJECT_SIZE ] / 12;
}


SIO2object *sio2ObjectDuplicate( SIO2object	   *_SIO2object,
								 SIO2transform *_SIO2transform,
								 char		   *_name,
								 unsigned char  _physic )
{
	unsigned int i = 0;
	
	SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object,
			   *dup = NULL;
			   
	if( _physic && sio2IsEnabled( tmp->flags, SIO2_OBJECT_SOFTBODY ) )
	{ return NULL; }
			   	   
	dup = sio2ObjectInit( _name );

	sio2StringCpy( dup->instname, tmp->name );
	
	dup->_SIO2instance = tmp;	

	dup->rad = _SIO2object->rad;
	dup->flags = _SIO2object->flags;
	
	memcpy( dup->dim, _SIO2object->dim, 12 );

	sio2ObjectUpdateType( dup );
	
	sio2TransformSetLoc( dup->_SIO2transform, _SIO2transform->loc );
	sio2TransformSetRot( dup->_SIO2transform, _SIO2transform->rot );
	sio2TransformSetScl( dup->_SIO2transform, _SIO2transform->scl );
	
	sio2TransformBindMatrix( dup->_SIO2transform );


	if( _physic )
	{
		tmp->buf = ( unsigned char * )sio2MapBuffer( tmp->vbo, GL_ARRAY_BUFFER );
		
		while( i != tmp->n_vgroup )
		{
			tmp->_SIO2vertexgroup[ i ]->ind = ( unsigned short * )sio2MapBuffer( tmp->_SIO2vertexgroup[ i ]->vbo,
																				 GL_ELEMENT_ARRAY_BUFFER );
			++i;
		}

		dup->bounds  = _SIO2object->bounds;
		dup->mass    = _SIO2object->mass;
		dup->damp    = _SIO2object->damp;
		dup->rotdamp = _SIO2object->rotdamp;

		sio2PhysicAddObject( sio2->_SIO2physic, dup );
		
		tmp->buf = ( unsigned char * )sio2UnmapBuffer( GL_ARRAY_BUFFER );
		
		i = 0;
		while( i != tmp->n_vgroup )
		{
			tmp->_SIO2vertexgroup[ i ]->ind = ( unsigned short * )sio2UnmapBuffer( GL_ELEMENT_ARRAY_BUFFER );
			++i;
		}
	}
	
	return dup;
}


void sio2ObjectEnableObjectCollisionCallback( SIO2object *_SIO2object )
{
	if( _SIO2object->_btRigidBody )
	{ _SIO2object->_btRigidBody->setCollisionFlags( btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK ); }
}


void sio2ObjectDisableObjectCollisionCallback( SIO2object *_SIO2object )
{
	if( _SIO2object->_btRigidBody )
	{ _SIO2object->_btRigidBody->setCollisionFlags( btCollisionObject::CF_NO_CONTACT_RESPONSE ); }
}


void sio2ObjectUpdateType( SIO2object *_SIO2object )
{
	unsigned int i = 0;
	
	SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object;
	
	_SIO2object->type = 0;
	
	while( i != tmp->n_vgroup )
	{
		if(  tmp->_SIO2vertexgroup[ i ]->_SIO2material &&
			 tmp->_SIO2vertexgroup[ i ]->_SIO2material->blend &&
			!tmp->_SIO2vertexgroup[ i ]->_SIO2material->alvl )
		{
			sio2EnableState( &_SIO2object->type, SIO2_OBJECT_ALPHA );
			return;
		}
		
		++i;
	}
	
	sio2EnableState( &_SIO2object->type, SIO2_OBJECT_SOLID );
}


unsigned char sio2ObjectSetAction( SIO2object   *_SIO2object,
								   char		    *_name,
								   float		 _inter,
								   float		 _fps )
{
	unsigned int i = 0;
	
	while( i != _SIO2object->n_frame )
	{
		if( sio2StringTok( _SIO2object->_SIO2frame[ i ]->name, _name ) )
		{
			_SIO2object->start_frame = i;
			break;
		}
	
		++i;
	}
	
	
	if( i == _SIO2object->n_frame )
	{ return 0; }
	

	while( i != _SIO2object->n_frame )
	{
		if( !sio2StringTok( _SIO2object->_SIO2frame[ i ]->name, _name ) )
		{ break; }

		++i;
	}


	if( _SIO2object->loop )
	{ _SIO2object->loop = 1; }

	_SIO2object->inter = _inter;
	_SIO2object->fps   = _fps;
	
	_SIO2object->end_frame  = ( i - 1 );
	_SIO2object->curr_frame = _SIO2object->start_frame;
	_SIO2object->next_frame = _SIO2object->start_frame + 1;

	_SIO2object->d_time = 0.0f;	
	sio2ObjectUpdateTimeRatio( _SIO2object );

	return 1;
}


unsigned char sio2ObjectSetNextAction( SIO2object *_SIO2object,
									   char		  *_name,
									   float	   _inter,
									   float	   _fps )
{
	unsigned int i = 0;
	
	while( i != _SIO2object->n_frame )
	{
		if( sio2StringTok( _SIO2object->_SIO2frame[ i ]->name, _name ) )
		{
			_SIO2object->start_frame = i;
			break;
		}
	
		++i;
	}
	
	
	if( i == _SIO2object->n_frame )
	{ return 0; }
	

	while( i != _SIO2object->n_frame )
	{
		if( !sio2StringTok( _SIO2object->_SIO2frame[ i ]->name, _name ) )
		{ break; }

		++i;
	}


	if( _SIO2object->loop )
	{ _SIO2object->loop = 1; }


	_SIO2object->end_frame  = ( i - 1 );
	_SIO2object->next_frame = _SIO2object->start_frame;

	_SIO2object->inter   = _inter;
	_SIO2object->t_ratio = _inter;
	_SIO2object->fps	 = _fps;
		
	_SIO2object->d_time = 0.0f;
	_SIO2object->next_action = 1;
		
	return 1; 
}


void sio2ObjectPlay( SIO2object		*_SIO2object,
					 unsigned char	 _loop )
{
	_SIO2object->state = SIO2_OBJECT_PLAY;
	_SIO2object->loop  = _loop;
}


void sio2ObjectPause( SIO2object *_SIO2object )
{ _SIO2object->state = SIO2_OBJECT_PAUSE; }


void sio2ObjectStop( SIO2object *_SIO2object )
{
	_SIO2object->state = SIO2_OBJECT_STOP;
	_SIO2object->d_time = 0.0f;
}


void sio2ObjectBuildAction( SIO2object	 *_SIO2object,
							unsigned int  _from,
							unsigned int  _to,
							char		 *_name )
{
	unsigned int i = 0;
	
	while( i != _SIO2object->n_frame )
	{
		if( _SIO2object->_SIO2frame[ i ]->frame >= _from &&
			_SIO2object->_SIO2frame[ i ]->frame <= _to )
		{ sio2StringCpy( _SIO2object->_SIO2frame[ i ]->name, _name ); }
		
		++i;
	}
}


void sio2ObjectClearAllAction( SIO2object *_SIO2object )
{
	unsigned int i = 0;
	
	while( i != _SIO2object->n_frame )
	{
		sio2StringCpy( _SIO2object->_SIO2frame[ i ]->name, "" );
		++i;
	}
}


void sio2ObjectUpdateTimeRatio( SIO2object *_SIO2object )
{
	_SIO2object->t_ratio = ( float )( ( _SIO2object->_SIO2frame[ _SIO2object->next_frame ]->frame * ( 1.0f / _SIO2object->fps ) ) - 
									  ( _SIO2object->_SIO2frame[ _SIO2object->curr_frame ]->frame * ( 1.0f / _SIO2object->fps ) ) );
}


void sio2ObjectSetVertexColorAlpha( SIO2object    *_SIO2object,
									unsigned char  _a )
{
	SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object;

	if( tmp->vbo_offset[ SIO2_OBJECT_VCOLOR ] )
	{
		unsigned int i = 0,
					 n_vert = sio2ObjectGetNumVert( tmp );
		
		tmp->buf = ( unsigned char * )sio2MapBuffer( tmp->vbo, GL_ARRAY_BUFFER );
		
		while( i != n_vert )
		{
			tmp->buf[ tmp->vbo_offset[ SIO2_OBJECT_VCOLOR ] + ( i * 4 ) + 3 ] = _a;
			++i;
		}		
		
		tmp->buf = ( unsigned char * )sio2UnmapBuffer( GL_ARRAY_BUFFER );
	}
}