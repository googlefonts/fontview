
#line 1 "concurrent.rl"
/*
 * Show off concurrent abilities.
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define BUFSIZE 2048

struct Concurrent
{
	int cur_char;
	int start_word;
	int start_comment;
	int start_literal;

	int cs;

	int init( );
	int execute( const char *data, int len, bool isEof );
	int finish( );
};


#line 75 "concurrent.rl"



#line 35 "concurrent.cpp"
static const int Concurrent_start = 0;
static const int Concurrent_first_final = 0;
static const int Concurrent_error = -1;

static const int Concurrent_en_main = 0;


#line 78 "concurrent.rl"

int Concurrent::init( )
{
	
#line 48 "concurrent.cpp"
	{
	cs = Concurrent_start;
	}

#line 82 "concurrent.rl"
	cur_char = 0;
	return 1;
}

int Concurrent::execute( const char *data, int len, bool isEof )
{
	const char *p = data;
	const char *pe = data + len;
	const char *eof = isEof ? pe : 0;

	
#line 65 "concurrent.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr1:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st0;
tr5:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
	goto st0;
tr19:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
	goto st0;
tr46:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 124 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr1;
		case 39: goto tr2;
		case 47: goto tr3;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr1;
	goto tr0;
tr0:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st1;
tr4:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st1;
tr18:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
	goto st1;
tr45:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 175 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr5;
		case 39: goto tr6;
		case 47: goto tr7;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr5;
	goto tr4;
tr13:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st2;
tr8:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st2;
tr2:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
#line 50 "concurrent.rl"
	{
		start_literal = cur_char;
	}
	goto st2;
tr6:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 50 "concurrent.rl"
	{
		start_literal = cur_char;
	}
	goto st2;
tr20:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
#line 50 "concurrent.rl"
	{
		start_literal = cur_char;
	}
	goto st2;
tr50:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
	goto st2;
tr47:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
#line 50 "concurrent.rl"
	{
		start_literal = cur_char;
	}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 269 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr9;
		case 39: goto tr10;
		case 47: goto tr11;
		case 92: goto tr12;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr9;
	goto tr8;
tr14:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st3;
tr9:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
	goto st3;
tr51:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 316 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr14;
		case 39: goto tr15;
		case 47: goto tr16;
		case 92: goto tr17;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr14;
	goto tr13;
tr15:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st4;
tr10:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st4;
tr52:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 357 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr19;
		case 39: goto tr20;
		case 47: goto tr21;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr19;
	goto tr18;
tr3:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
#line 42 "concurrent.rl"
	{
		start_comment = cur_char;
	}
	goto st5;
tr7:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 42 "concurrent.rl"
	{
		start_comment = cur_char;
	}
	goto st5;
tr21:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 42 "concurrent.rl"
	{
		start_comment = cur_char;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
	goto st5;
tr48:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
#line 42 "concurrent.rl"
	{
		start_comment = cur_char;
	}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 424 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr5;
		case 39: goto tr6;
		case 42: goto tr22;
		case 47: goto tr7;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr5;
	goto tr4;
tr26:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st6;
tr22:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st6;
tr40:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 465 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr23;
		case 39: goto tr24;
		case 42: goto tr25;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr23;
	goto tr22;
tr27:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st7;
tr23:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
	goto st7;
tr41:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 511 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr27;
		case 39: goto tr28;
		case 42: goto tr29;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr27;
	goto tr26;
tr35:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st8;
tr30:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st8;
tr28:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
#line 50 "concurrent.rl"
	{
		start_literal = cur_char;
	}
	goto st8;
tr24:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 50 "concurrent.rl"
	{
		start_literal = cur_char;
	}
	goto st8;
tr42:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
#line 50 "concurrent.rl"
	{
		start_literal = cur_char;
	}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 579 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr31;
		case 39: goto tr32;
		case 42: goto tr33;
		case 92: goto tr34;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr31;
	goto tr30;
tr36:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st9;
tr31:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 610 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr36;
		case 39: goto tr37;
		case 42: goto tr38;
		case 92: goto tr39;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr36;
	goto tr35;
tr37:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st10;
tr32:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 640 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr41;
		case 39: goto tr42;
		case 42: goto tr43;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr41;
	goto tr40;
tr29:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st11;
tr25:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st11;
tr43:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 680 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr23;
		case 39: goto tr24;
		case 42: goto tr25;
		case 47: goto tr44;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr23;
	goto tr22;
tr44:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 700 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr46;
		case 39: goto tr47;
		case 47: goto tr48;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr46;
	goto tr45;
tr38:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st13;
tr33:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 729 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr31;
		case 39: goto tr32;
		case 42: goto tr33;
		case 47: goto tr49;
		case 92: goto tr34;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr31;
	goto tr30;
tr49:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 750 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr51;
		case 39: goto tr52;
		case 47: goto tr53;
		case 92: goto tr54;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto tr50;
tr16:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
#line 42 "concurrent.rl"
	{
		start_comment = cur_char;
	}
	goto st15;
tr11:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 42 "concurrent.rl"
	{
		start_comment = cur_char;
	}
	goto st15;
tr53:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
#line 42 "concurrent.rl"
	{
		start_comment = cur_char;
	}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 803 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr9;
		case 39: goto tr10;
		case 42: goto tr30;
		case 47: goto tr11;
		case 92: goto tr12;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr9;
	goto tr8;
tr17:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st16;
tr12:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st16;
tr54:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 845 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr9;
		case 47: goto tr11;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr9;
	goto tr8;
tr39:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
#line 34 "concurrent.rl"
	{
		start_word = cur_char;
	}
	goto st17;
tr34:
#line 30 "concurrent.rl"
	{
		cur_char += 1;
	}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 873 "concurrent.cpp"
	switch( (*p) ) {
		case 32: goto tr31;
		case 42: goto tr33;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr31;
	goto tr30;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 5: 
	case 6: 
	case 8: 
	case 11: 
	case 13: 
	case 15: 
	case 16: 
	case 17: 
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
	break;
	case 12: 
	case 14: 
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
#line 45 "concurrent.rl"
	{
		cout << "comment: " << start_comment <<
				" " << cur_char-1 << endl;
	}
	break;
	case 4: 
	case 10: 
#line 37 "concurrent.rl"
	{
		cout << "word: " << start_word << 
				" " << cur_char-1 << endl;
	}
#line 53 "concurrent.rl"
	{
		cout << "literal: " << start_literal <<
				" " << cur_char-1 << endl;
	}
	break;
#line 947 "concurrent.cpp"
	}
	}

	}

#line 93 "concurrent.rl"

	if ( cs == Concurrent_error )
		return -1;
	if ( cs >= Concurrent_first_final )
		return 1;
	return 0;
}

int Concurrent::finish( )
{
	if ( cs == Concurrent_error )
		return -1;
	if ( cs >= Concurrent_first_final )
		return 1;
	return 0;
}

Concurrent concurrent;
char buf[BUFSIZE];

int main()
{
	concurrent.init();
	while ( 1 ) {
		int len = fread( buf, 1, BUFSIZE, stdin );
		concurrent.execute( buf, len, len != BUFSIZE );
		if ( len != BUFSIZE )
			break;
	}

	if ( concurrent.finish() <= 0 )
		cerr << "concurrent: error parsing input" << endl;
	return 0;
}
