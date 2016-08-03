
#line 1 "awkemu.rl"
/*
 * Perform the basic line parsing of input performed by awk.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#line 55 "awkemu.rl"



#line 18 "awkemu.c"
static const int awkemu_start = 2;

static const int awkemu_en_main = 2;


#line 58 "awkemu.rl"

#define MAXWORDS 256
#define BUFSIZE 4096
char buf[BUFSIZE];

int main()
{
	int i, nwords = 0;
	char *ls = 0;
	char *ws[MAXWORDS];
	char *we[MAXWORDS];

	int cs;
	int have = 0;

	
#line 41 "awkemu.c"
	{
	cs = awkemu_start;
	}

#line 74 "awkemu.rl"

	while ( 1 ) {
		char *p, *pe, *data = buf + have;
		int len, space = BUFSIZE - have;
		/* fprintf( stderr, "space: %i\n", space ); */

		if ( space == 0 ) { 
			fprintf(stderr, "buffer out of space\n");
			exit(1);
		}

		len = fread( data, 1, space, stdin );
		/* fprintf( stderr, "len: %i\n", len ); */
		if ( len == 0 )
			break;

		/* Find the last newline by searching backwards. This is where 
		 * we will stop processing on this iteration. */
		p = buf;
		pe = buf + have + len - 1;
		while ( *pe != '\n' && pe >= buf )
			pe--;
		pe += 1;

		/* fprintf( stderr, "running on: %i\n", pe - p ); */

		
#line 74 "awkemu.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr2:
#line 17 "awkemu.rl"
	{
		we[nwords++] = p;
	}
#line 26 "awkemu.rl"
	{
		printf("endline(%i): ", nwords );
		fwrite( ls, 1, p - ls, stdout );
		printf("\n");

		for ( i = 0; i < nwords; i++ ) {
			printf("  word: ");
			fwrite( ws[i], 1, we[i] - ws[i], stdout );
			printf("\n");
		}
	}
	goto st2;
tr5:
#line 26 "awkemu.rl"
	{
		printf("endline(%i): ", nwords );
		fwrite( ls, 1, p - ls, stdout );
		printf("\n");

		for ( i = 0; i < nwords; i++ ) {
			printf("  word: ");
			fwrite( ws[i], 1, we[i] - ws[i], stdout );
			printf("\n");
		}
	}
	goto st2;
tr8:
#line 21 "awkemu.rl"
	{
		nwords = 0;
		ls = p;
	}
#line 26 "awkemu.rl"
	{
		printf("endline(%i): ", nwords );
		fwrite( ls, 1, p - ls, stdout );
		printf("\n");

		for ( i = 0; i < nwords; i++ ) {
			printf("  word: ");
			fwrite( ws[i], 1, we[i] - ws[i], stdout );
			printf("\n");
		}
	}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 135 "awkemu.c"
	switch( (*p) ) {
		case 9: goto tr7;
		case 10: goto tr8;
		case 32: goto tr7;
	}
	goto tr6;
tr3:
#line 13 "awkemu.rl"
	{
		ws[nwords] = p;
	}
	goto st0;
tr6:
#line 21 "awkemu.rl"
	{
		nwords = 0;
		ls = p;
	}
#line 13 "awkemu.rl"
	{
		ws[nwords] = p;
	}
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 163 "awkemu.c"
	switch( (*p) ) {
		case 9: goto tr1;
		case 10: goto tr2;
		case 32: goto tr1;
	}
	goto st0;
tr1:
#line 17 "awkemu.rl"
	{
		we[nwords++] = p;
	}
	goto st1;
tr7:
#line 21 "awkemu.rl"
	{
		nwords = 0;
		ls = p;
	}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 187 "awkemu.c"
	switch( (*p) ) {
		case 9: goto st1;
		case 10: goto tr5;
		case 32: goto st1;
	}
	goto tr3;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 

	_test_eof: {}
	}

#line 101 "awkemu.rl"

		/* How much is still in the buffer. */
		have = data + len - pe;
		if ( have > 0 )
			memmove( buf, pe, have );

		/* fprintf(stderr, "have: %i\n", have ); */

		if ( len < space )
			break;
	}

	if ( have > 0 )
		fprintf(stderr, "input not newline terminated\n");
	return 0;
}
