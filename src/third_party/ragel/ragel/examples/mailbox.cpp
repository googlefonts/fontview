
#line 1 "mailbox.rl"
/*
 * Parses unix mail boxes into headers and bodies.
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define BUFSIZE 2048

/* A growable buffer for collecting headers. */
struct Buffer
{
	Buffer() : data(0), allocated(0), length(0) { }
	~Buffer() { empty(); }

	void append( char p ) {
		if ( ++length > allocated )
			upAllocate( length*2 );
		data[length-1] = p;
	}
		
	void clear() { length = 0; }
	void upAllocate( int len );
	void empty();

	char *data;
	int allocated;
	int length;
};


struct MailboxScanner
{
	Buffer headName;
	Buffer headContent;

	int cs, top, stack[1];

	int init( );
	int execute( const char *data, int len, bool isEof );
	int finish( );
};


#line 137 "mailbox.rl"



#line 56 "mailbox.cpp"
static const int MailboxScanner_start = 100;
static const int MailboxScanner_first_final = 100;
static const int MailboxScanner_error = 0;

static const int MailboxScanner_en_consumeHeader = 102;
static const int MailboxScanner_en_printHeader = 103;
static const int MailboxScanner_en_main = 100;


#line 140 "mailbox.rl"

int MailboxScanner::init( )
{
	
#line 71 "mailbox.cpp"
	{
	cs = MailboxScanner_start;
	top = 0;
	}

#line 144 "mailbox.rl"
	return 1;
}

int MailboxScanner::execute( const char *data, int len, bool isEof )
{
	const char *p = data;
	const char *pe = data + len;
	const char *eof = isEof ? pe : 0;

	
#line 88 "mailbox.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	goto _resume;

_again:
	switch ( cs ) {
		case 100: goto st100;
		case 0: goto st0;
		case 1: goto st1;
		case 2: goto st2;
		case 3: goto st3;
		case 4: goto st4;
		case 5: goto st5;
		case 6: goto st6;
		case 7: goto st7;
		case 8: goto st8;
		case 9: goto st9;
		case 10: goto st10;
		case 11: goto st11;
		case 12: goto st12;
		case 13: goto st13;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 23: goto st23;
		case 24: goto st24;
		case 25: goto st25;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 34: goto st34;
		case 101: goto st101;
		case 35: goto st35;
		case 36: goto st36;
		case 37: goto st37;
		case 38: goto st38;
		case 39: goto st39;
		case 40: goto st40;
		case 41: goto st41;
		case 42: goto st42;
		case 43: goto st43;
		case 44: goto st44;
		case 45: goto st45;
		case 46: goto st46;
		case 47: goto st47;
		case 48: goto st48;
		case 49: goto st49;
		case 50: goto st50;
		case 51: goto st51;
		case 52: goto st52;
		case 53: goto st53;
		case 54: goto st54;
		case 55: goto st55;
		case 56: goto st56;
		case 57: goto st57;
		case 58: goto st58;
		case 59: goto st59;
		case 60: goto st60;
		case 61: goto st61;
		case 62: goto st62;
		case 63: goto st63;
		case 64: goto st64;
		case 65: goto st65;
		case 66: goto st66;
		case 67: goto st67;
		case 68: goto st68;
		case 69: goto st69;
		case 70: goto st70;
		case 71: goto st71;
		case 72: goto st72;
		case 73: goto st73;
		case 74: goto st74;
		case 75: goto st75;
		case 76: goto st76;
		case 77: goto st77;
		case 78: goto st78;
		case 79: goto st79;
		case 80: goto st80;
		case 81: goto st81;
		case 82: goto st82;
		case 83: goto st83;
		case 84: goto st84;
		case 85: goto st85;
		case 86: goto st86;
		case 87: goto st87;
		case 88: goto st88;
		case 89: goto st89;
		case 90: goto st90;
		case 91: goto st91;
		case 92: goto st92;
		case 93: goto st93;
		case 94: goto st94;
		case 95: goto st95;
		case 96: goto st96;
		case 97: goto st97;
		case 102: goto st102;
		case 98: goto st98;
		case 103: goto st103;
		case 99: goto st99;
		case 104: goto st104;
	default: break;
	}

	if ( ++p == pe )
		goto _test_eof;
_resume:
	switch ( cs )
	{
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	if ( (*p) == 70 )
		goto st1;
	goto st0;
tr101:
#line 92 "mailbox.rl"
	{
		headContent.append(0);
		cout << headContent.data << endl;
		headContent.clear();
		p--;
		{cs = stack[--top];goto _again;}
	}
	goto st0;
#line 226 "mailbox.cpp"
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 114 )
		goto st2;
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 111 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 109 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 32 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	goto st5;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st7;
	goto st5;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st8;
	goto st5;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st9;
	goto st5;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st10;
	}
	goto st5;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st11;
	goto st5;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st12;
	goto st5;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st13;
	goto st5;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st14;
	}
	goto st5;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st15;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st11;
	} else if ( (*p) >= 48 )
		goto st97;
	goto st5;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st7;
	} else if ( (*p) >= 48 )
		goto st16;
	goto st5;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st17;
	}
	goto st5;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st7;
	} else if ( (*p) >= 48 )
		goto st18;
	goto st5;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st19;
	goto st5;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
		case 58: goto st20;
	}
	goto st5;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st21;
	goto st5;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st22;
	goto st5;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st23;
		case 58: goto st94;
	}
	goto st5;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
		case 43: goto st24;
		case 45: goto st24;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st92;
	} else if ( (*p) >= 48 )
		goto st84;
	goto st5;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st25;
	goto st5;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st26;
	goto st5;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st27;
	goto st5;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st28;
	goto st5;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st29;
	}
	goto st5;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st7;
	} else if ( (*p) >= 48 )
		goto st30;
	goto st5;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st31;
	goto st5;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st32;
	goto st5;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st33;
	goto st5;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 10: goto st34;
		case 32: goto st6;
	}
	goto st5;
