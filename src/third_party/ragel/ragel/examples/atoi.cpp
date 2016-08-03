
#line 1 "atoi.rl"
/*
 * Convert a string to an integer.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#line 13 "atoi.cpp"
static const int atoi_start = 1;
static const int atoi_first_final = 4;
static const int atoi_error = 0;

static const int atoi_en_main = 1;


#line 12 "atoi.rl"


long long atoi( char *str )
{
	char *p = str, *pe = str + strlen( str );
	int cs;
	long long val = 0;
	bool neg = false;

	
#line 32 "atoi.cpp"
	{
	cs = atoi_start;
	}

#line 37 "atoi.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 43: goto st2;
		case 45: goto tr2;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr3;
	goto st0;
st0:
cs = 0;
	goto _out;
tr2:
#line 22 "atoi.rl"
	{
			neg = true;
		}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 64 "atoi.cpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr3;
	goto st0;
tr3:
#line 26 "atoi.rl"
	{ 
			val = val * 10 + ((*p) - '0');
		}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 78 "atoi.cpp"
	if ( (*p) == 10 )
		goto st4;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr3;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 37 "atoi.rl"


	if ( neg )
		val = -1 * val;

	if ( cs < atoi_first_final )
		fprintf( stderr, "atoi: there was an error\n" );

	return val;
};


#define BUFSIZE 1024

int main()
{
	char buf[BUFSIZE];
	while ( fgets( buf, sizeof(buf), stdin ) != 0 ) {
		long long value = atoi( buf );
		printf( "%lld\n", value );
	}
	return 0;
}
