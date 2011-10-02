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


SIO2video *sio2VideoInit( char *_name )
{
	int i = 0;
	
	SIO2video *_SIO2video = ( SIO2video * ) calloc( 1, sizeof( SIO2video ) );

	sio2StringCpy( _SIO2video->name, _name );


	while( i != 256 )
	{
		_SIO2video->b0[ i ] = ( 113443 * ( i - 128 ) + 32768 ) >> 16;
		++i;
	}


	i = 0;
	while( i != 256 )
	{
		_SIO2video->b1[ i ] = ( 45744 * ( i - 128 ) + 32768 ) >> 16;
		++i;
	}


	i = 0;
	while( i != 256 )
	{
		_SIO2video->b2[ i ] = ( 22020 * ( i - 128 ) + 32768 ) >> 16;
		++i;
	}


	i = 0;
	while( i != 256 )
	{
		_SIO2video->b3[ i ] = ( 113508 * ( i - 128 ) + 32768 ) >> 16;
		++i;
	}

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_VIDEO,
					 ( void * )_SIO2video );

	return _SIO2video;
}


SIO2video *sio2VideoFree( SIO2video *_SIO2video )
{
	sio2VideoStop( _SIO2video );

	ogg_stream_clear( &_SIO2video->to );
	ogg_sync_clear  ( &_SIO2video->oy );

	theora_clear		( &_SIO2video->td );
	theora_comment_clear( &_SIO2video->tc );
	theora_info_clear	( &_SIO2video->ti );

	if( _SIO2video->_SIO2thread )
	{ _SIO2video->_SIO2thread = sio2ThreadFree( _SIO2video->_SIO2thread ); }

	_SIO2video->_SIO2stream = sio2StreamClose( _SIO2video->_SIO2stream );

	sio2ResourceDel( sio2->_SIO2resource,
					  SIO2_VIDEO,
					  (void *)_SIO2video );	

	free( _SIO2video );
	
	return NULL;
}


void sio2VideoLoad( SIO2video  *_SIO2video,
					SIO2stream *_SIO2stream )
{
	ogg_sync_init( &_SIO2video->oy );

	theora_comment_init( &_SIO2video->tc );

	theora_info_init( &_SIO2video->ti );

	_SIO2video->_SIO2stream = _SIO2stream;

	while( !_SIO2video->flags )
	{
		char *buffer = ogg_sync_buffer( &_SIO2video->oy, SIO2_VIDEO_BUFFER_SIZE );
		
		int	bytes = sio2StreamRead( _SIO2video->_SIO2stream,
									buffer, SIO2_VIDEO_BUFFER_SIZE );

		ogg_sync_wrote( &_SIO2video->oy, bytes );


		while( ogg_sync_pageout( &_SIO2video->oy, &_SIO2video->og ) > 0 )
		{
			if( !ogg_page_bos( &_SIO2video->og ) )
			{ 
				ogg_stream_pagein( &_SIO2video->to, &_SIO2video->og );
				
				_SIO2video->flags = 1;

				break;
			}

			ogg_stream_init( &_SIO2video->os, ogg_page_serialno( &_SIO2video->og ) );
			ogg_stream_pagein( &_SIO2video->os, &_SIO2video->og );
			ogg_stream_packetout( &_SIO2video->os, &_SIO2video->op );

			
			if( !_SIO2video->theora_p && theora_decode_header( &_SIO2video->ti,
															   &_SIO2video->tc,
															   &_SIO2video->op ) >= 0 )
			{
				memcpy( &_SIO2video->to, &_SIO2video->os, sizeof( _SIO2video->os ) );
				
				_SIO2video->theora_p = 1;
			}
			
		}
	}


	while( ( _SIO2video->theora_p && _SIO2video->theora_p < 3 ) )
	{
		int ret;

		while( _SIO2video->theora_p &&
			  ( _SIO2video->theora_p < 3 ) &&
			  ( ret = ogg_stream_packetout( &_SIO2video->to,&_SIO2video->op ) ) )
		{
			theora_decode_header( &_SIO2video->ti,
								  &_SIO2video->tc,
								  &_SIO2video->op );
								  
			++_SIO2video->theora_p;
		}

		ogg_sync_pageout( &_SIO2video->oy,
						  &_SIO2video->og );
		
		ogg_stream_pagein( &_SIO2video->to,
						   &_SIO2video->og );
	}


	if( _SIO2video->theora_p )
	{
		theora_decode_init( &_SIO2video->td, &_SIO2video->ti );

		theora_control( &_SIO2video->td,
						TH_DECCTL_GET_PPLEVEL_MAX,
						&_SIO2video->lvl_max,
						sizeof( _SIO2video->lvl_max ) );

		_SIO2video->lvl = _SIO2video->lvl_max;

		theora_control( &_SIO2video->td,
						TH_DECCTL_SET_PPLEVEL,
						&_SIO2video->lvl,
						sizeof( _SIO2video->lvl ) );
	}
	

	_SIO2video->fps_time =  1.0f / ( _SIO2video->ti.fps_numerator /
									 _SIO2video->ti.fps_denominator ); 
	

	_SIO2video->_SIO2image = sio2ImageInit( _SIO2video->name );
	
	_SIO2video->_SIO2image->width  = ( unsigned int )_SIO2video->ti.width;
	_SIO2video->_SIO2image->height = ( unsigned int )_SIO2video->ti.height;
	_SIO2video->_SIO2image->bits   = 3;
}


