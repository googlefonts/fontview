
#line 1 "statechart.rl"
/*
 * Demonstrate the use of labels, the epsilon operator, and the join operator
 * for creating machines using the named state and transition list paradigm.
 * This implementes the same machine as the atoi example.
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

struct StateChart
{
	bool neg;
	int val;
	int cs;

	int init( );
	int execute( const char *data, int len );
	int finish( );
};


#line 66 "statechart.rl"



#line 33 "statechart.cpp"
static const int StateChart_start = 3;
static const int StateChart_first_final = 3;
static const int StateChart_error = 0;

static const int StateChart_en_main = 3;


#line 69 "statechart.rl"

int StateChart::init( )
{
	neg = false;
	val = false;
	
#line 48 "statechart.cpp"
	{
	cs = StateChart_start;
	}

#line 75 "statechart.rl"
	return 1;
}

int StateChart::execute( const char *data, int len )
{
	const char *p = data;
	const char *pe = data + len;

	
#line 63 "statechart.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr2:
#line 41 "statechart.rl"
	{
		if ( neg )
			val = -1 * val;
	}
#line 65 "statechart.rl"
	{ cout << val << endl; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 82 "statechart.cpp"
	switch( (*p) ) {
		case 43: goto tr3;
		case 45: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr5;
	goto st0;
st0:
cs = 0;
	goto _out;
tr3:
#line 28 "statechart.rl"
	{
		neg = false;
		val = 0;
	}
	goto st1;
tr4:
#line 28 "statechart.rl"
	{
		neg = false;
		val = 0;
	}
#line 33 "statechart.rl"
	{
		neg = true;
	}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 115 "statechart.cpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr0;
	goto st0;
tr0:
#line 37 "statechart.rl"
	{ 
		val = val * 10 + ((*p) - '0');
	}
	goto st2;
tr5:
#line 28 "statechart.rl"
	{
		neg = false;
		val = 0;
	}
#line 37 "statechart.rl"
	{ 
		val = val * 10 + ((*p) - '0');
	}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 140 "statechart.cpp"
	if ( (*p) == 10 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr0;
	goto st0;
	}
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 84 "statechart.rl"

	if ( cs == StateChart_error )
		return -1;
	if ( cs >= StateChart_first_final )
		return 1;
	return 0;
}

int StateChart::finish( )
{
	if ( cs == StateChart_error )
		return -1;
	if ( cs >= StateChart_first_final )
		return 1;
	return 0;
}


#define BUFSIZE 1024

int main()
{
	char buf[BUFSIZE];

	StateChart atoi;
	atoi.init();
	while ( fgets( buf, sizeof(buf), stdin ) != 0 ) {
		atoi.execute( buf, strlen(buf) );
	}
	if ( atoi.finish() <= 0 )
		cerr << "statechart: error: parsing input" << endl;
	return 0;
}
