
#line 1 "cppscan.rl"
/*
 * A C++ scanner. Uses the longest match construction.
 * << <= <<= >> >= >>= are left out since angle brackets are used in templates.
 */

#include <string.h>
#include <stdlib.h>
#include <iostream>

#define TK_Dlit 256
#define TK_Slit 257
#define TK_Float 258
#define TK_Id 259
#define TK_NameSep 260
#define TK_Arrow 261
#define TK_PlusPlus 262
#define TK_MinusMinus 263
#define TK_ArrowStar 264
#define TK_DotStar 265
#define TK_ShiftLeft 266
#define TK_ShiftRight 267
#define TK_IntegerDecimal 268
#define TK_IntegerOctal 269
#define TK_IntegerHex 270
#define TK_EqualsEquals 271
#define TK_NotEquals 272
#define TK_AndAnd 273
#define TK_OrOr 274
#define TK_MultAssign 275
#define TK_DivAssign 276
#define TK_PercentAssign 277
#define TK_PlusAssign 278
#define TK_MinusAssign 279
#define TK_AmpAssign 280
#define TK_CaretAssign 281
#define TK_BarAssign 282
#define TK_DotDotDot 283
#define TK_Whitespace 284
#define TK_Comment 285

#define BUFSIZE 16384

/* EOF char used to flush out that last token. This should be a whitespace
 * token. */

#define LAST_CHAR 0

using std::cerr;
using std::cout;
using std::cin;
using std::endl;

static char buf[BUFSIZE];
static int line = 1, col = 1;
static char *ts, *te;
static int act, have = 0;
static int cs;


#line 63 "cppscan.cpp"
static const int Scanner_start = 12;
static const int Scanner_error = 0;

static const int Scanner_en_c_comment = 10;
static const int Scanner_en_main = 12;


#line 132 "cppscan.rl"


