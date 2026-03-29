//
// The trick here is to normalize the game board.  I am turning this into
// a vector of rows, because cells only affect each other in a line.
// So each diagonal line is turned into a row.
//
// For each cell index, I get the row and column indices.
// Then for each of the player's trees, see if I am blocked by another tree
// (both mine and others).
//
// Tree a blocks tree b if:
//
// - they are in same row
// - a is to the left of b (col[a] < col[b])
// - a is at least as tall as b
// - col[b] - col[a] <= height of a

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> board = {
  {4,9,15,22},
  {3,8,14,21,28},
  {2,7,13,20,27,33},
  {1,6,12,19,26,32,37},
  {5,11,18,25,31,36},
  {10,17,24,30,35},
  {16,23,29,34}
};

int row[38], col[38];

void init()
{
  for (int r = 0; r < board.size(); r++) {
    for (int c = 0; c < board[r].size(); c++) {
      row[board[r][c]] = r;
      col[board[r][c]] = c;
    }
  }
}

// does t1 block t2
bool block(pair<int,int> t1, pair<int,int> t2)
{
  int r1 = row[t1.first], c1 = col[t1.first];
  int r2 = row[t2.first], c2 = col[t2.first];

  if (r1 != r2) return false;                // not in the same line
  if (c1 > c2) return false;                 // t1 comes after
  if (t1.second < t2.second) return false;   // cannot block larger tree

  return (c2 - c1 <= t1.second);             // in shadow
}

int main()
{
  init();

  const string size_str = " SML";
  int N, M;
  vector<pair<int, int>> others, mine;

  cin >> N;
  for (int i = 0; i < N; i++) {
    int p;
    char x;
    cin >> p >> x;
    others.emplace_back(p, size_str.find(x));
  }
  cin >> M;
  for (int i = 0; i < M; i++) {
    int p;
    char x;
    cin >> p >> x;
    mine.emplace_back(p, size_str.find(x));
  }

  int tokens = 0;

  for (int i = 0; i < M; i++) {
    bool blocked = false;
    for (int j = 0; j < N; j++) {
      blocked |= block(others[j], mine[i]);
    }
    for (int j = 0; j < M; j++) {
      blocked |= (i != j && block(mine[j], mine[i]));
    }
    if (!blocked) {
      tokens += mine[i].second;
    }
  }
    
  cout << tokens << endl;
  
  return 0;
}
