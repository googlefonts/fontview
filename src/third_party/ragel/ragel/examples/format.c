
#line 1 "format.rl"
/*
 * Partial printf implementation.
 */

#define BUFLEN 1024
#include <stdio.h>

typedef void (*WriteFunc)( char *data, int len );

struct format
{
	char buf[BUFLEN+1];
	int buflen;
	WriteFunc write;

	int flags;
	int width;
	int prec;
	int cs;
};

void do_conv( struct format *fsm, char c )
{
	printf( "flags: %x\n", fsm->flags );
	printf( "width: %i\n", fsm->width );
	printf( "prec: %i\n", fsm->prec );
	printf( "conv: %c\n", c );
	printf( "\n" );
}

#define FL_HASH          0x01
#define FL_ZERO          0x02
#define FL_DASH          0x04
#define FL_SPACE         0x08
#define FL_PLUS          0x10

#define FL_HAS_WIDTH   0x0100
#define FL_WIDTH_ARG   0x0200
#define FL_HAS_PREC    0x0400
#define FL_PREC_ARG    0x0800

#define FL_LEN_H     0x010000
#define FL_LEN_HH    0x020000
#define FL_LEN_L     0x040000
#define FL_LEN_LL    0x080000


#line 137 "format.rl"



#line 55 "format.c"
static const int format_start = 11;
static const int format_first_final = 11;
static const int format_error = 0;

static const int format_en_main = 11;


#line 140 "format.rl"

void format_init( struct format *fsm )
{
	fsm->buflen = 0;
	
#line 69 "format.c"
	{
	 fsm->cs = format_start;
	}

#line 145 "format.rl"
}

void format_execute( struct format *fsm, const char *data, int len, int isEof )
{
	const char *p = data;
	const char *pe = data + len;
	const char *eof = isEof ? pe : 0;

	
#line 84 "format.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  fsm->cs )
	{
tr3:
#line 113 "format.rl"
	{
		if ( fsm->buflen == BUFLEN ) {
			fsm->write( fsm->buf, fsm->buflen );
			fsm->buflen = 0;
		}
		fsm->buf[fsm->buflen++] = (*p);
	}
	goto st11;
tr10:
#line 99 "format.rl"
	{ 
		do_conv( fsm, (*p) );
	}
	goto st11;
tr14:
#line 63 "format.rl"
	{ fsm->flags |= FL_HAS_WIDTH; }
#line 99 "format.rl"
	{ 
		do_conv( fsm, (*p) );
	}
	goto st11;
tr19:
#line 69 "format.rl"
	{ fsm->flags |= FL_HAS_PREC; }
#line 99 "format.rl"
	{ 
		do_conv( fsm, (*p) );
	}
	goto st11;
tr22:
#line 86 "format.rl"
	{ fsm->flags |= FL_LEN_H; }
#line 99 "format.rl"
	{ 
		do_conv( fsm, (*p) );
	}
	goto st11;
tr24:
#line 87 "format.rl"
	{ fsm->flags |= FL_LEN_L; }
#line 99 "format.rl"
	{ 
		do_conv( fsm, (*p) );
	}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 142 "format.c"
	if ( (*p) == 37 )
		goto tr26;
	goto tr3;
tr26:
#line 51 "format.rl"
	{
		fsm->flags = 0;
		fsm->width = 0;
		fsm->prec = 0;
	}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 158 "format.c"
	switch( (*p) ) {
		case 32: goto tr1;
		case 35: goto tr2;
		case 37: goto tr3;
		case 42: goto tr4;
		case 43: goto tr5;
		case 45: goto tr6;
		case 46: goto st4;
		case 48: goto tr8;
		case 88: goto tr10;
		case 104: goto st6;
		case 105: goto tr10;
		case 108: goto st8;
		case 115: goto tr10;
		case 117: goto tr10;
		case 120: goto tr10;
	}
	if ( (*p) < 99 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto tr9;
	} else if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr10;
	} else
		goto tr10;
	goto tr0;
tr0:
#line 128 "format.rl"
	{
		printf("ERROR ON CHAR: 0x%x\n", (*p) );
	}
	goto st0;
#line 191 "format.c"
st0:
 fsm->cs = 0;
	goto _out;
tr1:
#line 76 "format.rl"
	{ fsm->flags |= FL_SPACE; }
	goto st2;
tr2:
#line 73 "format.rl"
	{ fsm->flags |= FL_HASH; }
	goto st2;
tr5:
#line 77 "format.rl"
	{ fsm->flags |= FL_PLUS; }
	goto st2;
tr6:
#line 75 "format.rl"
	{ fsm->flags |= FL_DASH; }
	goto st2;
tr8:
#line 74 "format.rl"
	{ fsm->flags |= FL_ZERO; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 219 "format.c"
	switch( (*p) ) {
		case 32: goto tr1;
		case 35: goto tr2;
		case 42: goto tr4;
		case 43: goto tr5;
		case 45: goto tr6;
		case 46: goto st4;
		case 48: goto tr8;
		case 88: goto tr10;
		case 104: goto st6;
		case 105: goto tr10;
		case 108: goto st8;
		case 115: goto tr10;
		case 117: goto tr10;
		case 120: goto tr10;
	}
	if ( (*p) < 99 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto tr9;
	} else if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr10;
	} else
		goto tr10;
	goto tr0;
tr4:
#line 62 "format.rl"
	{ fsm->flags |= FL_WIDTH_ARG; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 253 "format.c"
	switch( (*p) ) {
		case 46: goto tr13;
		case 88: goto tr14;
		case 104: goto tr15;
		case 105: goto tr14;
		case 108: goto tr16;
		case 115: goto tr14;
		case 117: goto tr14;
		case 120: goto tr14;
	}
	if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr14;
	} else if ( (*p) >= 99 )
		goto tr14;
	goto tr0;
tr13:
#line 63 "format.rl"
	{ fsm->flags |= FL_HAS_WIDTH; }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 278 "format.c"
	switch( (*p) ) {
		case 42: goto tr17;
		case 88: goto tr19;
		case 104: goto tr20;
		case 105: goto tr19;
		case 108: goto tr21;
		case 115: goto tr19;
		case 117: goto tr19;
		case 120: goto tr19;
	}
	if ( (*p) < 99 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr18;
	} else if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr19;
	} else
		goto tr19;
	goto tr0;
