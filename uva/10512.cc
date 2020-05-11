#include <iostream>
#include <cmath>

using namespace std;


bool check(long long X, long long Y,
	   long long P, long long Q)
{
  return (-32768 <= Y && Y <= X && X <= 32767 &&
	  (X+Y)*Y == P && (X-Y)*X == Q);
}

int isqrt(long long x, long long &r)
{
  r = (long long)floorl(sqrtl((long double)x) + 0.5);
  return r*r == x;
}

int main(void)
{
  int N;

  cin >> N;
  for (int i = 1; i <= N; i++) {
    cout << "Case " << i << ":" << endl;
    long long P, Q;

    cin >> P >> Q;

    long long a = 2;
    long long b = -(3*P+Q);
    long long c = P*P;
    long long disc = b*b - 4*a*c;
    long long X, Y, X_sq, Y_sq, r;
    long long XX, YY;
    bool found = 0;

    if (0 <= disc && isqrt(disc, r)) {
      Y_sq = -b + r;
      if (Y_sq % (2*a) == 0 && 0 <= Y_sq) {
	Y_sq /= 2*a;
	if (isqrt(Y_sq, Y)) {
	  X_sq = P+Q-Y_sq;
	  if (0 <= X_sq && isqrt(X_sq, X)) {
	    if (check(-X, -Y, P, Q) && (!found || -X < XX)) {
	      XX = -X; YY = -Y; found = 1;
	    } else if (check(-X, Y, P, Q) && (!found || -X < XX)) {
	      XX = -X; YY = Y; found = 1;
	    } else if (check(X, -Y, P, Q) && (!found || X < XX)) {
	      XX = X; YY = -Y; found = 1;
	    } else if (check(X, Y, P, Q) && (!found || X < XX)) {
	      XX = X; YY = Y; found = 1;
	    }
	  }
	}
      }
      Y_sq = -b - r;
      if (Y_sq % (2*a) == 0 && 0 <= Y_sq) {
	Y_sq /= (2*a);
	if (isqrt(Y_sq, Y)) {
	  X_sq = P+Q-Y_sq;
	  if (0 <= X_sq && isqrt(X_sq, X)) {
	    if (check(-X, -Y, P, Q) && (!found || -X < XX)) {
	      XX = -X; YY = -Y; found = 1;
	    } else if (check(-X, Y, P, Q) && (!found || -X < XX)) {
	      XX = -X; YY = Y; found = 1;
	    } else if (check(X, -Y, P, Q) && (!found || X < XX)) {
	      XX = X; YY = -Y; found = 1;
	    } else if (check(X, Y, P, Q) && (!found || X < XX)) {
	      XX = X; YY = Y; found = 1;
	    }
	  }
	}
      }

    }
    if (found) {
      cout << XX << " " << YY << endl;
    } else {
      cout << "Impossible." << endl;
    }
  }
  return 0;
}