void token( int tok )
{
	char *data = ts;
	int len = te - ts;

	cout << '<' << tok << "> ";
	cout.write( data, len );
	cout << '\n';
	
	/* Count newlines and columns. This code is here mainly for having some
	 * code in the token routine when commenting out the above output during
	 * performance testing. */
	for ( int i = 0; i < len; i ++ ) {
		if ( data[i] == '\n' ) {
			line += 1;
			col = 1;
		}
		else {
			col += 1;
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);

	
#line 102 "cppscan.cpp"
	{
	cs = Scanner_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 162 "cppscan.rl"

	/* Do the first read. */
	bool done = false;
	while ( !done ) {
		char *p = buf + have;
		int space = BUFSIZE - have;

		if ( space == 0 ) {
			/* We filled up the buffer trying to scan a token. */
			cerr << "OUT OF BUFFER SPACE" << endl;
			exit(1);
		}

		cin.read( p, space );
		int len = cin.gcount();
		char *pe = p + len;
		char *eof = 0;

		/* If we see eof then append the EOF char. */
	 	if ( cin.eof() ) {
			eof = pe;
			done = true;
		}

		
#line 136 "cppscan.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 1 "NONE"
	{	switch( act ) {
	case 0:
	{{goto st0;}}
	break;
	case 3:
	{{p = ((te))-1;}token( TK_Id );}
	break;
	case 4:
	{{p = ((te))-1;}token( TK_Float );}
	break;
	case 5:
	{{p = ((te))-1;}token( TK_IntegerDecimal );}
	break;
	case 6:
	{{p = ((te))-1;}token( TK_IntegerOctal );}
	break;
	}
	}
	goto st12;
tr2:
#line 78 "cppscan.rl"
	{te = p+1;{token( TK_Dlit );}}
	goto st12;
tr5:
#line 76 "cppscan.rl"
	{te = p+1;{token( TK_Slit );}}
	goto st12;
tr7:
#line 124 "cppscan.rl"
	{{p = ((te))-1;}{token( ts[0] );}}
	goto st12;
tr8:
#line 121 "cppscan.rl"
	{te = p+1;{token( TK_DotDotDot );}}
	goto st12;
tr12:
#line 128 "cppscan.rl"
	{te = p+1;}
	goto st12;
tr13:
#line 90 "cppscan.rl"
	{{p = ((te))-1;}{token( TK_IntegerDecimal );}}
	goto st12;
tr20:
#line 124 "cppscan.rl"
	{te = p+1;{token( ts[0] );}}
	goto st12;
tr36:
#line 129 "cppscan.rl"
	{te = p;p--;}
	goto st12;
tr37:
#line 124 "cppscan.rl"
	{te = p;p--;{token( ts[0] );}}
	goto st12;
tr38:
#line 103 "cppscan.rl"
	{te = p+1;{token( TK_NotEquals );}}
	goto st12;
tr39:
#line 108 "cppscan.rl"
	{te = p+1;{token( TK_PercentAssign );}}
	goto st12;
tr40:
#line 104 "cppscan.rl"
	{te = p+1;{token( TK_AndAnd );}}
	goto st12;
tr41:
#line 111 "cppscan.rl"
	{te = p+1;{token( TK_AmpAssign );}}
	goto st12;
tr42:
#line 106 "cppscan.rl"
	{te = p+1;{token( TK_MultAssign );}}
	goto st12;
tr43:
#line 114 "cppscan.rl"
	{te = p+1;{token( TK_PlusPlus );}}
	goto st12;
tr44:
#line 109 "cppscan.rl"
	{te = p+1;{token( TK_PlusAssign );}}
	goto st12;
tr45:
#line 115 "cppscan.rl"
	{te = p+1;{token( TK_MinusMinus );}}
	goto st12;
tr46:
#line 110 "cppscan.rl"
	{te = p+1;{token( TK_MinusAssign );}}
	goto st12;
tr48:
#line 116 "cppscan.rl"
	{te = p;p--;{token( TK_Arrow );}}
	goto st12;
tr49:
#line 117 "cppscan.rl"
	{te = p+1;{token( TK_ArrowStar );}}
	goto st12;
tr50:
#line 118 "cppscan.rl"
	{te = p+1;{token( TK_DotStar );}}
	goto st12;
tr53:
#line 86 "cppscan.rl"
	{te = p;p--;{token( TK_Float );}}
	goto st12;
tr55:
#line 86 "cppscan.rl"
	{te = p+1;{token( TK_Float );}}
	goto st12;
tr56:
#line 127 "cppscan.rl"
	{te = p+1;{ {goto st10;} }}
	goto st12;
tr57:
#line 107 "cppscan.rl"
	{te = p+1;{token( TK_DivAssign );}}
	goto st12;
tr58:
#line 90 "cppscan.rl"
	{te = p;p--;{token( TK_IntegerDecimal );}}
	goto st12;
tr62:
#line 94 "cppscan.rl"
	{te = p;p--;{token( TK_IntegerOctal );}}
	goto st12;
tr64:
#line 94 "cppscan.rl"
	{te = p+1;{token( TK_IntegerOctal );}}
	goto st12;
tr66:
#line 90 "cppscan.rl"
	{te = p+1;{token( TK_IntegerDecimal );}}
	goto st12;
tr67:
#line 98 "cppscan.rl"
	{te = p;p--;{token( TK_IntegerHex );}}
	goto st12;
tr69:
#line 98 "cppscan.rl"
	{te = p+1;{token( TK_IntegerHex );}}
	goto st12;
tr70:
#line 101 "cppscan.rl"
	{te = p+1;{token( TK_NameSep );}}
	goto st12;
tr71:
#line 102 "cppscan.rl"
	{te = p+1;{token( TK_EqualsEquals );}}
	goto st12;
tr72:
#line 82 "cppscan.rl"
	{te = p;p--;{token( TK_Id );}}
	goto st12;
tr73:
#line 112 "cppscan.rl"
	{te = p+1;{token( TK_CaretAssign );}}
	goto st12;
tr74:
#line 113 "cppscan.rl"
	{te = p+1;{token( TK_BarAssign );}}
	goto st12;
tr75:
#line 105 "cppscan.rl"
	{te = p+1;{token( TK_OrOr );}}
	goto st12;
st12:
#line 1 "NONE"
	{ts = 0;}
#line 1 "NONE"
	{act = 0;}
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 1 "NONE"
	{ts = p;}
#line 321 "cppscan.cpp"
	switch( (*p) ) {
		case 33: goto st14;
		case 34: goto st1;
		case 37: goto st15;
		case 38: goto st16;
		case 39: goto st3;
		case 42: goto st17;
		case 43: goto st18;
		case 45: goto st19;
		case 46: goto tr26;
		case 47: goto tr27;
		case 48: goto tr28;
		case 58: goto st33;
		case 61: goto st34;
		case 76: goto tr33;
		case 94: goto st37;
		case 95: goto st35;
		case 124: goto st38;
	}
	if ( (*p) < 65 ) {
		if ( (*p) < 49 ) {
			if ( 35 <= (*p) && (*p) <= 44 )
				goto tr20;
		} else if ( (*p) > 57 ) {
			if ( 59 <= (*p) && (*p) <= 64 )
				goto tr20;
		} else
			goto tr29;
	} else if ( (*p) > 90 ) {
		if ( (*p) < 97 ) {
			if ( 91 <= (*p) && (*p) <= 96 )
				goto tr20;
		} else if ( (*p) > 122 ) {
			if ( 123 <= (*p) && (*p) <= 126 )
				goto tr20;
		} else
			goto st35;
	} else
		goto st35;
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr36;
	goto st13;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 61 )
		goto tr38;
	goto tr37;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 10: goto tr0;
		case 34: goto tr2;
		case 92: goto st2;
	}
	goto st1;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	goto st1;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 61 )
		goto tr39;
	goto tr37;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 38: goto tr40;
		case 61: goto tr41;
	}
	goto tr37;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 10: goto tr0;
		case 39: goto tr5;
		case 92: goto st4;
	}
	goto st3;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	goto st3;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 61 )
		goto tr42;
	goto tr37;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 43: goto tr43;
		case 61: goto tr44;
	}
	goto tr37;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 45: goto tr45;
		case 61: goto tr46;
		case 62: goto st20;
	}
	goto tr37;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 42 )
		goto tr49;
	goto tr48;
