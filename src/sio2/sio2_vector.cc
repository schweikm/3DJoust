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


vec2 *sio2Vec2Init( void )
{ return ( vec2 * ) calloc( 1, sizeof( vec2 ) ); }


vec2 *sio2Vec2Free( vec2 *_v )
{
	free( _v );
	
	return NULL;
}


vec3 *sio2Vec3Init( void )
{ return ( vec3 * ) calloc( 1, sizeof( vec3 ) ); }


vec3 *sio2Vec3Free( vec3 *_v )
{
	free( _v );
	
	return NULL;
}


vec4 *sio2Vec4Init( void )
{ return ( vec4 * ) calloc( 1, sizeof( vec4 ) ); }


vec4 *sio2Vec4Free( vec4 *_v )
{
	free( _v );
	
	return NULL;
}


col4 *sio2Col4Init( void )
{ return ( col4 * ) calloc( 1, sizeof( col4 ) ); }


col4 *sio2Col4Free( col4 *_c )
{
	free( _c );

	return NULL;
}


// TODO: Move to SIO2transform and add quaternion
void sio2BuildMatrix( vec4  *_q,
					  vec3  *_p,
					  vec3  *_s,
					  float *_m )
{
	float xx = _q->x * _q->x;
	float xy = _q->x * _q->y;
	float xz = _q->x * _q->z;
	float xw = _q->x * _q->w;

	float yy = _q->y * _q->y;
	float yz = _q->y * _q->z;
	float yw = _q->y * _q->w;

	float zz = _q->z * _q->z;
	float zw = _q->z * _q->w;

	_m[  0 ] = 1.0f - 2.0f * ( yy + zz );
	_m[  1 ] =        2.0f * ( xy - zw );
	_m[  2 ] =        2.0f * ( xz + yw );

	_m[  4 ] =	      2.0f * ( xy + zw );
	_m[  5 ] = 1.0f - 2.0f * ( xx + zz );
	_m[  6 ] =        2.0f * ( yz - xw );

	_m[  8 ] =        2.0f * ( xz - yw );
	_m[  9 ] =        2.0f * ( yz + xw );
	_m[ 10 ] = 1.0f - 2.0f * ( xx + yy );	

	_m[  0 ] *= _s->x;
	_m[  1 ] *= _s->x;
	_m[  2 ] *= _s->x;

	_m[  4 ] *= _s->y;
	_m[  5 ] *= _s->y;
	_m[  6 ] *= _s->y;
	
	_m[  8 ] *= _s->z;
	_m[  9 ] *= _s->z;
	_m[ 10 ] *= _s->z;

	_m[ 12 ] = _p->x; 
	_m[ 13 ] = _p->y; 
	_m[ 14 ] = _p->z;
	
	_m[ 3 ]  =
	_m[ 7 ]  = 
	_m[ 11 ] = 
	_m[ 15 ] = 1.0f;
}


void sio2Rotate2D( vec2 *_v1,
				   float _az,
				   float _d,
				   vec2 *_v2 )
{
	_v2->x = _v1->x + _d * sinf( _az * SIO2_DEG_TO_RAD );
	_v2->y = _v1->y - _d * cosf( _az * SIO2_DEG_TO_RAD );
}


void sio2Rotate3D( vec3  *_v1,
				   float  _ax,
				   float  _az,
				   float  _d,
				   vec3  *_v2 )
{ 
	float cos_a_x = cosf( _ax * SIO2_DEG_TO_RAD );
	
	_v2->x = _v1->x + _d * cos_a_x * sinf( _az * SIO2_DEG_TO_RAD );
	_v2->y = _v1->y - _d * cos_a_x * cosf( _az * SIO2_DEG_TO_RAD );
	_v2->z = _v1->z + _d * sinf( _ax * SIO2_DEG_TO_RAD );
}