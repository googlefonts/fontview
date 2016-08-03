
#line 1 "rlscan.rl"
/*
 * Lexes Ragel input files.
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void escapeXML( char *data )
{
	while ( *data != 0 ) {
		switch ( *data ) {
			case '<': cout << "&lt;"; break;
			case '>': cout << "&gt;"; break;
			case '&': cout << "&amp;"; break;
			default: cout << *data; break;
		}
		data += 1;
	}
}

void escapeXML( char c )
{
	switch ( c ) {
		case '<': cout << "&lt;"; break;
		case '>': cout << "&gt;"; break;
		case '&': cout << "&amp;"; break;
		default: cout << c; break;
	}
}

void escapeXML( char *data, int len )
{
	for ( char *end = data + len; data != end; data++  ) {
		switch ( *data ) {
			case '<': cout << "&lt;"; break;
			case '>': cout << "&gt;"; break;
			case '&': cout << "&amp;"; break;
			default: cout << *data; break;
		}
	}
}

inline void write( const char *data )
{
	cout << data;
}

inline void write( char c )
{
	cout << c;
}

inline void write( char *data, int len )
{
	cout.write( data, len );
}



#line 237 "rlscan.rl"



#line 71 "rlscan.cpp"
static const int RagelScan_start = 24;
static const int RagelScan_error = 0;

static const int RagelScan_en_c_comment = 6;
static const int RagelScan_en_ilscan = 31;
static const int RagelScan_en_rlscan = 35;
static const int RagelScan_en_main = 24;


#line 240 "rlscan.rl"

#define BUFSIZE 2048

int main()
{
	std::ios::sync_with_stdio(false);

	int cs, act;
	char *ts, *te;
	int stack[1], top;

	static char inbuf[BUFSIZE];
	bool single_line = false;
	int inline_depth = 0;

	
#line 98 "rlscan.cpp"
	{
	cs = RagelScan_start;
	top = 0;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 256 "rlscan.rl"

	bool done = false;
	int have = 0;
	while ( !done ) {
		/* How much space is in the buffer? */
		int space = BUFSIZE - have;
		if ( space == 0 ) {
			/* Buffer is full. */
			cerr << "TOKEN TOO BIG" << endl;
			exit(1);
		}

		/* Read in a block. */
		char *p = inbuf + have;
		cin.read( p, space );
		int len = cin.gcount();
		char *pe = p + len;
		char *eof = 0;

		/* Check for EOF. */
		if ( len == 0 ) {
			eof = pe;
			done = true;
		}

		
#line 134 "rlscan.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	goto _resume;

_again:
	switch ( cs ) {
		case 24: goto st24;
		case 25: goto st25;
		case 1: goto st1;
		case 2: goto st2;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 3: goto st3;
		case 4: goto st4;
		case 29: goto st29;
		case 5: goto st5;
		case 6: goto st6;
		case 0: goto st0;
		case 7: goto st7;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 8: goto st8;
		case 9: goto st9;
		case 33: goto st33;
		case 10: goto st10;
		case 11: goto st11;
		case 34: goto st34;
		case 12: goto st12;
		case 35: goto st35;
		case 36: goto st36;
		case 13: goto st13;
		case 14: goto st14;
		case 37: goto st37;
		case 15: goto st15;
		case 38: goto st38;
		case 16: goto st16;
		case 17: goto st17;
		case 39: goto st39;
		case 18: goto st18;
		case 19: goto st19;
		case 40: goto st40;
		case 41: goto st41;
		case 20: goto st20;
		case 42: goto st42;
		case 43: goto st43;
		case 44: goto st44;
		case 21: goto st21;
		case 22: goto st22;
		case 45: goto st45;
		case 23: goto st23;
	default: break;
	}

	if ( ++p == pe )
		goto _test_eof;
