#include <bits/stdc++.h>

using namespace std;

string A[7];
int cost[4] = {1, 10, 100, 1000};

bool done(string A[7])
{
  return (A[2] == "###A#B#C#D###" &&
	  A[3] == "  #A#B#C#D#" &&
	  A[4] == "  #A#B#C#D#" &&
	  A[5] == "  #A#B#C#D#");
}

typedef long long ll;
typedef tuple<int,int,int,int> ti4;
map<string,ll> memo;
map<string,ti4> bestmove;

  
ll search(string A[7])
{
  string H = A[1]+A[2]+A[3]+A[4]+A[5];
  if (memo.find(H) != memo.end()) {
    return memo[H];
  }

  // try moving each one out
  if (done(A)) return memo[H] = 0;
  memo[H] = INT_MAX;

  ll ans = INT_MAX;
  for (int c = 0; c < 4; c++) {
    int col = 3 + c*2;
    int row = 2;
    while (row < 6 && A[row][col] == '.') {
      row++;
    }
    if (row == 6) {
      // this col is empty
      continue;
    }

    char ch = A[row][col];
    bool stay = (ch-'A') == c;
    for (int r = row+1; r < 6 && stay; r++) {
      stay &= A[r][col] == ch;
    }
    if (stay) continue;      // don't move it again
    
    A[row][col] = '.';

    for (int j = col; j >= 0 && A[1][j] == '.'; j--) {
      if (A[2][j] != '#') continue;    // room below
      A[1][j] = ch;
      ll temp = cost[ch-'A'] * (col-j + row-1) + search(A);
      if (temp < ans) {
	ans = temp;
	bestmove[H] = make_tuple(1, row, col, j);
      }
      A[1][j] = '.';
    }
    
    for (int j = col; j < 13 && A[1][j] == '.'; j++) {
      if (A[2][j] != '#') continue;    // room below
      A[1][j] = ch;
      ll temp = cost[ch-'A'] * (j-col + row-1) + search(A);
      if (temp < ans) {
	ans = temp;
	bestmove[H] = make_tuple(1, row, col, j);
      }
      A[1][j] = '.';
    }
    
    A[row][col] = ch;
  }
  
  // try moving each one in
  for (int j = 0; j < 13; j++) {
    if (!isalpha(A[1][j])) continue;
    int dest = 3 + (A[1][j] - 'A') * 2;
    int row = -1;
    bool good = true;
    for (int r = 5; r >= 2 && good; r--) {
      if (A[r][dest] == '.') {
	row = r;
	break;
      } else if (A[r][dest] != A[1][j]) {
	good = false;
      }
    }
    
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

    char ch = A[1][j];
    assert(isalpha(ch));
    A[1][j] = '.';
    A[row][dest] = ch;
    ll temp = cost[ch-'A'] * (abs(dest-j) + row-1) + search(A);
    if (temp < ans) {
      ans = temp;
      bestmove[H] = make_tuple(2, row, j, dest);
    }

    A[row][dest] = '.';
    A[1][j] = ch;
  }

  return memo[H] = ans;
}

void trace(string A[7])
{
  string H = A[1]+A[2]+A[3]+A[4]+A[5];
  cout << memo[H] << endl;
  for (int i = 0; i < 7; i++) {
    cout << A[i] << endl;
  }
  cout << "==========" << endl;
  if (done(A)) return;
  
  auto &t = bestmove[H];
  auto [type,row,col,dest] = t;
  if (get<0>(t) == 1) {
    char ch = A[row][col];
    A[row][col] = '.';
    A[1][dest] = ch;
    trace(A);
  } else {
    char ch = A[1][col];
    A[1][col] = '.';
    A[row][dest] = ch;
    trace(A);
  }

}

int main()
{
  
  for (int i = 0; i < 3; i++) {
    getline(cin, A[i]);
  }
  A[3] = "  #D#C#B#A#";
  A[4] = "  #D#B#A#C#";
  for (int i = 5; i < 7; i++) {
    getline(cin, A[i]);
  }

  int ans = search(A);
  cout << ans << endl;

  //  trace(A);
    
  return 0;
}
