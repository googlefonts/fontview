
#line 1 "gotocallret.rl"
/*
 * Demonstrate the use of goto, call and return. This machine expects either a
 * lower case char or a digit as a command then a space followed by the command
 * arg. If the command is a char, then the arg must be an a string of chars.
 * If the command is a digit, then the arg must be a string of digits. This
 * choice is determined by action code, rather than though transition
 * desitinations.
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

struct GotoCallRet 
{
	char comm;
	int cs, top, stack[32];

	int init( );
	int execute( const char *data, int len, bool isEof );
	int finish( );
};


#line 57 "gotocallret.rl"



#line 35 "gotocallret.cpp"
static const int GotoCallRet_start = 7;
static const int GotoCallRet_first_final = 7;
static const int GotoCallRet_error = 0;

static const int GotoCallRet_en_garble_line = 3;
static const int GotoCallRet_en_alp_comm = 5;
static const int GotoCallRet_en_dig_comm = 6;
static const int GotoCallRet_en_main = 7;


#line 60 "gotocallret.rl"

int GotoCallRet::init( )
{
	
#line 51 "gotocallret.cpp"
	{
	cs = GotoCallRet_start;
	top = 0;
	}

#line 64 "gotocallret.rl"
	return 1;
}

int GotoCallRet::execute( const char *data, int len, bool isEof )
{
	const char *p = data;
	const char *pe = data + len;
	const char *eof = isEof ? pe : 0;

	
#line 68 "gotocallret.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	goto _resume;

_again:
	switch ( cs ) {
		case 7: goto st7;
		case 0: goto st0;
		case 1: goto st1;
		case 2: goto st2;
		case 3: goto st3;
		case 4: goto st4;
		case 8: goto st8;
		case 5: goto st5;
		case 9: goto st9;
		case 6: goto st6;
		case 10: goto st10;
	default: break;
	}

	if ( ++p == pe )
		goto _test_eof;
_resume:
	switch ( cs )
	{
tr2:
#line 52 "gotocallret.rl"
	{cout << "correct command" << endl;}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 103 "gotocallret.cpp"
	if ( (*p) > 57 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr11;
	} else if ( (*p) >= 48 )
		goto tr11;
	goto tr0;
tr0:
#line 56 "gotocallret.rl"
	{p--;{goto st3;}}
	goto st0;
tr7:
#line 38 "gotocallret.rl"
	{p--;{cs = stack[--top];goto _again;}}
	goto st0;
tr9:
#line 39 "gotocallret.rl"
	{p--;{cs = stack[--top];goto _again;}}
	goto st0;
#line 122 "gotocallret.cpp"
st0:
cs = 0;
	goto _out;
tr11:
#line 51 "gotocallret.rl"
	{comm = (*p);}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 134 "gotocallret.cpp"
	if ( (*p) == 32 )
		goto tr1;
	goto tr0;
tr1:
#line 42 "gotocallret.rl"
	{
		if ( comm >= 'a' )
			{stack[top++] = 2; goto st5;}
		else 
			{stack[top++] = 2; goto st6;}
	}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 151 "gotocallret.cpp"
	if ( (*p) == 10 )
		goto tr2;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 10 )
		goto tr4;
	goto tr3;
tr3:
#line 34 "gotocallret.rl"
	{cout << "error: garbling line" << endl;}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 170 "gotocallret.cpp"
	if ( (*p) == 10 )
		goto tr6;
	goto st4;
tr4:
#line 34 "gotocallret.rl"
	{cout << "error: garbling line" << endl;}
#line 34 "gotocallret.rl"
	{{goto st7;}}
	goto st8;
tr6:
#line 34 "gotocallret.rl"
	{{goto st7;}}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 188 "gotocallret.cpp"
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st9;
	} else if ( (*p) >= 65 )
		goto st9;
	goto tr7;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st9;
	} else if ( (*p) >= 65 )
		goto st9;
	goto tr7;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st10;
	goto tr9;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st10;
	goto tr9;
	}
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 5: 
#line 38 "gotocallret.rl"
	{p--;{cs = stack[--top];goto _again;}}
	break;
	case 6: 
#line 39 "gotocallret.rl"
	{p--;{cs = stack[--top];goto _again;}}
	break;
	case 1: 
	case 2: 
#line 56 "gotocallret.rl"
	{p--;{goto st3;}}
	break;
#line 253 "gotocallret.cpp"
	}
	}

	_out: {}
	}

#line 74 "gotocallret.rl"
	if ( cs == GotoCallRet_error )
		return -1;
	if ( cs >= GotoCallRet_first_final )
		return 1;
	return 0;
}

#define BUFSIZE 1024

int main()
{
	char buf[BUFSIZE];

	GotoCallRet gcr;
	gcr.init();
	while ( fgets( buf, sizeof(buf), stdin ) != 0 )
		gcr.execute( buf, strlen(buf), false );

	gcr.execute( 0, 0, true );
	if ( gcr.cs < GotoCallRet_first_final )
		cerr << "gotocallret: error: parsing input" << endl;
	return 0;
}