_resume:
	switch ( cs )
	{
tr0:
#line 230 "rlscan.rl"
	{{p = ((te))-1;}{ 
			escapeXML( *ts );
		}}
	goto st24;
tr2:
#line 79 "rlscan.rl"
	{te = p+1;{
		escapeXML( ts, te-ts );
	}}
	goto st24;
tr5:
#line 79 "rlscan.rl"
	{te = p+1;{
		escapeXML( ts, te-ts );
	}}
	goto st24;
tr8:
#line 79 "rlscan.rl"
	{te = p+1;{
		escapeXML( ts, te-ts );
	}}
	goto st24;
tr40:
#line 230 "rlscan.rl"
	{te = p+1;{ 
			escapeXML( *ts );
		}}
	goto st24;
tr41:
#line 235 "rlscan.rl"
	{te = p+1;}
	goto st24;
tr46:
#line 230 "rlscan.rl"
	{te = p;p--;{ 
			escapeXML( *ts );
		}}
	goto st24;
tr48:
#line 224 "rlscan.rl"
	{te = p;p--;{
			write( "<section>\n" ); 
			single_line = true; 
			{goto st35;}
		}}
	goto st24;
tr49:
#line 218 "rlscan.rl"
	{te = p+1;{ 
			write( "<section>\n" );
			single_line = false;
			{goto st35;}
		}}
	goto st24;
tr50:
#line 211 "rlscan.rl"
	{te = p+1;{
			escapeXML( ts, te-ts );
			{stack[top++] = 24; goto st6;}
		}}
	goto st24;
st24:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 1 "NONE"
	{ts = p;}
#line 267 "rlscan.cpp"
	switch( (*p) ) {
		case 0: goto tr41;
		case 34: goto tr42;
		case 37: goto st26;
		case 39: goto tr44;
		case 47: goto tr45;
	}
	goto tr40;
tr42:
#line 1 "NONE"
	{te = p+1;}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 284 "rlscan.cpp"
	switch( (*p) ) {
		case 34: goto tr2;
		case 92: goto st2;
	}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 34: goto tr2;
		case 92: goto st2;
	}
	goto st1;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	goto st1;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	if ( (*p) == 37 )
		goto st27;
	goto tr46;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	if ( (*p) == 123 )
		goto tr49;
	goto tr48;
tr44:
#line 1 "NONE"
	{te = p+1;}
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 326 "rlscan.cpp"
	switch( (*p) ) {
		case 39: goto tr5;
		case 92: goto st4;
	}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 39: goto tr5;
		case 92: goto st4;
	}
	goto st3;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	goto st3;
tr45:
#line 1 "NONE"
	{te = p+1;}
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 354 "rlscan.cpp"
	switch( (*p) ) {
		case 42: goto tr50;
		case 47: goto st5;
	}
	goto tr46;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 10 )
		goto tr8;
	goto st5;
tr9:
#line 76 "rlscan.rl"
	{ escapeXML( (*p) ); }
	goto st6;
st6:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 377 "rlscan.cpp"
	switch( (*p) ) {
		case 0: goto st0;
		case 42: goto tr11;
	}
	goto tr9;
st0:
cs = 0;
	goto _out;
tr11:
#line 76 "rlscan.rl"
	{ escapeXML( (*p) ); }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 394 "rlscan.cpp"
	switch( (*p) ) {
		case 0: goto st0;
		case 42: goto tr11;
		case 47: goto tr12;
	}
	goto tr9;
tr12:
#line 76 "rlscan.rl"
	{ escapeXML( (*p) ); }
#line 77 "rlscan.rl"
	{ {cs = stack[--top];goto _again;} }
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 411 "rlscan.cpp"
	goto st0;
tr13:
#line 112 "rlscan.rl"
	{{p = ((te))-1;}{ escapeXML( *ts ); }}
	goto st31;
tr15:
#line 79 "rlscan.rl"
	{te = p+1;{
		escapeXML( ts, te-ts );
	}}
	goto st31;
tr18:
#line 79 "rlscan.rl"
	{te = p+1;{
		escapeXML( ts, te-ts );
	}}
	goto st31;
tr21:
#line 79 "rlscan.rl"
	{te = p+1;{
		escapeXML( ts, te-ts );
	}}
	goto st31;
tr51:
#line 112 "rlscan.rl"
	{te = p+1;{ escapeXML( *ts ); }}
	goto st31;
tr55:
#line 97 "rlscan.rl"
	{te = p+1;{
			write( '{' );
			inline_depth += 1; 
		}}
	goto st31;
tr56:
#line 102 "rlscan.rl"
	{te = p+1;{
			write( '}' );
			/* If dropping down to the last } then return 
			 * to ragel code. */
			if ( --inline_depth == 0 ) {
				write( "</inline>\n" );
				{goto st35;}
			}
		}}
	goto st31;
tr57:
#line 112 "rlscan.rl"
	{te = p;p--;{ escapeXML( *ts ); }}
	goto st31;
tr58:
#line 91 "rlscan.rl"
	{te = p+1;{
			write( "/*" );
			{stack[top++] = 31; goto st6;}
		}}
	goto st31;
st31:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 1 "NONE"
	{ts = p;}
