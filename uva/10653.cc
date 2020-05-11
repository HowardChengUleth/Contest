/* @JUDGE_ID: 1102NT 10653 C++ "" */

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

const int NOT_REACHED = -1;
const int BLOCKED = -2;

int board[1000][1000];
int R, C;

struct Point {
  int r, c;
  Point(int rr = 0, int cc = 0) { r = rr; c = cc; }
};

istream &operator>>(istream &is, Point &p)
{
  return (is >> p.r >> p.c);
}

void clear_board(void)
{
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      board[i][j] = NOT_REACHED;
    }
  }
}

void bfs(Point start, Point dest)
{
  queue<Point> q;
  board[start.r][start.c] = 0;
  
  q.push(start);
  while (board[dest.r][dest.c] < 0) {
    assert(q.size() > 0);
    Point p = q.front(), p2;
    q.pop();

    int d = board[p.r][p.c];

    if (p.r > 0 && board[p.r-1][p.c] == NOT_REACHED) {
      board[p.r-1][p.c] = d+1;
      p2 = p; p2.r--;
      q.push(p2);
    }
    if (p.r < R-1 && board[p.r+1][p.c] == NOT_REACHED) {
      board[p.r+1][p.c] = d+1;
      p2 = p; p2.r++;
      q.push(p2);
    }
    if (p.c > 0 && board[p.r][p.c-1] == NOT_REACHED) {
      board[p.r][p.c-1] = d+1;
      p2 = p; p2.c--;
      q.push(p2);
    }
    if (p.c < C-1 && board[p.r][p.c+1] == NOT_REACHED) {
      board[p.r][p.c+1] = d+1;
      p2 = p; p2.c++;
      q.push(p2);
    }
  }
}

int main(void)
{
  
  while (cin >> R >> C && R > 0 && C > 0) {
    clear_board();
    int nrows;
    cin >> nrows;
    while (nrows -- > 0) {
      int r, nc, c;
      cin >> r >> nc;
      while (nc -- > 0) {
	cin >> c;
      }
      board[r][c] = BLOCKED;
    }
    
    Point start, dest;
    
    cin >> start >> dest;

    bfs(start, dest);
    cout << board[dest.r][dest.c] << endl;

  }
  return 0;
}
