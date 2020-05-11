/*

1995-96 ACM International Collegiate Programming Contest
Southwestern European Regional Contest
ETH Zurich, Switzerland
December 9, 1995


Problem: Triangle

Idea and first implementation:	Berni Seybold, ETH Zurich
Implementation:					Manuel Bleichenbacher, Head Judge

Source file: triangle.c / triangle.p
Input file: triangle.in
Output file: triangle.out

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


const double cEps = 0.000001;
const double cUndefined = -1.0;

typedef enum {
	FALSE = 0,
	TRUE = 1
} bool;

typedef enum {
	errOk,
	errInvalidInput,
	errManySolutions
} ErrorState;

typedef double *Params;


bool IsDef( double value );
bool CheckParams (Params p);
bool ValidTriangle (Params p);
bool IsState( char* s, Params p );
void Rule_SumOfAngles( Params p, int alpha, int beta, int gamma, ErrorState* err );
void Rule_Sine_Side( Params p, int a, int b, int alpha, int beta, ErrorState* err );
void Rule_Sine_Angle( Params p, int alpha, int a, int beta, int b, ErrorState* err );
void Rule_Cosine_Side( Params p, int a, int b, int alpha, int c, ErrorState* err );
void Rule_Cosine_Angle( Params p, int alpha, int a, int b, int c, ErrorState* err );
bool DetectRule( Params p, ErrorState* err );
void CalculateTriangle( Params p, ErrorState* err );


double pi;


bool IsDef ( double value )
{
	return value != cUndefined;
}


bool CheckParams (Params p)
{
	int i;
	
	for (i = 0; i < 3; i++) {
	
		/* check side */
		if ( IsDef (p[i*2]) )
			if ( p[i*2] <= 0.0 )
				return FALSE;
		
		/* check angle */
		if ( IsDef (p[i*2+1]) )
			if ( p[i*2+1] <= 0.0 || p[i*2+1] >= pi )
				return FALSE;
	}
	return TRUE;
}


bool ValidTriangle (Params p)
{
	double q;
	
	if ( ! CheckParams( p ) )
		return FALSE;
	if ( fabs( p[1] + p[3] + p[5] - pi ) >= cEps )
		return FALSE;
	if ( p[0] + p[2] <= p[4] || p[2] + p[4] <= p[0] || p[4] + p[0] <= p[2] )
		return FALSE;
	q = sin( p[3] ) / p[0];
	if ( fabs( sin( p[5] ) / p[2] - q ) >= cEps )
		return FALSE;
	if ( fabs( sin( p[1] ) / p[4] - q ) >= cEps )
		return FALSE;
	return TRUE;
}


bool IsState( char* s, Params p )
{
	/* s:	"x" = already defined
			"0" = to be calculated
			"-" = don't care
	*/
	
	int i;
	for (i = 0; i < 6; i++) {
		if ( s[i] == 'x' && ! IsDef( p[i] ) )
			return FALSE;	/* rule cannot be applied */
		if ( s[i] == '0' && IsDef( p[i] ) )
			return FALSE;	/* parameter already defined */
	}
	return TRUE;
}


void Rule_SumOfAngles( Params p, int alpha, int beta, int gamma, ErrorState* err )
{
	/*	Rule:		alpha + beta + gamma = Pi
		To compute:	alpha	( = Pi - beta - gamma )
		Defined:	beta, gamma
	*/
	
	assert( (alpha & 1) == 1 );
	assert( (beta  & 1) == 1 );
	assert( (gamma & 1) == 1 );
	assert( alpha != beta );
	assert( beta != gamma );
	
	p[alpha] = pi - p[beta] - p[gamma];
}


void Rule_Sine_Angle( Params p, int alpha, int beta, int a, int b, ErrorState* err )
{
	/*	Rule:		a / sin(alpha) = b / sin(beta) = c / sin(gamma)
		To compute:	alpha	( = arcsin( a * sin(beta) / b ) )
		Situation:	Angle-Side-Side or Side-Side-Angle
		Defined:	beta, a, b
	*/
	
	double q;
	
	assert( (a & 1) == 0 );
	assert( (b & 1) == 0 );
	assert( (alpha & 1) == 1 );
	assert( (beta & 1) == 1);
	assert( a != b );
	assert( alpha != beta );
	
	if ( p[b] > 0.0 ) {
		q = p[a] * sin (p[beta]) / p[b];
		if ( fabs( q - 1.0 ) < cEps ) {		/* special case: single solution! */
			p[alpha] = pi / 2.0;
			return;
		}
		if ( q < 1.0 ) {
			if ( p[b] < p[a] ) {	/* two solutions */
				*err = errManySolutions;
				return;
			}
			p[alpha] = asin(q);	/* alpha must be smaller than 90 deg here,
									so we don't have to check for a second solution */
			return;
		}
	}
	*err = errInvalidInput;	/* no solution */
}