#line 477 "rlscan.cpp"
	switch( (*p) ) {
		case 0: goto st0;
		case 34: goto tr52;
		case 39: goto tr53;
		case 47: goto tr54;
		case 123: goto tr55;
		case 125: goto tr56;
	}
	goto tr51;
tr52:
#line 1 "NONE"
	{te = p+1;}
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
#line 495 "rlscan.cpp"
	switch( (*p) ) {
		case 34: goto tr15;
		case 92: goto st9;
	}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 34: goto tr15;
		case 92: goto st9;
	}
	goto st8;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	goto st8;
tr53:
#line 1 "NONE"
	{te = p+1;}
	goto st33;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
#line 523 "rlscan.cpp"
	switch( (*p) ) {
		case 39: goto tr18;
		case 92: goto st11;
	}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 39: goto tr18;
		case 92: goto st11;
	}
	goto st10;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	goto st10;
tr54:
#line 1 "NONE"
	{te = p+1;}
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 551 "rlscan.cpp"
	switch( (*p) ) {
		case 42: goto tr58;
		case 47: goto st12;
	}
	goto tr57;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 10 )
		goto tr21;
	goto st12;
tr22:
#line 193 "rlscan.rl"
	{{p = ((te))-1;}{
			write( "<symbol>" );
			escapeXML( (*p) );
			write( "</symbol>\n" );
		}}
	goto st35;
tr24:
#line 166 "rlscan.rl"
	{te = p+1;{
			write( "<double_lit>" );
			escapeXML( ts, te-ts );
			write( "</double_lit>\n" );
		}}
	goto st35;
tr27:
#line 156 "rlscan.rl"
	{te = p+1;}
	goto st35;
tr29:
#line 159 "rlscan.rl"
	{te = p+1;{
			write( "<single_lit>" );
			escapeXML( ts, te-ts );
			write( "</single_lit>\n" );
		}}
	goto st35;
tr32:
#line 180 "rlscan.rl"
	{te = p+1;{
			write( "<re_lit>" );
			escapeXML( ts, te-ts );
			write( "</re_lit>\n" );
		}}
	goto st35;
tr34:
#line 142 "rlscan.rl"
	{{p = ((te))-1;}{
			write( "<int>" );
			write( ts, te-ts );
			write( "</int>\n" );
		}}
	goto st35;
tr38:
#line 173 "rlscan.rl"
	{te = p+1;{
			write( "<or_lit>" );
			escapeXML( ts, te-ts );
			write( "</or_lit>\n" );
		}}
	goto st35;
tr39:
#line 120 "rlscan.rl"
	{te = p+1;{
			if ( !single_line ) {
				write( "</section>\n" );
				{goto st24;}
			}
		}}
	goto st35;
tr59:
#line 199 "rlscan.rl"
	{te = p+1;}
	goto st35;
tr60:
#line 127 "rlscan.rl"
	{te = p+1;{
			if ( single_line ) {
				write( "</section>\n" );
				{goto st24;}
			}
		}}
	goto st35;
tr61:
#line 193 "rlscan.rl"
	{te = p+1;{
			write( "<symbol>" );
			escapeXML( (*p) );
			write( "</symbol>\n" );
		}}
	goto st35;
tr70:
#line 187 "rlscan.rl"
	{te = p+1;{
			inline_depth = 1;
			write( "<inline>{" );
			{goto st31;}
		}}
	goto st35;
tr72:
#line 193 "rlscan.rl"
	{te = p;p--;{
			write( "<symbol>" );
			escapeXML( (*p) );
			write( "</symbol>\n" );
		}}
	goto st35;
tr73:
#line 142 "rlscan.rl"
	{te = p;p--;{
			write( "<int>" );
			write( ts, te-ts );
			write( "</int>\n" );
		}}
	goto st35;
tr75:
#line 149 "rlscan.rl"
	{te = p;p--;{
			write( "<hex>" );
			write( ts, te-ts );
			write( "</hex>\n" );
		}}
	goto st35;
tr76:
#line 135 "rlscan.rl"
	{te = p;p--;{
			write( "<word>" );
			write( ts, te-ts );
			write( "</word>\n" );
		}}
	goto st35;
st35:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof35;
case 35:
#line 1 "NONE"
	{ts = p;}