tr88:
#line 108 "mailbox.rl"
	{
		headName.append(0);
		if ( strcmp( headName.data, "From" ) == 0 ||
				strcmp( headName.data, "To" ) == 0 ||
				strcmp( headName.data, "Subject" ) == 0 )
		{
			/* Print the header name, then jump to a machine the will display
			 * the contents. */
			cout << headName.data << ":";
			headName.clear();
			{stack[top++] = 34; goto st103;}
		}

		headName.clear();
		{stack[top++] = 34; goto st102;}
	}
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 603 "mailbox.cpp"
	if ( (*p) == 10 )
		goto tr38;
	if ( (*p) > 57 ) {
		if ( 59 <= (*p) && (*p) <= 126 )
			goto tr39;
	} else if ( (*p) >= 33 )
		goto tr39;
	goto st0;
tr38:
#line 55 "mailbox.rl"
	{ cout << endl; }
	goto st101;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
#line 620 "mailbox.cpp"
	switch( (*p) ) {
		case 10: goto st101;
		case 70: goto st36;
	}
	goto st35;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	if ( (*p) == 10 )
		goto st101;
	goto st35;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 10: goto st101;
		case 114: goto st37;
	}
	goto st35;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 10: goto st101;
		case 111: goto st38;
	}
	goto st35;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 10: goto st101;
		case 109: goto st39;
	}
	goto st35;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st40;
	}
	goto st35;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	goto st40;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st42;
	goto st40;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st43;
	goto st40;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st44;
	goto st40;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st45;
	}
	goto st40;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st46;
	goto st40;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st47;
	goto st40;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto st48;
	goto st40;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st49;
	}
	goto st40;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st50;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st46;
	} else if ( (*p) >= 48 )
		goto st82;
	goto st40;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st42;
	} else if ( (*p) >= 48 )
		goto st51;
	goto st40;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st52;
	}
	goto st40;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st42;
	} else if ( (*p) >= 48 )
		goto st53;
	goto st40;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st54;
	goto st40;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
		case 58: goto st55;
	}
	goto st40;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st56;
	goto st40;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st57;
	goto st40;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st58;
		case 58: goto st79;
	}
	goto st40;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
		case 43: goto st59;
		case 45: goto st59;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st77;
	} else if ( (*p) >= 48 )
		goto st69;
	goto st40;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st60;
	goto st40;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st61;
	goto st40;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st62;
	goto st40;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st63;
	goto st40;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st64;
	}
	goto st40;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st42;
	} else if ( (*p) >= 48 )
		goto st65;
	goto st40;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st66;
	goto st40;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st67;
	goto st40;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st68;
	goto st40;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 10: goto st34;
		case 32: goto st41;
	}
	goto st40;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st70;
	goto st40;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st71;
	goto st40;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st72;
	goto st40;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 10: goto st34;
		case 32: goto st73;
	}
	goto st40;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
		case 43: goto st74;
		case 45: goto st74;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st75;
	goto st40;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st65;
	goto st40;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st43;
	} else if ( (*p) >= 65 )
		goto st76;
	goto st40;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st68;
	goto st40;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st43;
	} else if ( (*p) >= 65 )
		goto st78;
	goto st40;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st63;
	goto st40;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st80;
	goto st40;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st81;
	goto st40;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st58;
	}
	goto st40;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 10: goto st101;
		case 32: goto st41;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st51;
	goto st40;
