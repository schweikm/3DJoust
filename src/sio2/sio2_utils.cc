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


unsigned int sio2GetElapsedTime( void )
{
	int time_base = 0;
	struct timeval t;

	gettimeofday( &t, NULL );

	time_base =  ( unsigned int )( ( ( ( t.tv_sec * 1000000 ) +
									     t.tv_usec ) - sio2->i_time ) * 0.001 ); 

	return time_base;
}


void sio2ExtractPath( char *_fname,
					  char *_ppath,
					  char *_aname )
{
	unsigned int i = 0,
				 s = sio2StringLen( _fname );
				 
	char *curr_pos;

	while( i != s )
	{
		if( _fname[ i ] == '\\' )
		{ _fname[ i ] = '/'; }
		
		++i;
	}
	
	curr_pos = strrchr( _fname, '/' );
	
	if( curr_pos )
	{
		memcpy( _ppath, _fname, s - sio2StringLen( curr_pos ) + 1 );
		
		if( _aname )
		{ memcpy( _aname, ( curr_pos + 1 ), s - sio2StringLen( curr_pos ) ); }
	}
}


float sio2RoundAngle( float _a )
{ return ( unsigned int )( 360.0f * floorf( abs( _a ) / 360.0f ) + _a ) % 360; }

 
void sio2Perspective( float fov,
					  float rat, 
					  float n,
					  float f )
{
	float m[ 16 ],
		  s,
		  c,
		  d = f - n,
		  r = fov * 0.5f * SIO2_DEG_TO_RAD;

	s = sinf( r );

	c = cosf( r ) / s;

	memset( &m[ 0 ], 0, 64 );
	
	m[ 10 ] = 
	m[ 15 ] = 1.0f;

	m[ 0  ] = c / rat;
	m[ 5  ] = c;
	m[ 10 ] = -( f + n ) / d;
	m[ 11 ] = -1.0f;
	m[ 14 ] = -2.0f * f * n / d;

	glMultMatrixf( &m[ 0 ] );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}

						 
