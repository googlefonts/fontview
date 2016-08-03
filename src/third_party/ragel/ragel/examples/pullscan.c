
#line 1 "pullscan.rl"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096

typedef struct _Scanner {
	/* Scanner state. */
    int cs;
    int act;
    int have;
    int curline;
    char *ts;
    char *te;
    char *p;
    char *pe;
    char *eof;
	FILE *file;
	int done;

	/* Token data */
	char *data;
	int len;
    int value;

	char buf[BUFSIZE];
} Scanner;



#line 34 "pullscan.c"
static const int Scanner_start = 2;
static const int Scanner_first_final = 2;
static const int Scanner_error = -1;

static const int Scanner_en_main = 2;


#line 33 "pullscan.rl"


void scan_init( Scanner *s, FILE *file )
{
	memset (s, '\0', sizeof(Scanner));
	s->curline = 1;
	s->file = file;
	s->eof = 0;
	
#line 52 "pullscan.c"
	{
	 s->cs = Scanner_start;
	 s->ts = 0;
	 s->te = 0;
	 s->act = 0;
	}

#line 42 "pullscan.rl"
}

#define TK_NO_TOKEN (-1)
#define TK_ERR 128
#define TK_EOF 129
#define TK_Identifier 130
#define TK_Number 131
#define TK_String 132

#define ret_tok( _tok ) token = _tok; s->data = s->ts