tr39:
#line 52 "mailbox.rl"
	{ headName.append((*p)); }
	goto st83;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
#line 1157 "mailbox.cpp"
	if ( (*p) == 58 )
		goto tr88;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr39;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st85;
	goto st5;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st86;
	goto st5;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st87;
	goto st5;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 10: goto st34;
		case 32: goto st88;
	}
	goto st5;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
		case 43: goto st89;
		case 45: goto st89;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st90;
	goto st5;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st30;
	goto st5;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st8;
	} else if ( (*p) >= 65 )
		goto st91;
	goto st5;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st33;
	goto st5;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st8;
	} else if ( (*p) >= 65 )
		goto st93;
	goto st5;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st28;
	goto st5;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st95;
	goto st5;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st96;
	goto st5;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st23;
	}
	goto st5;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 10: goto st0;
		case 32: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st16;
	goto st5;
tr99:
#line 86 "mailbox.rl"
	{p--; {cs = stack[--top];goto _again;}}
	goto st102;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
#line 1329 "mailbox.cpp"
	if ( (*p) == 10 )
		goto st98;
	goto st102;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 9: goto st102;
		case 32: goto st102;
	}
	goto tr99;
tr106:
#line 89 "mailbox.rl"
	{headContent.append((*p));}
	goto st103;
tr108:
#line 90 "mailbox.rl"
	{headContent.append(' ');}
#line 89 "mailbox.rl"
	{headContent.append((*p));}
	goto st103;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
#line 1356 "mailbox.cpp"
	if ( (*p) == 10 )
		goto st99;
	goto tr106;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 9: goto st104;
		case 32: goto st104;
	}
	goto tr101;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	switch( (*p) ) {
		case 9: goto st104;
		case 10: goto st99;
		case 32: goto st104;
	}
	goto tr108;
	}
	_test_eof100: cs = 100; goto _test_eof; 
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
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 104: 
#line 90 "mailbox.rl"
	{headContent.append(' ');}
	break;
	case 99: 
#line 92 "mailbox.rl"
	{
		headContent.append(0);
		cout << headContent.data << endl;
		headContent.clear();
		p--;
		{cs = stack[--top];goto _again;}
	}
	break;
#line 1503 "mailbox.cpp"
	}
	}

	_out: {}
	}

#line 154 "mailbox.rl"

	if ( cs == MailboxScanner_error )
		return -1;
	if ( cs >= MailboxScanner_first_final )
		return 1;
	return 0;
}

int MailboxScanner::finish( )
{
	if ( cs == MailboxScanner_error )
		return -1;
	if ( cs >= MailboxScanner_first_final )
		return 1;
	return 0;
}


void Buffer::empty()
{
	if ( data != 0 ) {
		free( data );

		data = 0;
		length = 0;
		allocated = 0;
	}
}

void Buffer::upAllocate( int len )
{
	if ( data == 0 )
		data = (char*) malloc( len );
	else
		data = (char*) realloc( data, len );
	allocated = len;
}

MailboxScanner mailbox;
char buf[BUFSIZE];

int main()
{
	mailbox.init();
	while ( 1 ) {
		int len = fread( buf, 1, BUFSIZE, stdin );
		mailbox.execute( buf, len, len != BUFSIZE );
		if ( len != BUFSIZE )
			break;
	}
	if ( mailbox.finish() <= 0 )
		cerr << "mailbox: error parsing input" << endl;
	return 0;
}
