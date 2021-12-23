#include <bits/stdc++.h>

using namespace std;

string A[5];
int cost[4] = {1, 10, 100, 1000};

bool done(string A[5])
{
  return (A[2] == "###A#B#C#D###" &&
	  A[3] == "  #A#B#C#D#");
}

typedef long long ll;

map<string,ll> memo;

ll search(string A[5])
{
  if (done(A)) return 0;

  string H = A[1]+A[2]+A[3];
  if (memo.find(H) != memo.end()) {
    return memo[H];
  }
  
  // try moving each one out
  ll &ans = memo[H];
  ans = INT_MAX;
  for (int c = 0; c < 4; c++) {
    int col = 3 + c*2;
    int row = 2;
    while (row < 4 && A[row][col] == '.') {
      row++;
    }
    if (row == 4) {
      // this col is empty
      continue;
    }

    char ch = A[row][col];
    A[row][col] = '.';

    for (int j = col; j >= 0 && A[1][j] == '.'; j--) {
      if (A[2][j] != '#') continue;    // room below
      A[1][j] = ch;
      ll temp = cost[ch-'A'] * (col-j + row-1) + search(A);
      ans = min(ans, temp);
      A[1][j] = '.';
    }
    
    for (int j = col; j < 13 && A[1][j] == '.'; j++) {
      if (A[2][j] != '#') continue;    // room below
      A[1][j] = ch;
      ll temp = cost[ch-'A'] * (j-col + row-1) + search(A);
      ans = min(ans, temp);
      A[1][j] = '.';
    }
    
    A[row][col] = ch;
  }
  
  // try moving each one in
  for (int j = 0; j < 13; j++) {
    if (!isalpha(A[1][j])) continue;
    int dest = 3 + (A[1][j] - 'A') * 2;
    bool good = (A[2][dest] == '.' &&
		 (A[3][dest] == '.' || A[3][dest] == A[1][j]));
    if (!good) continue;         // cannot move into dest
    int c1, c2;
    if (j < dest) {
      c1 = j+1;
      c2 = dest;
    } else {
      c1 = dest;
      c2 = j-1;
    }
    for (int c = c1; c <= c2; c++) {
      good &= A[1][c] == '.';
    }
    if (!good) continue;         // blocked

    int row = 3;
    if (A[3][dest] != '.') row = 2;
    char ch = A[1][j];
    A[1][j] = '.';
    A[row][dest] = ch;
    ll temp = cost[ch-'A'] * (abs(dest-j) + row-1) + search(A);
    ans = min(ans, temp);
    A[row][dest] = '.';
    A[1][j] = ch;
  }
      
  return ans;

}


int main()
{
  for (int i = 0; i < 5; i++) {
    getline(cin, A[i]);
  }

  int ans = search(A);
  cout << ans << endl;
  
  return 0;
}