unsigned char sio2Project( float objx, float objy, float objz,
						   float model[16], float proj[16], int viewport[4],
						   float *winx, float *winy, float *winz )
{
	float in [ 4 ],
		  out[ 4 ];

	in[ 0 ] = objx;
	in[ 1 ] = objy;
	in[ 2 ] = objz;
	in[ 3 ] = 1.0f;
	
	#define M( row, col ) model[ col * 4 + row ]
	
		out[ 0 ] = M( 0, 0 ) * in[ 0 ] + M( 0, 1 ) * in[ 1 ] + M( 0, 2 ) * in[ 2 ] + M( 0, 3 ) * in[ 3 ];
		out[ 1 ] = M( 1, 0 ) * in[ 0 ] + M( 1, 1 ) * in[ 1 ] + M( 1, 2 ) * in[ 2 ] + M( 1, 3 ) * in[ 3 ];
		out[ 2 ] = M( 2, 0 ) * in[ 0 ] + M( 2, 1 ) * in[ 1 ] + M( 2, 2 ) * in[ 2 ] + M( 2, 3 ) * in[ 3 ];
		out[ 3 ] = M( 3, 0 ) * in[ 0 ] + M( 3, 1 ) * in[ 1 ] + M( 3, 2 ) * in[ 2 ] + M( 3, 3 ) * in[ 3 ];
	#undef M


	#define M( row, col ) proj[ col * 4 + row ]
	
		in[ 0 ] = M( 0, 0 ) * out[ 0 ] + M( 0, 1 ) * out[ 1 ] + M( 0, 2 ) * out[ 2 ] + M( 0, 3 ) * out[ 3 ];
		in[ 1 ] = M( 1, 0 ) * out[ 0 ] + M( 1, 1 ) * out[ 1 ] + M( 1, 2 ) * out[ 2 ] + M( 1, 3 ) * out[ 3 ];
		in[ 2 ] = M( 2, 0 ) * out[ 0 ] + M( 2, 1 ) * out[ 1 ] + M( 2, 2 ) * out[ 2 ] + M( 2, 3 ) * out[ 3 ];
		in[ 3 ] = M( 3, 0 ) * out[ 0 ] + M( 3, 1 ) * out[ 1 ] + M( 3, 2 ) * out[ 2 ] + M( 3, 3 ) * out[ 3 ];
	#undef M

	if( !in[ 3 ] )
	{ return 0; }

	in[ 0 ] /= in[ 3 ];
	in[ 1 ] /= in[ 3 ];
	in[ 2 ] /= in[ 3 ];

	*winx = viewport[ 0 ] + ( 1.0f + in[ 0 ] ) * viewport[ 2 ] * 0.5f;
	*winy = viewport[ 1 ] + ( 1.0f + in[ 1 ] ) * viewport[ 3 ] * 0.5f;
	*winz = ( 1.0f + in[ 2 ] ) * 0.5f;
	
	return 1;
}

					   
unsigned char sio2UnProject( float winx,
							 float winy,
							 float winz,
							 float model [ 16 ],
							 float proj  [ 16 ],
							 int viewport[ 4  ],
							 float *objx,
							 float *objy,
							 float *objz )
{
	int i = 0;
	
	float m   [ 16 ],
		  a   [ 16 ],
		  in  [ 4  ],
		  out [ 4  ],
		  temp[ 16 ],
		  wtmp[ 4  ][ 8 ],
		  m0,
		  m1,
		  m2,
		  m3,
		  s,
		  *r0,
		  *r1,
		  *r2,
		  *r3;

	in[ 0 ] = ( winx - viewport[ 0 ] ) * 2.0f / viewport[ 2 ] - 1.0f;
	in[ 1 ] = ( winy - viewport[ 1 ] ) * 2.0f / viewport[ 3 ] - 1.0f;
	in[ 2 ] = 2.0f * winz - 1.0f;
	in[ 3 ] = 1.0f;
	
	
 	#define A(row,col) proj[ ( col << 2 ) + row ]
	
	#define B(row,col) model[ ( col << 2 ) + row ]
	
	#define T(row,col) temp[ ( col << 2 ) + row ]

		while( i != 4 )
		{
			T( i, 0 ) = A( i , 0 ) *B( 0, 0 ) + A( i, 1 ) * B( 1,0 ) + A( i, 2 ) *B( 2, 0 ) + A( i, 3) *B( 3, 0 );
			T( i, 1 ) = A( i , 0 ) *B( 0, 1 ) + A( i, 1 ) * B( 1,1 ) + A( i, 2 ) *B( 2, 1 ) + A( i, 3) *B( 3, 1 );
			T( i, 2 ) = A( i , 0 ) *B( 0, 2 ) + A( i, 1 ) * B( 1,2 ) + A( i, 2 ) *B( 2, 2 ) + A( i, 3) *B( 3, 2 );
			T( i, 3 ) = A( i , 0 ) *B( 0, 3 ) + A( i, 1 ) * B( 1,3 ) + A( i, 2 ) *B( 2, 3 ) + A( i, 3) *B( 3, 3 );
			
			++i;
		}
	
	#undef A
	#undef B
	#undef T
	
	
	memcpy( ( void * )a, ( void * )temp, sizeof( float ) << 4 );


	#define SWAP_ROWS( a, b ) { float *_tmp = a; ( a ) = ( b ); ( b ) = _tmp; }
	
	#define MAT( a, r, c ) ( a )[ ( c << 2 ) + ( r ) ]
	 
		r0 = wtmp[ 0 ], r1 = wtmp[ 1 ], r2 = wtmp[ 2 ], r3 = wtmp[ 3 ];

		r0[ 0 ] = MAT( a, 0, 0 ), r0[ 1 ] = MAT( a, 0, 1 ),
		r0[ 2 ] = MAT( a, 0, 2 ), r0[ 3 ] = MAT( a, 0, 3 ),
		r0[ 4 ] = 1.0f          , r0[ 5 ] = r0[ 6 ] = r0[ 7 ] = 0.0f,
		r1[ 0 ] = MAT( a, 1, 0 ), r1[ 1 ] = MAT( a, 1, 1 ),
		r1[ 2 ] = MAT( a, 1, 2 ), r1[ 3 ] = MAT( a, 1, 3 ),
		r1[ 5 ] = 1.0f, r1[ 4 ] = r1[ 6 ] = r1[ 7 ] = 0.0f,
		r2[ 0 ] = MAT( a, 2, 0 ), r2[ 1 ] = MAT( a, 2, 1 ),
		r2[ 2 ] = MAT( a, 2, 2 ), r2[ 3 ] = MAT( a, 2, 3 ),
		r2[ 6 ] = 1.0f          , r2[ 4 ] = r2[ 5 ] = r2[ 7 ] = 0.0f,
		r3[ 0 ] = MAT( a, 3, 0 ), r3[ 1 ] = MAT( a, 3, 1 ),
		r3[ 2 ] = MAT( a, 3, 2 ), r3[ 3 ] = MAT( a, 3, 3 ),
		r3[ 7 ] = 1.0f          , r3[ 4 ] = r3[ 5 ] = r3[ 6 ] = 0.0f;

		if( fabs( r3[ 0 ] ) > fabs( r2[ 0 ] ) )
		{ SWAP_ROWS( r3, r2 ); }
		
		if( fabs( r2[ 0 ] ) > fabs( r1[ 0 ] ) )
		{ SWAP_ROWS( r2, r1 ); }
		
		if( fabs( r1[ 0 ] ) > fabs( r0[ 0 ] ) )
		{ SWAP_ROWS( r1, r0 ); }
		
		if( !r0[0] )
		{ return 0; }


		m1 = r1[ 0 ] / r0[ 0 ];
		m2 = r2[ 0 ] / r0[ 0 ];
		m3 = r3[ 0 ] / r0[ 0 ];
		s  = r0[ 1 ];
		
		r1[ 1 ] -= m1 * s;
		r2[ 1 ] -= m2 * s;
		r3[ 1 ] -= m3 * s;
		s = r0[ 2 ];
		
		r1[ 2 ] -= m1 * s;
		r2[ 2 ] -= m2 * s;
		r3[ 2 ] -= m3 * s;
		s = r0[ 3 ];
		
		r1[ 3 ] -= m1 * s;
		r2[ 3 ] -= m2 * s;
		r3[ 3 ] -= m3 * s;
		s = r0[ 4 ];
		
		if( s )
		{
			r1[ 4 ] -= m1 * s;
			r2[ 4 ] -= m2 * s;
			r3[ 4 ] -= m3 * s;
		}
		s = r0[ 5 ];
		
		if( s )
		{
			r1[ 5 ] -= m1 * s;
			r2[ 5 ] -= m2 * s;
			r3[ 5 ] -= m3 * s;
		}
		s = r0[ 6 ];

		if( s )
		{
			r1[ 6 ] -= m1 * s;
			r2[ 6 ] -= m2 * s;
			r3[ 6 ] -= m3 * s;
		}
		s = r0[ 7 ];

		if (s != 0.0)
		{
			r1[ 7 ] -= m1 * s;
			r2[ 7 ] -= m2 * s;
			r3[ 7 ] -= m3 * s;
		}

		if( fabs( r3[ 1 ] ) > fabs( r2[ 1 ] ) )
		{ SWAP_ROWS( r3, r2 ); }
		
		if( fabs( r2[ 1 ] ) > fabs( r1[ 1 ] ) )
		{ SWAP_ROWS( r2, r1 ); }
		
		if( !r1[ 1 ] )
		{ return 0; }
		 
		m2 = r2[ 1 ] / r1[ 1 ];
		m3 = r3[ 1 ] / r1[ 1 ];
		
		r2[ 2 ] -= m2 * r1[ 2 ];
		r3[ 2 ] -= m3 * r1[ 2 ];
		r2[ 3 ] -= m2 * r1[ 3 ];
		r3[ 3 ] -= m3 * r1[ 3 ];
		s = r1[ 4 ];
		
		if( s )
		{
			r2[ 4 ] -= m2 * s;
			r3[ 4 ] -= m3 * s;
		}
		s = r1[ 5 ];
		
		if( s )
		{
			r2[ 5 ] -= m2 * s;
			r3[ 5 ] -= m3 * s;
		}
		s = r1[ 6 ];

		if( s )
		{
			r2[ 6 ] -= m2 * s;
			r3[ 6 ] -= m3 * s;
		}
		s = r1[ 7 ];

		if( s )
		{
			r2[ 7 ] -= m2 * s;
			r3[ 7 ] -= m3 * s;
		}

		if( fabs( r3[ 2 ] ) > fabs( r2[ 2 ] ) )
		{ SWAP_ROWS( r3, r2 ); }
		
		if( !r2[ 2 ] )
		{ return 0; }

		m3 = r3[ 2 ] / r2[ 2 ];
		r3[ 3 ] -= m3 * r2[ 3 ], r3[ 4 ] -= m3 * r2[ 4 ],
		r3[ 5 ] -= m3 * r2[ 5 ], r3[ 6 ] -= m3 * r2[ 6 ], r3[ 7 ] -= m3 * r2[ 7 ];


		if( !r3[ 3 ] )
		{ return 0; }
		 
		s = 1.0f / r3[ 3 ];
		r3[ 4 ] *= s;
		r3[ 5 ] *= s;
		r3[ 6 ] *= s;
		r3[ 7 ] *= s;

		m2 = r2[ 3 ];
		s = 1.0f / r2[ 2 ];
		r2[ 4 ] = s * ( r2[ 4 ] - r3[ 4 ] * m2 ), r2[ 5 ] = s * ( r2[ 5 ] - r3[ 5 ] * m2 ),
		r2[ 6 ] = s * ( r2[ 6 ] - r3[ 6 ] * m2 ), r2[ 7 ] = s * ( r2[ 7 ] - r3[ 7 ] * m2 );
		
		m1 = r1[ 3 ];
		r1[ 4 ] -= r3[ 4 ] * m1, r1[ 5 ] -= r3[ 5 ] * m1,
		r1[ 6 ] -= r3[ 6 ] * m1, r1[ 7 ] -= r3[ 7 ] * m1;
		
		m0 = r0[3];
		r0[ 4 ] -= r3[ 4 ] * m0, r0[ 5 ] -= r3[ 5 ] * m0,
		r0[ 6 ] -= r3[ 6 ] * m0, r0[ 7 ] -= r3[ 7 ] * m0;

		m1 = r1[ 2 ];
		s = 1.0f / r1[ 1 ];
		r1[ 4 ] = s * ( r1[ 4 ] - r2[ 4 ] * m1 ), r1[ 5 ] = s * ( r1[ 5 ] - r2[ 5 ] * m1 ),
		r1[ 6 ] = s * ( r1[ 6 ] - r2[ 6 ] * m1 ), r1[ 7 ] = s * ( r1[ 7 ] - r2[ 7 ] * m1 );
		
		m0 = r0[ 2 ];
		r0[ 4 ] -= r2[ 4 ] * m0, r0[ 5 ] -= r2[ 5 ] * m0,
		r0[ 6 ] -= r2[ 6 ] * m0, r0[ 7 ] -= r2[ 7 ] * m0;
		 
		m0 = r0[ 1 ];
		s = 1.0f / r0[ 0 ];
		r0[ 4 ] = s * ( r0[ 4 ] - r1[ 4 ] * m0 ), r0[ 5 ] = s * ( r0[ 5 ] - r1[ 5 ] * m0 ),
		r0[ 6 ] = s * ( r0[ 6 ] - r1[ 6 ] * m0 ), r0[ 7 ] = s * ( r0[ 7 ] - r1[ 7 ] * m0 );

		MAT( m, 0, 0 ) = r0[ 4 ];
		MAT( m, 0, 1 ) = r0[ 5 ], MAT( m, 0, 2 ) = r0[ 6 ];
		MAT( m, 0, 3 ) = r0[ 7 ], MAT( m, 1, 0 ) = r1[ 4 ];
		MAT( m, 1, 1 ) = r1[ 5 ], MAT( m, 1, 2 ) = r1[ 6 ];
		MAT( m, 1, 3 ) = r1[ 7 ], MAT( m, 2, 0 ) = r2[ 4 ];
		MAT( m, 2, 1 ) = r2[ 5 ], MAT( m, 2, 2 ) = r2[ 6 ];
		MAT( m, 2, 3 ) = r2[ 7 ], MAT( m, 3, 0 ) = r3[ 4 ];
		MAT( m, 3, 1 ) = r3[ 5 ], MAT( m, 3, 2 ) = r3[ 6 ];
		MAT( m, 3, 3 ) = r3[ 7 ];

	#undef MAT
	#undef SWAP_ROWS


	#define M(row,col) m[ col * 4 + row ]
	
		out[ 0 ] = M( 0, 0 ) * in[ 0 ] + M( 0, 1 ) * in[ 1 ] + M( 0, 2 ) * in[ 2 ] + M( 0, 3 ) * in[ 3 ];
		out[ 1 ] = M( 1, 0 ) * in[ 0 ] + M( 1, 1 ) * in[ 1 ] + M( 1, 2 ) * in[ 2 ] + M( 1, 3 ) * in[ 3 ];
		out[ 2 ] = M( 2, 0 ) * in[ 0 ] + M( 2, 1 ) * in[ 1 ] + M( 2, 2 ) * in[ 2 ] + M( 2, 3 ) * in[ 3 ];
		out[ 3 ] = M( 3, 0 ) * in[ 0 ] + M( 3, 1 ) * in[ 1 ] + M( 3, 2 ) * in[ 2 ] + M( 3, 3 ) * in[ 3 ];
	#undef M


	if( !out[ 3 ] )
	{ return 0; }

	*objx = out[ 0 ] / out[ 3 ];
	*objy = out[ 1 ] / out[ 3 ];
	*objz = out[ 2 ] / out[ 3 ];

	return 1;
}