void Rule_Sine_Side( Params p, int a, int b, int alpha, int beta, ErrorState* err )
{
	/*	Rule:		a / sin(alpha) = b / sin(beta) = c / sin(gamma)
		To compute:	a	( = sin(alpha) * b / sin(beta) )
		Situation:	Angle-Angle-Side or Side-Angle-Angle
		Defined:	alpha, b, beta
	*/
	
	double q, m;
	
	assert( (a & 1) == 0 );
	assert( (b & 1) == 0 );
	assert( (alpha & 1) == 1 );
	assert( (beta & 1) == 1);
	assert( a != b );
	assert( alpha != beta );
	
	if ( sin( p[beta] ) != 0.0 ) {
		q = sin( p[alpha] ) / sin( p[beta] );
		m = p[b] * sin( p[alpha] );
		if ( q != 0.0 ) {
			p[a] = p[b] * q;
			return;
		} else if ( m != 0.0 ) {
			p[a] = m / sin( p[beta] );
			return;
		}
	}
	*err = errInvalidInput;
}


void Rule_Cosine_Side( Params p, int a, int b, int alpha, int c, ErrorState* err )
{
	/*	Rule:		a^2 = b^2 + c^2 - 2 * b * c * cos(alpha)
		To compute:	a
		Defined:	b, c, alpha
		Situation:	Side-Angle-Side
	*/
	
	double sqra;
	
	assert( (a & 1) == 0 );
	assert( (b & 1) == 0 );
	assert( (alpha & 1) == 1 );
	assert( (c & 1) == 0 );
	assert( a != b );
	assert( b != c );
	
	/*	Summing up the squares of number can be tricky,
		but we have only three numbers and use doubles.
		That should be enough precision	*/
	sqra = -2 * p[b] * p[c] * cos( p[alpha] ) + p[b] * p[b] + p[c] * p[c];
	if (sqra > 0.0 ) {
		p[a] = sqrt( sqra );
		return;
	}
	*err = errInvalidInput;
}


void Rule_Cosine_Angle( Params p, int alpha, int a, int b, int c, ErrorState* err )
{
	/*	Rule:		a^2 = b^2 + c^2 - 2 * b * c * cos(alpha)
		To compute:	alpha
		Defined:	a, b, c
		Situation:	Side-Side-Side
	*/

	double d, cosalpha;
	
	assert( (alpha & 1) == 1 );
	assert( (a & 1) == 0 );
	assert( (b & 1) == 0 );
	assert( (c & 1) == 0 );
	assert( a != b );
	assert( b != c );
	
	d = 2.0 * p[b] * p[c];
	if ( d != 0.0 ) {
		cosalpha = ( - p[a] * p[a] + p[b] * p[b] + p[c] * p[c] ) / d;
		if ( fabs( cosalpha ) <= 1.0 ) {
			p[alpha] = acos( cosalpha );
			return;
		}
	}
	*err = errInvalidInput;
}


