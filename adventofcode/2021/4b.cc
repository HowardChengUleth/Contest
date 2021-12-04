#include <bits/stdc++.h>

using namespace std;

struct Board
{
  int A[5][5];
  bool B[5][5];
  bool won;
  
  bool read()
  {
    for (int i = 0; i < 5; i++) {
      for (int j = 0;j < 5; j++) {
	if (!(cin >> A[i][j])) {
	  return false;
	}
	B[i][j] = false;
      }
    }
    won = false;
    return true;
  }

  bool mark(int x)
  {
    if (won) {
      return false;
    }
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
	if (A[i][j] == x) {
	  B[i][j] = true;
	}
      }
    }

    for (int i = 0; i < 5; i++) {
      int c = 0;
      for (int j = 0; j < 5; j++) {
	if (B[i][j]) c++;
      }
      if (c == 5) {
	won = true;
	return true;
      }
    }

    for (int j = 0; j < 5; j++) {
      int c = 0;
      for (int i = 0; i < 5; i++) {
	if (B[i][j]) c++;
      }
      if (c == 5) {
	won = true;
	return true;
      }
    }
    return false;
  }

  int score(int x) const {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
	if (!B[i][j]) sum += A[i][j];
      }
    }
    return sum * x;
  }
};

int main()
{
  string s;
  getline(cin, s);
  replace(begin(s), end(s), ',', ' ');
  istringstream iss(s);

  vector<int> draw;
  int x;
  while (iss >> x) {
    draw.push_back(x);
  }

  vector<Board> boards;
  Board B;

  while (B.read()) {
    boards.push_back(B);
  }

  int winner = 0;
  for (auto d : draw) {
    for (auto &B : boards) {
      if (B.mark(d)) {
	winner++;
	if (winner == boards.size()) {
	  cout << B.score(d) << endl;
	}
      }
    }
  }
  
  
  

  return 0;
}