int scan( Scanner *s )
{
	int token = TK_NO_TOKEN;
	int space, readlen;

	while ( 1 ) {
		if ( s->p == s->pe ) {
			printf("scanner: need more data\n");

			if ( s->ts == 0 )
				s->have = 0;
			else {
				/* There is data that needs to be shifted over. */
				printf("scanner: buffer broken mid token\n");
				s->have = s->pe - s->ts;
				memmove( s->buf, s->ts, s->have );
				s->te -= (s->ts-s->buf);
				s->ts = s->buf;
			}

			s->p = s->buf + s->have;
			space = BUFSIZE - s->have;

			if ( space == 0 ) {
				/* We filled up the buffer trying to scan a token. */
				printf("scanner: out of buffer space\n");
				return TK_ERR;
			}

			if ( s->done ) {
				printf("scanner: end of file\n");
				s->p[0] = 0;
				readlen = 1;
			}
			else {
				readlen = fread( s->p, 1, space, s->file );
				if ( readlen < space )
					s->done = 1;
			}

			s->pe = s->p + readlen;
		}

		
#line 116 "pullscan.c"
	{
	if ( ( s->p) == ( s->pe) )
		goto _test_eof;
	switch (  s->cs )
	{
tr0:
#line 125 "pullscan.rl"
	{{( s->p) = (( s->te))-1;}{ ret_tok( *s->p ); {( s->p)++;  s->cs = 2; goto _out;} }}
	goto st2;
tr2:
#line 113 "pullscan.rl"
	{ s->te = ( s->p)+1;{ ret_tok( TK_String ); {( s->p)++;  s->cs = 2; goto _out;} }}
	goto st2;
tr4:
#line 125 "pullscan.rl"
	{ s->te = ( s->p)+1;{ ret_tok( *s->p ); {( s->p)++;  s->cs = 2; goto _out;} }}
	goto st2;
tr5:
#line 121 "pullscan.rl"
	{ s->te = ( s->p)+1;{ ret_tok( TK_EOF ); {( s->p)++;  s->cs = 2; goto _out;} }}
	goto st2;
tr6:
#line 110 "pullscan.rl"
	{ s->te = ( s->p)+1;}
	goto st2;
tr10:
#line 125 "pullscan.rl"
	{ s->te = ( s->p);( s->p)--;{ ret_tok( *s->p ); {( s->p)++;  s->cs = 2; goto _out;} }}
	goto st2;
tr11:
#line 117 "pullscan.rl"
	{ s->te = ( s->p);( s->p)--;{ ret_tok( TK_Number ); {( s->p)++;  s->cs = 2; goto _out;} }}
	goto st2;
tr12:
#line 107 "pullscan.rl"
	{ s->te = ( s->p);( s->p)--;{ ret_tok( TK_Identifier ); {( s->p)++;  s->cs = 2; goto _out;} }}
	goto st2;
st2:
#line 1 "NONE"
	{ s->ts = 0;}
	if ( ++( s->p) == ( s->pe) )
		goto _test_eof2;
case 2:
#line 1 "NONE"
	{ s->ts = ( s->p);}
#line 162 "pullscan.c"
	switch( (*( s->p)) ) {
		case 0: goto tr5;
		case 32: goto tr6;
		case 34: goto tr7;
		case 95: goto st5;
	}
	if ( (*( s->p)) < 48 ) {
		if ( 9 <= (*( s->p)) && (*( s->p)) <= 10 )
			goto tr6;
	} else if ( (*( s->p)) > 57 ) {
		if ( (*( s->p)) > 90 ) {
			if ( 97 <= (*( s->p)) && (*( s->p)) <= 122 )
				goto st5;
		} else if ( (*( s->p)) >= 65 )
			goto st5;
	} else
		goto st4;
	goto tr4;
tr7:
#line 1 "NONE"
	{ s->te = ( s->p)+1;}
	goto st3;
st3:
	if ( ++( s->p) == ( s->pe) )
		goto _test_eof3;
case 3:
#line 189 "pullscan.c"
	switch( (*( s->p)) ) {
		case 34: goto tr2;
		case 92: goto st1;
	}
	goto st0;
st0:
	if ( ++( s->p) == ( s->pe) )
		goto _test_eof0;
case 0:
	switch( (*( s->p)) ) {
		case 34: goto tr2;
		case 92: goto st1;
	}
	goto st0;
st1:
	if ( ++( s->p) == ( s->pe) )
		goto _test_eof1;
case 1:
	goto st0;
st4:
	if ( ++( s->p) == ( s->pe) )
		goto _test_eof4;
case 4:
	if ( 48 <= (*( s->p)) && (*( s->p)) <= 57 )
		goto st4;
	goto tr11;
st5:
	if ( ++( s->p) == ( s->pe) )
		goto _test_eof5;
case 5:
	if ( (*( s->p)) == 95 )
		goto st5;
	if ( (*( s->p)) < 65 ) {
		if ( 48 <= (*( s->p)) && (*( s->p)) <= 57 )
			goto st5;
	} else if ( (*( s->p)) > 90 ) {
		if ( 97 <= (*( s->p)) && (*( s->p)) <= 122 )
			goto st5;
	} else
		goto st5;
	goto tr12;
	}
	_test_eof2:  s->cs = 2; goto _test_eof; 
	_test_eof3:  s->cs = 3; goto _test_eof; 
	_test_eof0:  s->cs = 0; goto _test_eof; 
	_test_eof1:  s->cs = 1; goto _test_eof; 
	_test_eof4:  s->cs = 4; goto _test_eof; 
	_test_eof5:  s->cs = 5; goto _test_eof; 

	_test_eof: {}
	if ( ( s->p) == ( s->eof) )
	{
	switch (  s->cs ) {
	case 3: goto tr10;
	case 0: goto tr0;
	case 1: goto tr0;
	case 4: goto tr11;
	case 5: goto tr12;
	}
	}

	_out: {}
	}

#line 130 "pullscan.rl"


		if ( s->cs == Scanner_error )
			return TK_ERR;

		if ( token != TK_NO_TOKEN ) {
			s->len = s->p - s->data;
			return token;
		}
	}
}


int main (int argc, char** argv)
{
	Scanner ss;
	int tok;

	scan_init(&ss, stdin);

	while ( 1 ) {
		tok = scan (&ss);
		if ( tok == TK_EOF ) {
			printf ("parser: EOF\n");
			break;
		}
		else if ( tok == TK_ERR ) {
			printf ("parser: ERR\n");
			break;
		}
		else {
			printf ("parser: %d \"", tok);
			fwrite ( ss.data, 1, ss.len, stdout );
			printf ("\"\n" );
		}
	}

	return 0;
}