tr26:
#line 1 "NONE"
	{te = p+1;}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 463 "cppscan.cpp"
	switch( (*p) ) {
		case 42: goto tr50;
		case 46: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr52;
	goto tr37;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 46 )
		goto tr8;
	goto tr7;
tr52:
#line 1 "NONE"
	{te = p+1;}
#line 86 "cppscan.rl"
	{act = 4;}
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 488 "cppscan.cpp"
	switch( (*p) ) {
		case 69: goto st6;
		case 70: goto tr55;
		case 76: goto tr55;
		case 101: goto st6;
		case 102: goto tr55;
		case 108: goto tr55;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr52;
	goto tr53;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 43: goto st7;
		case 45: goto st7;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st23;
	goto tr0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st23;
	goto tr0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 70: goto tr55;
		case 76: goto tr55;
		case 102: goto tr55;
		case 108: goto tr55;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st23;
	goto tr53;
tr27:
#line 1 "NONE"
	{te = p+1;}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 539 "cppscan.cpp"
	switch( (*p) ) {
		case 42: goto tr56;
		case 47: goto st8;
		case 61: goto tr57;
	}
	goto tr37;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 10 )
		goto tr12;
	goto st8;
tr28:
#line 1 "NONE"
	{te = p+1;}
#line 90 "cppscan.rl"
	{act = 5;}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 563 "cppscan.cpp"
	switch( (*p) ) {
		case 46: goto tr52;
		case 69: goto st6;
		case 76: goto st28;
		case 85: goto st28;
		case 101: goto st6;
		case 108: goto st28;
		case 117: goto st28;
		case 120: goto st9;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr59;
	goto tr58;
tr59:
#line 1 "NONE"
	{te = p+1;}
#line 94 "cppscan.rl"
	{act = 6;}
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 587 "cppscan.cpp"
	switch( (*p) ) {
		case 46: goto tr52;
		case 69: goto st6;
		case 76: goto st27;
		case 85: goto st27;
		case 101: goto st6;
		case 108: goto st27;
		case 117: goto st27;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr59;
	goto tr62;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 76: goto tr64;
		case 85: goto tr64;
		case 108: goto tr64;
		case 117: goto tr64;
	}
	goto tr62;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 76: goto st29;
		case 85: goto st29;
		case 108: goto st29;
		case 117: goto st29;
	}
	goto tr58;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 76: goto tr66;
		case 85: goto tr66;
		case 108: goto tr66;
		case 117: goto tr66;
	}
	goto tr58;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st30;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st30;
	} else
		goto st30;
	goto tr13;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 76: goto st31;
		case 85: goto st31;
		case 108: goto st31;
		case 117: goto st31;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st30;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st30;
	} else
		goto st30;
	goto tr67;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 76: goto tr69;
		case 85: goto tr69;
		case 108: goto tr69;
		case 117: goto tr69;
	}
	goto tr67;
