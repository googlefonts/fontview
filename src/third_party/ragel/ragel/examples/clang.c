
#line 1 "clang.rl"
/*
 * A mini C-like language scanner.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#line 91 "clang.rl"



#line 17 "clang.c"
static const int clang_start = 10;
static const int clang_error = 0;

static const int clang_en_c_comment = 8;
static const int clang_en_main = 10;


#line 94 "clang.rl"

#define BUFSIZE 128

void scanner()
{
	static char buf[BUFSIZE];
	int cs, act, have = 0, curline = 1;
	char *ts, *te = 0;
	int done = 0;

	
#line 37 "clang.c"
	{
	cs = clang_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 105 "clang.rl"

	while ( !done ) {
		char *p = buf + have, *pe, *eof = 0;
		int len, space = BUFSIZE - have;
		
		if ( space == 0 ) {
			/* We've used up the entire buffer storing an already-parsed token
			 * prefix that must be preserved. */
			fprintf(stderr, "OUT OF BUFFER SPACE\n" );
			exit(1);
		}

		len = fread( p, 1, space, stdin );
		pe = p + len;

		/* Check if this is the end of file. */
		if ( len < space ) {
			eof = pe;
			done = 1;
		}
			
		
#line 68 "clang.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr2:
#line 50 "clang.rl"
	{te = p+1;{
		printf( "double_lit(%i): ", curline );
		fwrite( ts, 1, te-ts, stdout );
		printf("\n");
	}}
	goto st10;
tr6:
#line 42 "clang.rl"
	{te = p+1;{
		printf( "single_lit(%i): ", curline );
		fwrite( ts, 1, te-ts, stdout );
		printf("\n");
	}}
	goto st10;
tr8:
#line 28 "clang.rl"
	{{p = ((te))-1;}{
		printf( "symbol(%i): %c\n", curline, ts[0] );
	}}
	goto st10;
tr10:
#line 12 "clang.rl"
	{curline += 1;}
#line 62 "clang.rl"
	{te = p+1;}
	goto st10;
tr11:
#line 68 "clang.rl"
	{{p = ((te))-1;}{
		printf( "int(%i): ", curline );
		fwrite( ts, 1, te-ts, stdout );
		printf("\n");
	}}
	goto st10;
tr18:
#line 57 "clang.rl"
	{te = p+1;}
	goto st10;
tr19:
#line 12 "clang.rl"
	{curline += 1;}
#line 57 "clang.rl"
	{te = p+1;}
	goto st10;
tr20:
#line 28 "clang.rl"
	{te = p+1;{
		printf( "symbol(%i): %c\n", curline, ts[0] );
	}}
	goto st10;
tr25:
#line 28 "clang.rl"
	{te = p;p--;{
		printf( "symbol(%i): %c\n", curline, ts[0] );
	}}
	goto st10;
tr26:
#line 64 "clang.rl"
	{te = p+1;{ {goto st8;} }}
	goto st10;
tr27:
#line 68 "clang.rl"
	{te = p;p--;{
		printf( "int(%i): ", curline );
		fwrite( ts, 1, te-ts, stdout );
		printf("\n");
	}}
	goto st10;
tr30:
#line 76 "clang.rl"
	{te = p;p--;{
		printf( "float(%i): ", curline );
		fwrite( ts, 1, te-ts, stdout );
		printf("\n");
	}}
	goto st10;
tr31:
#line 84 "clang.rl"
	{te = p;p--;{
		printf( "hex(%i): ", curline );
		fwrite( ts, 1, te-ts, stdout );
		printf("\n");
	}}
	goto st10;
tr32:
#line 34 "clang.rl"
	{te = p;p--;{
		printf( "ident(%i): ", curline );
		fwrite( ts, 1, te-ts, stdout );
		printf("\n");
	}}
	goto st10;
st10:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 1 "NONE"
	{ts = p;}
#line 176 "clang.c"
	switch( (*p) ) {
		case 10: goto tr19;
		case 34: goto st1;
		case 39: goto st3;
		case 47: goto tr21;
		case 48: goto tr22;
		case 95: goto st16;
	}
	if ( (*p) < 65 ) {
		if ( (*p) < 49 ) {
			if ( 33 <= (*p) && (*p) <= 46 )
				goto tr20;
		} else if ( (*p) > 57 ) {
			if ( 58 <= (*p) && (*p) <= 64 )
				goto tr20;
		} else
			goto tr23;
	} else if ( (*p) > 90 ) {
		if ( (*p) < 97 ) {
			if ( 91 <= (*p) && (*p) <= 96 )
				goto tr20;
		} else if ( (*p) > 122 ) {
			if ( 123 <= (*p) && (*p) <= 126 )
				goto tr20;
		} else
			goto st16;
	} else
		goto st16;
	goto tr18;
tr1:
#line 12 "clang.rl"
	{curline += 1;}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 214 "clang.c"
	switch( (*p) ) {
		case 10: goto tr1;
		case 34: goto tr2;
		case 92: goto st2;
	}
	goto st1;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 10 )
		goto tr1;
	goto st1;
tr5:
#line 12 "clang.rl"
	{curline += 1;}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 236 "clang.c"
	switch( (*p) ) {
		case 10: goto tr5;
		case 39: goto tr6;
		case 92: goto st4;
	}
	goto st3;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 10 )
		goto tr5;
	goto st3;
tr21:
#line 1 "NONE"
	{te = p+1;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 258 "clang.c"
	switch( (*p) ) {
		case 42: goto tr26;
		case 47: goto st5;
	}
	goto tr25;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 10 )
		goto tr10;
	goto st5;
tr22:
#line 1 "NONE"
	{te = p+1;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 279 "clang.c"
	switch( (*p) ) {
		case 46: goto st6;
		case 120: goto st7;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr23;
	goto tr27;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st13;
	goto tr11;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st13;
	goto tr30;
tr23:
#line 1 "NONE"
	{te = p+1;}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 309 "clang.c"
	if ( (*p) == 46 )
		goto st6;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr23;
	goto tr27;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st15;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st15;
	} else
		goto st15;
	goto tr11;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st15;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st15;
	} else
		goto st15;
	goto tr31;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 95 )
		goto st16;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st16;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st16;
	} else
		goto st16;
	goto tr32;
tr15:
#line 12 "clang.rl"
	{curline += 1;}
	goto st8;
st8:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 366 "clang.c"
	switch( (*p) ) {
		case 10: goto tr15;
		case 42: goto st9;
	}
	goto st8;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 10: goto tr15;
		case 42: goto st9;
		case 47: goto tr17;
	}
	goto st8;
tr17:
#line 16 "clang.rl"
	{{goto st10;}}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 390 "clang.c"
	goto st0;
st0:
cs = 0;
	goto _out;
	}
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 11: goto tr25;
	case 5: goto tr8;
	case 12: goto tr27;
	case 6: goto tr11;
	case 13: goto tr30;
	case 14: goto tr27;
	case 7: goto tr11;
	case 15: goto tr31;
	case 16: goto tr32;
	}
	}

	_out: {}
	}

#line 127 "clang.rl"

		if ( cs == clang_error ) {
			fprintf(stderr, "PARSE ERROR\n" );
			break;
		}

		if ( ts == 0 )
			have = 0;
		else {
			/* There is a prefix to preserve, shift it over. */
			have = pe - ts;
			memmove( buf, ts, have );
			te = buf + (te-ts);
			ts = buf;
		}
	}
}

int main()
{
	scanner();
	return 0;
}

