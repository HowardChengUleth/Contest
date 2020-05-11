#include <iostream>

using namespace std;

//  1 => x wins
// -1 => o wins
//  0 => tie

int result(char board[4][4])
{
  int xcount, ocount;

  for (int i = 0; i < 4; i++) {
    xcount = ocount = 0;
    for (int j = 0; j < 4; j++) {
      switch (board[i][j]) {
      case 'x':
	xcount++;
	break;
      case 'o':
	ocount++;
	break;
      }
    }
    if (xcount == 4) {
      return 1;
    } else if (ocount == 4) {
      return -1;
    }
  }

  for (int j = 0; j < 4; j++) {
    xcount = ocount = 0;
    for (int i = 0; i < 4; i++) {
      switch (board[i][j]) {
      case 'x':
	xcount++;
	break;
      case 'o':
	ocount++;
	break;
      }
    }
    if (xcount == 4) {
      return 1;
    } else if (ocount == 4) {
      return -1;
    }
  }
						\
  xcount = ocount = 0;
  for (int i = 0; i < 4; i++) {
    switch (board[i][i]) {
    case 'x':
      xcount++;
      break;
    case 'o':
      ocount++;
      break;
    }
  }
  if (xcount == 4) {
    return 1;
  } else if (ocount == 4) {
    return -1;
  }

  xcount = ocount = 0;
  for (int i = 0; i < 4; i++) {
    switch (board[i][3-i]) {
    case 'x':
      xcount++;
      break;
    case 'o':
      ocount++;
      break;
    }
  }
  if (xcount == 4) {
    return 1;
  } else if (ocount == 4) {
    return -1;
  } else {
    return 0;
  }
}

int bestmoveo(char board[4][4], int alpha, int beta, int left);

int bestmovex(char board[4][4], int &best_r, int &best_c, int alpha, int beta,
	      int left)
{
  int r = result(board);
  if (r != 0 || left == 0) return r;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] != '.') continue;
      board[i][j] = 'x';
      int r2 = bestmoveo(board, alpha, beta, left-1);
      board[i][j] = '.';

      if (r2 > alpha) {
	best_r = i; best_c = j;
	alpha = r2;
      }
      if (alpha >= beta) {
	return alpha;
      }
    }
  }

  return alpha;
}

int bestmoveo(char board[4][4], int alpha, int beta, int left)
{
  int r = result(board);
  if (r != 0 || left == 0) return r;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] != '.') continue;
      board[i][j] = 'o';
      int dr, dc;
      int r2 = bestmovex(board, dr, dc, alpha, beta, left-1);
      board[i][j] = '.';

      if (r2 < beta) {
	beta = r2;
      }
      if (alpha >= beta) {
	return beta;
      }
    }
  }

  return beta;
}

bool solve()
{
  char ch;
  cin >> ch;
  if (ch == '$') return false;

  int left = 16;
  char board[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cin >> board[i][j];
      if (board[i][j] != '.') left--;
    }
  }

  int best_r, best_c;
  int r = bestmovex(board, best_r, best_c, -1, 1, left);
  if (r != 1) {
    cout << "#####" << endl;
  } else {
    cout << "(" << best_r << "," << best_c << ")" << endl;
  }

  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
