
#line 1 "params.rl"
/*
 * Parse command line arguments.
 */

#include <stdio.h>
#include <string.h>

#define BUFLEN 1024

struct params
{
	char buffer[BUFLEN+1];
	int buflen;
	int cs;
};


#line 61 "params.rl"



#line 25 "params.c"
static const int params_start = 23;
static const int params_first_final = 23;
static const int params_error = 0;

static const int params_en_main = 23;


#line 64 "params.rl"

void params_init( struct params *fsm )
{
	fsm->buflen = 0;
	
#line 39 "params.c"
	{
	 fsm->cs = params_start;
	}

#line 69 "params.rl"
}

void params_execute( struct params *fsm, const char *data, int len )
{
	const char *p = data;
	const char *pe = data + len;

	
#line 53 "params.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  fsm->cs )
	{
tr11:
#line 38 "params.rl"
	{ printf("help\n"); }
	goto st23;
tr17:
#line 39 "params.rl"
	{ printf("version\n"); }
	goto st23;
tr21:
#line 30 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = 0;
	}
#line 42 "params.rl"
	{ printf("machine: \"%s\"\n", fsm->buffer); }
	goto st23;
tr25:
#line 30 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = 0;
	}
#line 41 "params.rl"
	{ printf("spec: \"%s\"\n", fsm->buffer); }
	goto st23;
tr29:
#line 30 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = 0;
	}
#line 40 "params.rl"
	{ printf("output: \"%s\"\n", fsm->buffer); }
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 98 "params.c"
	if ( (*p) == 45 )
		goto st1;
	goto st0;
st0:
 fsm->cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 45: goto st2;
		case 63: goto st6;
		case 72: goto st6;
		case 77: goto st14;
		case 83: goto st17;
		case 104: goto st6;
		case 111: goto st20;
		case 118: goto st13;
	}
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	switch( (*p) ) {
		case 104: goto st3;
		case 118: goto st7;
	}
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 101 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 108 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 112 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 0 )
		goto tr11;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 101 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 114 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 115 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 105 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 111 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 110 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 0 )
		goto tr17;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 0 )
		goto st16;
	goto tr18;
tr18:
#line 36 "params.rl"
	{ fsm->buflen = 0; }
#line 24 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = (*p);
	}
	goto st15;
tr20:
#line 24 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = (*p);
	}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 233 "params.c"
	if ( (*p) == 0 )
		goto tr21;
	goto tr20;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 0 )
		goto st0;
	goto tr18;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 0 )
		goto st19;
	goto tr22;
tr22:
#line 36 "params.rl"
	{ fsm->buflen = 0; }
#line 24 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = (*p);
	}
	goto st18;
tr24:
#line 24 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = (*p);
	}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 271 "params.c"
	if ( (*p) == 0 )
		goto tr25;
	goto tr24;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 0 )
		goto st0;
	goto tr22;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 0 )
		goto st22;
	goto tr26;
tr26:
#line 36 "params.rl"
	{ fsm->buflen = 0; }
#line 24 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = (*p);
	}
	goto st21;
tr28:
#line 24 "params.rl"
	{
		if ( fsm->buflen < BUFLEN )
			fsm->buffer[fsm->buflen++] = (*p);
	}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 309 "params.c"
	if ( (*p) == 0 )
		goto tr29;
	goto tr28;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 0 )
		goto st0;
	goto tr26;
	}
	_test_eof23:  fsm->cs = 23; goto _test_eof; 
	_test_eof1:  fsm->cs = 1; goto _test_eof; 
	_test_eof2:  fsm->cs = 2; goto _test_eof; 
	_test_eof3:  fsm->cs = 3; goto _test_eof; 
	_test_eof4:  fsm->cs = 4; goto _test_eof; 
	_test_eof5:  fsm->cs = 5; goto _test_eof; 
	_test_eof6:  fsm->cs = 6; goto _test_eof; 
	_test_eof7:  fsm->cs = 7; goto _test_eof; 
	_test_eof8:  fsm->cs = 8; goto _test_eof; 
	_test_eof9:  fsm->cs = 9; goto _test_eof; 
	_test_eof10:  fsm->cs = 10; goto _test_eof; 
	_test_eof11:  fsm->cs = 11; goto _test_eof; 
	_test_eof12:  fsm->cs = 12; goto _test_eof; 
	_test_eof13:  fsm->cs = 13; goto _test_eof; 
	_test_eof14:  fsm->cs = 14; goto _test_eof; 
	_test_eof15:  fsm->cs = 15; goto _test_eof; 
	_test_eof16:  fsm->cs = 16; goto _test_eof; 
	_test_eof17:  fsm->cs = 17; goto _test_eof; 
	_test_eof18:  fsm->cs = 18; goto _test_eof; 
	_test_eof19:  fsm->cs = 19; goto _test_eof; 
	_test_eof20:  fsm->cs = 20; goto _test_eof; 
	_test_eof21:  fsm->cs = 21; goto _test_eof; 
	_test_eof22:  fsm->cs = 22; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 77 "params.rl"
}

int params_finish( struct params *fsm )
{
	if ( fsm->cs == params_error )
		return -1;
	if ( fsm->cs >= params_first_final )
		return 1;
	return 0;
}

#define BUFSIZE 2048

int main( int argc, char **argv )
{
	int a;
	struct params params;

	params_init( &params );
	for ( a = 1; a < argc; a++ )
		params_execute( &params, argv[a], strlen(argv[a])+1 );
	if ( params_finish( &params ) != 1 )
		fprintf( stderr, "params: error processing arguments\n" );

	return 0;
}
