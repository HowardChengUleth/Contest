#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Pos {
  int row, col;
  
  Pos() {}

  Pos(const string &s)
  {
    row = s[0] - 'a';
    col = s[1] - '1';
  }

  bool inside() const
  {
    return 0 <= row && row < 8 && 0 <= col && col < 8;
  }

  bool operator==(const Pos &p) const
  {
    return row == p.row && col == p.col;
  }
};

int dist(const string &start, const string &end)
{
  Pos s_pos(start), e_pos(end);
  int board[8][8];

  int dr[8] = {-1, -1, -2, -2, 1,  1, 2,  2};
  int dc[8] = { 2, -2,  1, -1, 2, -2, 1, -1};

  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      board[r][c] = -1;
    }
  }

  queue<Pos> q;

  board[s_pos.row][s_pos.col] = 0;
  q.push(s_pos);
  while (!q.empty()) {
    s_pos = q.front();
    q.pop();
    if (s_pos == e_pos) break;
    for (int i = 0; i < 8; i++) {
      Pos next_pos;
      next_pos.row = s_pos.row + dr[i];
      next_pos.col = s_pos.col + dc[i];
      if (!next_pos.inside()) continue;
      if (board[next_pos.row][next_pos.col] != -1) continue;
      board[next_pos.row][next_pos.col] = board[s_pos.row][s_pos.col] + 1;
      q.push(next_pos);
    }
  }

  return board[e_pos.row][e_pos.col];
}


int main(void)
{
  string start, end;

  while (cin >> start >> end) {
    cout << "To get from " << start << " to " << end << " takes "
	 << dist(start, end) << " knight moves." << endl;
  }

  return 0;
}
