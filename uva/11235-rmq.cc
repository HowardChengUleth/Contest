#include <iostream>
#include <algorithm>
#include <cassert>
#include <climits>

using namespace std;
const int MAX_N = 100000;
int size;

void constructRMQ(int A[MAX_N], int M[4*MAX_N], int n) {
  size = 1; while(size < n) size <<= 1;
  for (int i=0; i < size; i++) M[size-1+i] = (i < n ? A[i] : INT_MIN);
  for (int i=size-2; i>=0; i--) M[i] = max(M[2*i+1],M[2*i+2]);
}

int getmax(int M[4*MAX_N], int a, int b, int st=0,int en=size,int ind=0) {
  if (a > b || a >= en || b < st)         return INT_MIN;
  if ((a <= st && en <= b) || st+1 >= en) return M[ind];
  int mid = (st+en)/2;
  return max(getmax(M,a,b,st,mid,2*ind+1), getmax(M,a,b,mid,en,2*ind+2));
}

void update(int A[MAX_N], int M[4*MAX_N], int i, int val){
  A[i] = val; M[i += size-1] = val;
  while((i = (i-1)/2)) M[i] = max(M[2*i+1],M[2*i+2]);
}

int M[4*MAX_N];

int main()
{
  int A[100000];
  int start[100000];
  
  int n, q;
  while (cin >> n >> q && n) {
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }

    int j;
    for (int i = 0; i < n; ) {
      for (j = i+1; j < n && A[i] == A[j]; j++)
	;
      int c = j - i;
      int s = i;
      for (; i < j; i++) {
	A[i] = c;
	start[i] = s;
      }
    }

    constructRMQ(A, M, n);
    
    while (q--) {
      int i, j;
      cin >> i >> j;
      i--;   j--;

      int ans = 0;

      if (start[i] == start[j]) {
	// same segment
	ans = j - i + 1;
      } else {
	ans = A[i] - (i - start[i]);        // segment i is in
	ans = max(ans, j - start[j] + 1);   // segment j is in
	i = start[i] + A[i];
	j = start[j] - 1;
	ans = max(ans, getmax(M, i, j));
      }

      cout << ans << endl;
    }
  }

  return 0;
}