tr29:
#line 1 "NONE"
	{te = p+1;}
#line 90 "cppscan.rl"
	{act = 5;}
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
#line 686 "cppscan.cpp"
	switch( (*p) ) {
		case 46: goto tr52;
		case 69: goto st6;
		case 76: goto st28;
		case 85: goto st28;
		case 101: goto st6;
		case 108: goto st28;
		case 117: goto st28;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr29;
	goto tr58;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	if ( (*p) == 58 )
		goto tr70;
	goto tr37;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) == 61 )
		goto tr71;
	goto tr37;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	if ( (*p) == 95 )
		goto st35;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st35;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st35;
	} else
		goto st35;
	goto tr72;
tr33:
#line 1 "NONE"
	{te = p+1;}
#line 82 "cppscan.rl"
	{act = 3;}
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 738 "cppscan.cpp"
	switch( (*p) ) {
		case 34: goto st1;
		case 39: goto st3;
		case 95: goto st35;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st35;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st35;
	} else
		goto st35;
	goto tr72;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	if ( (*p) == 61 )
		goto tr73;
	goto tr37;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 61: goto tr74;
		case 124: goto tr75;
	}
	goto tr37;
st10:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 775 "cppscan.cpp"
	if ( (*p) == 42 )
		goto st11;
	goto st10;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 42: goto st11;
		case 47: goto tr17;
	}
	goto st10;
tr17:
#line 70 "cppscan.rl"
	{ {goto st12;} }
	goto st39;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
#line 796 "cppscan.cpp"
	goto st0;
st0:
cs = 0;
	goto _out;
	}
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 13: goto tr36;
	case 14: goto tr37;
	case 1: goto tr0;
	case 2: goto tr0;
	case 15: goto tr37;
	case 16: goto tr37;
	case 3: goto tr0;
	case 4: goto tr0;
	case 17: goto tr37;
	case 18: goto tr37;
	case 19: goto tr37;
	case 20: goto tr48;
	case 21: goto tr37;
	case 5: goto tr7;
	case 22: goto tr53;
	case 6: goto tr0;
	case 7: goto tr0;
	case 23: goto tr53;
	case 24: goto tr37;
	case 8: goto tr7;
	case 25: goto tr58;
	case 26: goto tr62;
	case 27: goto tr62;
	case 28: goto tr58;
	case 29: goto tr58;
	case 9: goto tr13;
	case 30: goto tr67;
	case 31: goto tr67;
	case 32: goto tr58;
	case 33: goto tr37;
	case 34: goto tr37;
	case 35: goto tr72;
	case 36: goto tr72;
	case 37: goto tr37;
	case 38: goto tr37;
	}
	}

	_out: {}
	}

#line 187 "cppscan.rl"

		/* Check if we failed. */
		if ( cs == Scanner_error ) {
			/* Machine failed before finding a token. */
			cerr << "PARSE ERROR" << endl;
			exit(1);
		}

		/* Now set up the prefix. */
		if ( ts == 0 )
			have = 0;
		else {
			/* There is data that needs to be shifted over. */
			have = pe - ts;
			memmove( buf, ts, have );
			te -= (ts-buf);
			ts = buf;
		}
	}

	return 0;
}