unsigned char sio2IsPow2( int _size )
{
	switch( _size )
	{
		case 2	 : return 1;
		case 4	 : return 1;		
		case 8	 : return 1;
		case 16	 : return 1;
		case 32	 : return 1;
		case 64  : return 1;
		case 128 : return 1;
		case 256 : return 1;
		case 512 : return 1;
		case 1024: return 1;
	}
	
	return 0;	
}


void sio2Sleep( unsigned int _ms )
{
	int microsecs;
		
	struct timeval tv;

	microsecs = _ms * 1000;

	tv.tv_sec  = microsecs / 1000000;
	tv.tv_usec = microsecs % 1000000;

	select( 0, NULL, NULL, NULL, &tv );	
}


unsigned int sio2Randomui( unsigned int _max )
{ return ( random() % _max ) + 1; }


float sio2Randomf( void )
{ return rand() / (float)0x7FFFFFFF; }


void sio2SetColorIndex( unsigned int  _index,
						col4		 *_col )
{
	unsigned int i = _index >> 16;
	
	_col->r =
	_col->g =
	_col->b = 0;
	_col->a = 255;
	
	memcpy( &_col->r, &i, 1 );

	i = _index >> 8;
	memcpy( &_col->g, &i, 1 );

	memcpy( &_col->b, &_index, 1 );	

	glColor4ub( _col->r,
				_col->g,
				_col->b,
				_col->a );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif				
}


