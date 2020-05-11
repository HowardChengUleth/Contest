//
// we have X <= a <= b <= c <= Y
//
// Let f(X,Y) = number of triangles with the above constraints.
// Let g(c)   = number of triangles with 1 <= a and c being the largest
//              side
//
// Then f(X,Y) = sum(g(c), c = X..Y).
//
// Let's start with X = 1.
//
// If we look at g(c) then there are c*(c+1)/2 candidate pairs for (a,b).
// Looking at the candidate pairs:
//
// (1,1)
// (1,2) (2,2)
// (1,3) (2,3) (3,3)
// ...
// (1,c) (2,c) (3,c) ...    (c,c)
//
// We see that every antidiagonal contains pairs with the same sum, and the
// sums range from 2 to 2*c.  The number of elements in the antidiagonals
// give the sequence: 1, 1, 2, 2, 3, 3, ..., (c+1)/2, ... , 3, 3, 2, 2, 1, 1.
//
// So all we have to do is to look at this sequence, and subtract from
// c*(c+1)/2.  So
//
//   g(c) = c*(c+1)/2 - (c-1)*(c+1)/4       if c is odd
//        = c*(c+1)/2 - c^2/4               if c is even
//
// So if we add this all up: f(1,Y) = sum(g(1,c), c = 1..Y)
//
//   f(1,Y) = sum(c*(c+1)/2, c=1..Y) -
//            sum(k^2, k=1..Y/2) - sum((k-1)*k, k=1..Y/2)
//          = (2*Y^3 + 9*Y^2 + 10*Y) / 24                    if Y is even
// and
//          = sum(c*(c+1)/2, c=1..Y) -
//            sum(k^2, k=1..(Y-1)/2) - sum((k-1)*k, k=1..(Y+1)/2)
//           = (2*Y^3 + 9*Y^2 + 10*Y + 3) / 24               if Y is odd
//
// or f(1,Y) = floor((2*Y^3 + 9*Y^2 + 10*Y + 3) / 24) for all Y
//
// If X > 1 and 2*X <= Y, we want to reduce the problem so X = 1.  Again,
// we fix the largest side c with X <= a <= b <= c <= Y.
//
// Subtracting X-1 from all sides, we get:
//
//       1 <= a' <= b' <= c' <= Y - (X-1)
//
// where a' = a - (X-1), b' = b - (X-1), c' = c - (X-1)
//
// with the condition that a+b > c, or
//
//       a' + b' > c' - (X-1)
//
// Let h(X, c) = number of triples 1 <= a <= b <= c with largest side c,
//               satisfying the two constraints above.
//
// So now f(X,Y) = sum(h(X, c), c=1..Y-X+1)
//
// we use the same argument as above when X = 1, so that
//
//   h(X, c) = c*(c+1)/2 - (c-X)*(c-X+2)/4      if c - (X-1) is odd
//           = c*(c+1)/2 - (c-(X-1))^2/4        if c - (X-1) is even
//
// the second term should be taken only if it is positive
//
// Note that h(1,c) = g(c) in the above, so I guess we don't need to handle
// the special case.
//
// So f(X,Y) = sum(h(X, c), c=1..Y-X+1)
//           = sum(c*(c+1)/2, c=1..Y-X+1) -
//             sum((2*k-X)^2/4, k=(X+1)/2..(Y-X+1)/2) -
//             sum((2*k-X)*(2*k-X+2)/4, k=(X+1)/2..(Y-X+1)/2)
//
//                             if Y - X is odd, X is odd
// and
//           = sum(c*(c+1)/2, c=1..Y-X+1) -
//             sum((2*k-X)^2/4, k=X/2..(Y-X+1)/2) -
//             sum((2*k-X)*(2*k-X+2)/4, k=X/2..(Y-X+1)/2)
//
//                             if Y - X is odd, X is even
//
// and
//           = sum(c*(c+1)/2, c=1..Y-X+1) -
//             sum((2*k-X)^2/4, k=X/2..(Y-X+2)/2) -
//             sum((2*k-X)*(2*k-X+2)/4, k=X/2..(Y-X)/2)
//
//                                             if Y - X is even, X is even
//             
// and
//           = sum(c*(c+1)/2, c=1..Y-X+1) -
//             sum((2*k-X+1)^2/4, k=(X-1)/2..(Y-X)/2) -
//             sum((2*k-1-X)*(2*k+1-X)/4, k=(X+1)/2..(Y-X+2)/2)
//
//                                             if Y - X is even, X is odd
// 

#include <iostream>

using namespace std;

long long f(long long X, long long Y)
{
  long long ans = (Y-X+3)*(Y-X+1)*(Y-X+2)/6;  // there are no subtractive terms

  if ((Y-X) % 2 != 0) {
    if (X % 2 != 0) {
      if (Y >= 2*X) {
	ans -= (2*Y+3-4*X)*(Y+4-2*X)*(Y+2-2*X)/24;
      }
    } else {
      if (Y >= 2*X-1) {
	ans -= (Y+3-2*X)*(Y+1-2*X)*(2*Y+7-4*X)/24;
      }
    }
  } else {
    if (X % 2 == 0) {
      if (Y >= 2*X-2) {
	ans -= (Y+2-2*X)*(Y+4-2*X)*(Y+3-2*X)/24;
      }
      if (Y >= 2*X) {
	ans -= (Y-2*X)*(Y+2-2*X)*(Y+4-2*X)/24;
      }
    } else {
      if (Y >= 2*X-1) {
	ans -= (Y+1-2*X)*(Y+3-2*X)*(2*Y+7-4*X)/24;
      }
    }
  }
  return ans;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int X, Y;
    cin >> X >> Y;
    cout << f(X, Y) << endl;
  }

  return 0;
}