bool DetectRule( Params p, ErrorState* err )
{
	/* Format of pattern: a, gamma, b, alpha, c, beta */
	
	/* Angle - Side - Side and Side - Side - Angle */
	/* This rule may only be applied if exactly three parameters are defined. */
	/* Otherwise it could turn valid cases into "More than one solution" cases. */
	if (IsState( "x00xx0", p )) { Rule_Sine_Angle  ( p, 1, 3, 4, 0, err ); return TRUE; }
	if (IsState( "x0x00x", p )) { Rule_Sine_Angle  ( p, 3, 5, 0, 2, err ); return TRUE; }
	if (IsState( "0xx0x0", p )) { Rule_Sine_Angle  ( p, 5, 1, 2, 4, err ); return TRUE; }
	if (IsState( "00x0xx", p )) { Rule_Sine_Angle  ( p, 1, 5, 4, 2, err ); return TRUE; }
	if (IsState( "xx00x0", p )) { Rule_Sine_Angle  ( p, 3, 1, 0, 4, err ); return TRUE; }
	if (IsState( "x0xx00", p )) { Rule_Sine_Angle  ( p, 5, 3, 2, 0, err ); return TRUE; }
	
	/* Side - Side - Side */
	if (IsState( "x-x0x-", p )) { Rule_Cosine_Angle( p, 3, 0, 2, 4, err ); return TRUE; }
	if (IsState( "x-x-x0", p )) { Rule_Cosine_Angle( p, 5, 2, 4, 0, err ); return TRUE; }
	if (IsState( "x0x-x-", p )) { Rule_Cosine_Angle( p, 1, 4, 0, 2, err ); return TRUE; }

	/* Side - Angle - Side */
	if (IsState( "0-xxx-", p )) { Rule_Cosine_Side ( p, 0, 2, 3, 4, err ); return TRUE; }
	if (IsState( "x-0-xx", p )) { Rule_Cosine_Side ( p, 2, 4, 5, 0, err ); return TRUE; }
	if (IsState( "xxx-0-", p )) { Rule_Cosine_Side ( p, 4, 0, 1, 2, err ); return TRUE; }

	/* Side - Angle - Angle and Angle - Angle - Side */
	if (IsState( "0-xx-x", p )) { Rule_Sine_Side   ( p, 0, 2, 3, 5, err ); return TRUE; }
	if (IsState( "-x0-xx", p )) { Rule_Sine_Side   ( p, 2, 4, 5, 1, err ); return TRUE; }
	if (IsState( "xx-x0-", p )) { Rule_Sine_Side   ( p, 4, 0, 1, 3, err ); return TRUE; }
	if (IsState( "0x-xx-", p )) { Rule_Sine_Side   ( p, 0, 4, 3, 1, err ); return TRUE; }
	if (IsState( "x-0x-x", p )) { Rule_Sine_Side   ( p, 2, 0, 5, 3, err ); return TRUE; }
	if (IsState( "-xx-0x", p )) { Rule_Sine_Side   ( p, 4, 2, 1, 5, err ); return TRUE; }

	/* This is our replacement for the Angle - Side - Angle rule. */
	if (IsState( "-0-x-x", p )) { Rule_SumOfAngles ( p, 1, 3, 5, err ); return TRUE; }
	if (IsState( "-x-0-x", p )) { Rule_SumOfAngles ( p, 3, 5, 1, err ); return TRUE; }
	if (IsState( "-x-x-0", p )) { Rule_SumOfAngles ( p, 5, 1, 3, err ); return TRUE; }
	
	return FALSE;
}


void CalculateTriangle( Params p, ErrorState* err )
{
	bool changed = TRUE;
	*err = errOk;
	
	/* valid parameters on first sight? */
	if ( !CheckParams (p) )
		*err = errInvalidInput;
	
	while (changed && *err == errOk)
		changed = DetectRule( p, err );

	/* have all parameters been calculated? */
	if (*err == errOk && !IsState( "xxxxxx", p ) )
		*err = errInvalidInput;
	
	/* valid triangle? */	
	if (*err == errOk && !ValidTriangle( p ) )
		*err = errInvalidInput;
}


int main( int argc, char* argv[] )
{
	int			nTriangles;
	int			i, dummy;
	FILE*		fin;
	FILE*		fout;
	
	ErrorState	err;
	double		_p[6];
	Params		p = _p;
	
	pi = atan(1) * 4.0;
	
	/*
	fin = fopen( "triangle.in", "r" );
	assert( fin != 0 );
	fout = fopen( "triangle.out", "w" );
	assert( fout != 0 );
	*/
	fin = stdin;
	fout = stdout;
	
	/* read the number of triangles */
	dummy = fscanf( fin, "%d", &nTriangles );
	assert( dummy == 1 );
	
	for (i = 0; i < nTriangles; i++) {
	
		/* read the six parameters */
		/* input file: a, alpha, b, beta, c, gamma */
		/* internal rep: a, gamma, b, alpha, c, beta */
		dummy = fscanf( fin, "%lf %lf %lf %lf %lf %lf",
			&p[0], &p[3], &p[2], &p[5], &p[4], &p[1] );
		assert( dummy == 6 );
		
		CalculateTriangle( p, &err );
		
		/* write the result */
		if ( err == errOk )
			/* internal rep: a, gamma, b, alpha, c, beta */
			/* output file: a, alpha, b, beta, c, gamma */
			fprintf( fout, "%0.10f %0.10f %0.10f %0.10f %0.10f %0.10f\n",
				p[0], p[3], p[2], p[5], p[4], p[1] );
		else if ( err == errInvalidInput )
			fprintf( fout, "Invalid input.\n" );
		else if ( err == errManySolutions )
			fprintf( fout, "More than one solution.\n" );
		else
			assert( FALSE );
	}
	
	fclose( fin );
	fclose( fout );
	
	return 0;
}