unsigned char sio2VideoGetFrame( SIO2video *_SIO2video,
								 int	    _flags,
								 float		_filter )
{
	unsigned char status = 0;
	
	if( _SIO2video->frame )
	{ 
		sio2ImageGenId( _SIO2video->_SIO2image, _flags, _filter );
		_SIO2video->frame = 0;
		
		status = 1;
	}

	if( _SIO2video->ready )
	{ _SIO2video->ready = 0; }
	
	return status;
}


void sio2VideoPlay( SIO2video	  *_SIO2video,
					unsigned char  _loop )
{
	_SIO2video->loop = _loop;

	if( !_SIO2video->_SIO2thread )
	{
		_SIO2video->_SIO2thread = sio2ThreadInit();
		
		sio2ThreadCreate( _SIO2video->_SIO2thread,
						  sio2VideoDecompress,
						  ( void * )_SIO2video,
						  SIO2_THREAD_PRIORITY_VERY_HIGH );	
	}

	sio2ThreadPlay( _SIO2video->_SIO2thread );
	
	_SIO2video->state = SIO2_VIDEO_PLAY;
}


void sio2VideoPause( SIO2video *_SIO2video )
{
	if( _SIO2video->_SIO2thread )
	{ sio2ThreadPause( _SIO2video->_SIO2thread ); }
	
	_SIO2video->state = SIO2_VIDEO_PAUSE;
}


void sio2VideoStop( SIO2video *_SIO2video )
{
	if( _SIO2video->_SIO2thread )
	{ sio2ThreadStop( _SIO2video->_SIO2thread ); }
	
	_SIO2video->_SIO2stream->pos = 0;
	_SIO2video->v_frame = 0;
	
	_SIO2video->state = SIO2_VIDEO_STOP;
}


