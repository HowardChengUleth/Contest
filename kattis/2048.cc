#include <bits/stdc++.h>

using namespace std;

int board[4][4];

void transpose()
{
  int board2[4][4];
  for (int r = 0; r < 4; r++) {
    copy(board[r], board[r]+4, board2[r]);
  }
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      board[r][c] = board2[c][r];
    }
  }
}

void reverse()
{
  for (int r = 0; r < 4; r++) {
    reverse(board[r], board[r]+4);
  }
}

void normalize(int dir)
{
  if (dir & 1) {
    transpose();
  }
  if (dir & 2) {
    reverse();
  }
}

void restore(int dir)
{
  if (dir & 2) {
    reverse();
  }
  if (dir & 1) {
    transpose();
  }
}

void shiftrow(int r)
{
  int to = 0;
  for (int c = 0; c < 4; c++) {
    if (board[r][c]) {
      if (to != c) {
	board[r][to] = board[r][c];
	board[r][c] = 0;
      }
      to++;
    }
  }
}

void move()
{
  for (int r = 0; r < 4; r++) {
    shiftrow(r);
    for (int c = 0; c < 3; c++) {
      if (board[r][c] == board[r][c+1]) {
	board[r][c] *= 2;
	board[r][c+1] = 0;
      }
    }
    shiftrow(r);
  }
}

int main()
{
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      cin >> board[r][c];
    }
  }

  int dir;
  cin >> dir;

  normalize(dir);
  move();
  restore(dir);

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      cout << board[r][c] << ' ';
    }
    cout << endl;
  }

  return 0;
}