unsigned int sio2GetNextPow2( unsigned int _s )
{ return ( unsigned int )( powf( 2, ceilf( logf( _s ) / logf( 2 ) ) ) ); }


float sio2CubicBezier( float t, float a, float b, float c, float d )
{
	float i  = 1.0f - t,
		  t2 = t * t,
		  i2 = i * i;
	
	return i2 * i * a +  3.0f * t * i2 * b  +  3.0f * t2  * i * c + t2 * t * d;
}


void *sio2MapBuffer( unsigned int _id, int _type )
{
	void *ptr;
	
	glBindBuffer( _type, _id );

	glMapBufferOES( _type, GL_WRITE_ONLY_OES );

	glGetBufferPointervOES( _type, GL_BUFFER_MAP_POINTER_OES, &ptr );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
	
	return ptr;
}


void *sio2UnmapBuffer( int _type )
{
	glUnmapBufferOES( _type );

	glBindBuffer( _type, 0 );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
	
	return NULL;
}


void sio2LookAt( vec3 *_e,
				 vec3 *_c,
				 vec3 *_u )
{
	vec3 f,
		 s,
		 u;
	
    float m[ 4 ][ 4 ];
	
	sio2Vec3Diff( _c, _e, &f );
	
	sio2Normalize( &f, &f );

	sio2CrossProduct( &f, _u, &s );

	sio2Normalize( &s, &s );

	sio2CrossProduct( &s, &f, &u );

	memset( &m[ 0 ][ 0 ], 0, 64 );
	
    m[ 0 ][ 0 ] = s.x;
    m[ 1 ][ 0 ] = s.y;
    m[ 2 ][ 0 ] = s.z;
	
    m[ 0 ][ 1 ] = u.x;
    m[ 1 ][ 1 ] = u.y;
    m[ 2 ][ 1 ] = u.z;
	
    m[ 0 ][ 2 ] = -f.x;
    m[ 1 ][ 2 ] = -f.y;
    m[ 2 ][ 2 ] = -f.z;

	m[ 0 ][ 3 ] =
	m[ 1 ][ 3 ] =
	m[ 2 ][ 3 ] =
	m[ 3 ][ 0 ] =
	m[ 3 ][ 1 ] = 
	m[ 3 ][ 2 ] = 0.0f;  	
	
	m[ 3 ][ 3 ] = 1.0f;

    glMultMatrixf( &m[ 0 ][ 0 ] );
	
	glTranslatef( -_e->x, -_e->y, -_e->z );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


float sio2RGBtoFloat( unsigned char _c )
{ return (float)_c / 255.0f; }