void sio2VideoDecompress( void *_ptr )
{
	SIO2video *_SIO2video = ( SIO2video * )_ptr;

	if( !_SIO2video->frame && ( _SIO2video->sync_time >= _SIO2video->fps_time ) )
	{
		while( _SIO2video->theora_p && !_SIO2video->ready )
		{
			if( ogg_stream_packetout( &_SIO2video->to, &_SIO2video->op ) > 0 )
			{
				if( _SIO2video->inc )
				{
					_SIO2video->lvl += _SIO2video->inc;
					
					theora_control( &_SIO2video->td,
									TH_DECCTL_SET_PPLEVEL,
									&_SIO2video->lvl,
									sizeof( _SIO2video->lvl) );
					
					_SIO2video->inc = 0;
				}


				if( _SIO2video->op.granulepos >= 0 )
				{
					theora_control( &_SIO2video->td,
									TH_DECCTL_SET_GRANPOS,
									&_SIO2video->op.granulepos,
									sizeof( _SIO2video->op.granulepos ) );
				}

				
				if( !theora_decode_packetin( &_SIO2video->td, &_SIO2video->op ) ) 
				{
					_SIO2video->v_time = theora_granule_time( &_SIO2video->td, _SIO2video->td.granulepos );
					
					++_SIO2video->v_frame;
					
					_SIO2video->ready = 1;
				}
				else
				{ _SIO2video->ready = 0; }
			}
			else
			{ break; }
		}


		if( !_SIO2video->ready && sio2StreamEOF( _SIO2video->_SIO2stream ) )
		{
			if( !_SIO2video->loop )
			{ sio2VideoStop( _SIO2video ); }
			else
			{
				_SIO2video->_SIO2stream->pos = 0;
				_SIO2video->v_frame = 0;
			}
		}
		
		else if( !_SIO2video->ready )
		{
			char *buffer = ogg_sync_buffer( &_SIO2video->oy, SIO2_VIDEO_BUFFER_SIZE );
			
			int	bytes = sio2StreamRead( _SIO2video->_SIO2stream,
										buffer, SIO2_VIDEO_BUFFER_SIZE );

			ogg_sync_wrote( &_SIO2video->oy, bytes );

			while( ogg_sync_pageout( &_SIO2video->oy, &_SIO2video->og ) > 0 )
			{ ogg_stream_pagein( &_SIO2video->to, &_SIO2video->og ); }
		}
		
		else if( _SIO2video->flags  && _SIO2video->ready )
		{
			int y_shift,
				uv_shift,
				w2,
				ny,
				nu,
				nv,
				r,
				g,
				b;
		
			int w,
			    h = 0;
		
			unsigned char *buf;
			
			_SIO2video->sync_time = 0.0f;

			yuv_buffer yuv;
			theora_decode_YUVout( &_SIO2video->td, &yuv );
			
			_SIO2video->_SIO2image->tex = ( unsigned char * ) malloc( _SIO2video->_SIO2image->width  *
																	  _SIO2video->_SIO2image->height *
																	  _SIO2video->_SIO2image->bits	 );

			buf = _SIO2video->_SIO2image->tex;

			while( h != yuv.y_height )
			{
				y_shift = yuv.y_stride * h;
				uv_shift = yuv.uv_stride * ( h >> 1 );
			
				w = 0;
				while( w != yuv.y_width )
				{
					w2 = w >> 1;
					
					ny = *( yuv.y + y_shift  + w  );
					nu = *( yuv.u + uv_shift + w2 );
					nv = *( yuv.v + uv_shift + w2 );

					r = ny + _SIO2video->b0[ nv ];
					g = ny - _SIO2video->b1[ nv ] - _SIO2video->b2[ nu ];
					b = ny + _SIO2video->b3[ nu ];

					buf[ 0 ] = OC_CLAMP255( r - 16 );
					buf[ 1 ] = OC_CLAMP255( g - 16 );
					buf[ 2 ] = OC_CLAMP255( b - 16 );
					
					buf += _SIO2video->_SIO2image->bits;
				
					++w;
				}
			
				++h;
			}
			
			_SIO2video->frame = 1;		
		}
	}
	
	_SIO2video->curr_time = sio2GetElapsedTime();	
	
	if( _SIO2video->last_sync )
	{ _SIO2video->sync_time += ( _SIO2video->curr_time - _SIO2video->last_sync ) * 0.001f; }
	
	_SIO2video->last_sync = _SIO2video->curr_time;			
}
