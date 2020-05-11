#include <iostream>
using namespace std;

const int MAX_N = 10030;
long long A[MAX_N];
long long B[MAX_N][2];

int main(){
   int N;
   while(cin >> N){
      for(int i=0;i<N;i++)
	 cin >> A[i];
      for(int i=0;i<=N;i++)
	 B[i][0] = 0;
      int v = 1;
      // j is the number of cards left
      // i is the starting card
      for(int j=2;j<=N;j+=2,v=1-v)
	 for(int i=N-j;i>=0;i--)
	   B[i][v] = max(A[i]     + min(B[i+1][1-v],B[i+2][1-v]),
			 A[i+j-1] + min(B[i+1][1-v],B[i][1-v]));
      cout << B[0][1-v] << endl;
   }
   return 0;
}