#line 694 "rlscan.cpp"
	switch( (*p) ) {
		case 0: goto st0;
		case 10: goto tr60;
		case 34: goto tr62;
		case 35: goto tr63;
		case 39: goto tr64;
		case 47: goto tr65;
		case 48: goto tr66;
		case 91: goto tr69;
		case 95: goto st43;
		case 123: goto tr70;
		case 125: goto tr71;
	}
	if ( (*p) < 65 ) {
		if ( (*p) < 49 ) {
			if ( 33 <= (*p) && (*p) <= 46 )
				goto tr61;
		} else if ( (*p) > 57 ) {
			if ( 58 <= (*p) && (*p) <= 64 )
				goto tr61;
		} else
			goto st41;
	} else if ( (*p) > 90 ) {
		if ( (*p) < 97 ) {
			if ( 92 <= (*p) && (*p) <= 96 )
				goto tr61;
		} else if ( (*p) > 122 ) {
			if ( 124 <= (*p) && (*p) <= 126 )
				goto tr61;
		} else
			goto st43;
	} else
		goto st43;
	goto tr59;
tr62:
#line 1 "NONE"
	{te = p+1;}
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 737 "rlscan.cpp"
	switch( (*p) ) {
		case 34: goto tr24;
		case 92: goto st14;
	}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 34: goto tr24;
		case 92: goto st14;
	}
	goto st13;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	goto st13;
tr63:
#line 1 "NONE"
	{te = p+1;}
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 765 "rlscan.cpp"
	if ( (*p) == 10 )
		goto tr27;
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 10 )
		goto tr27;
	goto st15;
tr64:
#line 1 "NONE"
	{te = p+1;}
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 784 "rlscan.cpp"
	switch( (*p) ) {
		case 39: goto tr29;
		case 92: goto st17;
	}
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 39: goto tr29;
		case 92: goto st17;
	}
	goto st16;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	goto st16;
tr65:
#line 1 "NONE"
	{te = p+1;}
	goto st39;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
#line 812 "rlscan.cpp"
	switch( (*p) ) {
		case 47: goto tr32;
		case 92: goto st19;
	}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 47: goto tr32;
		case 92: goto st19;
	}
	goto st18;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	goto st18;
tr66:
#line 1 "NONE"
	{te = p+1;}
	goto st40;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
#line 840 "rlscan.cpp"
	if ( (*p) == 120 )
		goto st20;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st41;
	goto tr73;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st41;
	goto tr73;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st42;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st42;
	} else
		goto st42;
	goto tr34;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st42;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st42;
	} else
		goto st42;
	goto tr75;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	if ( (*p) == 95 )
		goto st43;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st43;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st43;
	} else
		goto st43;
	goto tr76;
tr69:
#line 1 "NONE"
	{te = p+1;}
	goto st44;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
#line 902 "rlscan.cpp"
	switch( (*p) ) {
		case 92: goto st22;
		case 93: goto tr38;
	}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 92: goto st22;
		case 93: goto tr38;
	}
	goto st21;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	goto st21;
tr71:
#line 1 "NONE"
	{te = p+1;}
	goto st45;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
#line 930 "rlscan.cpp"
	if ( (*p) == 37 )
		goto st23;
	goto tr72;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) == 37 )
		goto tr39;
	goto tr22;
	}
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 25: goto tr46;
	case 1: goto tr0;
	case 2: goto tr0;
	case 26: goto tr46;
	case 27: goto tr48;
	case 28: goto tr46;
	case 3: goto tr0;
	case 4: goto tr0;
	case 29: goto tr46;
	case 5: goto tr0;
	case 32: goto tr57;
	case 8: goto tr13;
	case 9: goto tr13;
	case 33: goto tr57;
	case 10: goto tr13;
	case 11: goto tr13;
	case 34: goto tr57;
	case 12: goto tr13;
	case 36: goto tr72;
	case 13: goto tr22;
	case 14: goto tr22;
	case 37: goto tr72;
	case 15: goto tr22;
	case 38: goto tr72;
	case 16: goto tr22;
	case 17: goto tr22;
	case 39: goto tr72;
	case 18: goto tr22;
	case 19: goto tr22;
	case 40: goto tr73;
	case 41: goto tr73;
	case 20: goto tr34;
	case 42: goto tr75;
	case 43: goto tr76;
	case 44: goto tr72;
	case 21: goto tr22;
	case 22: goto tr22;
	case 45: goto tr72;
	case 23: goto tr22;
	}
	}

	_out: {}
	}

#line 282 "rlscan.rl"

		if ( cs == RagelScan_error ) {
			/* Machine failed before finding a token. */
			cerr << "PARSE ERROR" << endl;
			exit(1);
		}

		if ( ts == 0 )
			have = 0;
		else {
			/* There is a prefix to preserve, shift it over. */
			have = pe - ts;
			memmove( inbuf, ts, have );
			te = inbuf + (te-ts);
			ts = inbuf;
		}
	}
	return 0;
}
