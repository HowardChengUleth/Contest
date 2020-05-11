//
// We just check the rules.  For rule 2, it is equivalent to make sure
// that every grid point has degree 0 or 2, and that all the edges are
// connected in one component.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

void DFS(int r, int c, int R, int C, string board[101], bool visited[101][101])
{
  int offset_rv[6] = { -2, -1, -1, 1, 1, 2 },
    offset_cv[6] = { 0, -1, 1, -1, 1, 0 };

  visited[r][c] = true;

  if (board[r][c] == '|') {
    for (int i = 0; i < 6; i++) {
      int nr = r + offset_rv[i];
      int nc = c + offset_cv[i];
      if (0 <= nr && nr < R && 0 <= nc && nc < C &&
	  board[nr][nc] != ' ' && !visited[nr][nc]) {
	DFS(nr, nc, R, C, board, visited);
      }
    }
  } else {
    assert(board[r][c] == '-');
    for (int i = 0; i < 6; i++) {
      int nr = r + offset_cv[i];
      int nc = c + offset_rv[i];
      if (0 <= nr && nr < R && 0 <= nc && nc < C &&
	  board[nr][nc] != ' ' && !visited[nr][nc]) {
	DFS(nr, nc, R, C, board, visited);
      }
    }
  }
}

bool solve_case(void)
{
  int R, C;

  cin >> R >> C;
  cin.ignore();

  string board[101];
  for (int r = 0; r < 2*R+1; r++) {
    getline(cin, board[r]);
  }

  // check rule 1
  for (int r = 1; r < 2*R+1; r += 2) {
    for (int c = 1; c < 2*C+1; c += 2) {
      if (board[r][c] == ' ') continue;
      int k = board[r][c] - '0';
      if (board[r-1][c] != ' ') k--;
      if (board[r+1][c] != ' ') k--;
      if (board[r][c-1] != ' ') k--;
      if (board[r][c+1] != ' ') k--;
      if (k) {
	return false;
      }
    }
  }

  // check rule 2a): it doesn't cross itself, so every vertex has degree 2
  for (int r = 0; r < 2*R+1; r += 2) {
    for (int c = 0; c < 2*C+1; c += 2) {
      int deg = 0;
      if (r > 0 && board[r-1][c] != ' ') deg++;
      if (r < 2*R && board[r+1][c] != ' ') deg++;
      if (c > 0 && board[r][c-1] != ' ') deg++;
      if (c < 2*C && board[r][c+1] != ' ') deg++;
      if (deg != 2 && deg != 0) {
	return false;
      }
    }
  }

  // check rule 2b): it forms a loop
  bool visited[101][101];
  for (int r = 0; r < 2*R+1; r++) {
    fill(visited[r], visited[r]+2*C+1, false);
  }
      
  for (int r = 0; r < 2*R+1; r++) {
    for (int c = 0; c < 2*C+1; c++) {
      if (r % 2 == c % 2) continue;
      if (board[r][c] == ' ') continue;
      DFS(r, c, 2*R+1, 2*C+1, board, visited);
      break;
    }
  }

  for (int r = 0; r < 2*R+1; r++) {
    for (int c = 0; c < 2*C+1; c++) {
      if (r % 2 == c % 2) continue;
      if (board[r][c] == ' ') continue;
      if (!visited[r][c]) {
	return false;
      }
    }
  }

  return true;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    cout << (solve_case() ? "Valid" : "Invalid") << endl;
  }
  return 0;
}