tr17:
#line 68 "format.rl"
	{ fsm->flags |= FL_PREC_ARG; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 306 "format.c"
	switch( (*p) ) {
		case 88: goto tr10;
		case 104: goto st6;
		case 105: goto tr10;
		case 108: goto st8;
		case 115: goto tr10;
		case 117: goto tr10;
		case 120: goto tr10;
	}
	if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr10;
	} else if ( (*p) >= 99 )
		goto tr10;
	goto tr0;
tr15:
#line 63 "format.rl"
	{ fsm->flags |= FL_HAS_WIDTH; }
	goto st6;
tr20:
#line 69 "format.rl"
	{ fsm->flags |= FL_HAS_PREC; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 334 "format.c"
	switch( (*p) ) {
		case 88: goto tr22;
		case 104: goto tr23;
		case 105: goto tr22;
		case 115: goto tr22;
		case 117: goto tr22;
		case 120: goto tr22;
	}
	if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr22;
	} else if ( (*p) >= 99 )
		goto tr22;
	goto tr0;
tr23:
#line 88 "format.rl"
	{ fsm->flags |= FL_LEN_HH; }
	goto st7;
tr25:
#line 89 "format.rl"
	{ fsm->flags |= FL_LEN_LL; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 361 "format.c"
	switch( (*p) ) {
		case 88: goto tr10;
		case 105: goto tr10;
		case 115: goto tr10;
		case 117: goto tr10;
		case 120: goto tr10;
	}
	if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr10;
	} else if ( (*p) >= 99 )
		goto tr10;
	goto tr0;
tr16:
#line 63 "format.rl"
	{ fsm->flags |= FL_HAS_WIDTH; }
	goto st8;
tr21:
#line 69 "format.rl"
	{ fsm->flags |= FL_HAS_PREC; }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 387 "format.c"
	switch( (*p) ) {
		case 88: goto tr24;
		case 105: goto tr24;
		case 108: goto tr25;
		case 115: goto tr24;
		case 117: goto tr24;
		case 120: goto tr24;
	}
	if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr24;
	} else if ( (*p) >= 99 )
		goto tr24;
	goto tr0;
tr18:
#line 67 "format.rl"
	{ fsm->prec = 10 * fsm->prec + ((*p)-'0'); }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 410 "format.c"
	switch( (*p) ) {
		case 88: goto tr19;
		case 104: goto tr20;
		case 105: goto tr19;
		case 108: goto tr21;
		case 115: goto tr19;
		case 117: goto tr19;
		case 120: goto tr19;
	}
	if ( (*p) < 99 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr18;
	} else if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr19;
	} else
		goto tr19;
	goto tr0;
tr9:
#line 61 "format.rl"
	{ fsm->width = 10 * fsm->width + ((*p)-'0'); }
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 437 "format.c"
	switch( (*p) ) {
		case 46: goto tr13;
		case 88: goto tr14;
		case 104: goto tr15;
		case 105: goto tr14;
		case 108: goto tr16;
		case 115: goto tr14;
		case 117: goto tr14;
		case 120: goto tr14;
	}
	if ( (*p) < 99 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr9;
	} else if ( (*p) > 100 ) {
		if ( 111 <= (*p) && (*p) <= 112 )
			goto tr14;
	} else
		goto tr14;
	goto tr0;
	}
	_test_eof11:  fsm->cs = 11; goto _test_eof; 
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

	_test_eof: {}
	if ( p == eof )
	{
	switch (  fsm->cs ) {
	case 11: 
#line 121 "format.rl"
	{
		if ( fsm->buflen > 0 )
			fsm->write( fsm->buf, fsm->buflen );
	}
	break;
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
	case 8: 
	case 9: 
	case 10: 
#line 125 "format.rl"
	{
		printf("EOF IN FORMAT\n");
	}
#line 128 "format.rl"
	{
		printf("ERROR ON CHAR: 0x%x\n", (*p) );
	}
	break;
#line 500 "format.c"
	}
	}

	_out: {}
	}

#line 154 "format.rl"
}

int format_finish( struct format *fsm )
{
	if ( fsm->cs == format_error )
		return -1;
	if ( fsm->cs >= format_first_final )
		return 1;
	return 0;
}


#define INPUT_BUFSIZE 2048

struct format fsm;
char buf[INPUT_BUFSIZE];

void write(char *data, int len )
{
	fwrite( data, 1, len, stdout );
}

int main()
{
	fsm.write = write;
	format_init( &fsm );
	while ( 1 ) {
		int len = fread( buf, 1, INPUT_BUFSIZE, stdin );
		int eof = len != INPUT_BUFSIZE;
		format_execute( &fsm, buf, len, eof );
		if ( eof )
			break;
	}
	if ( format_finish( &fsm ) <= 0 )
		printf("FAIL\n");
	return 0;
}

