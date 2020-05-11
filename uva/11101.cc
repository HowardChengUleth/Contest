#include <iostream>

using namespace std;

struct Node {
  short dist;
  short x, y;

  Node() { };
  Node(int d, short xx, short yy) : dist(d), x(xx), y(yy) { };
};

char visited[2001][2001];
Node q[2001*2001+1];
short dx[4] = {-1,1,0,0};
short dy[4] = {0,0,1,-1};

int main(void)
{
  int n;
  short d, x, y;
  
  while (cin >> n && n) {
    for (int i = 0; i <= 2000; i++) {
      for (int j = 0; j <= 2000; j++) {
	visited[i][j] = 0;
      }
    }

    int head = 0, tail = 0;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      q[tail++] = Node(0, x, y);
      visited[x][y] = 1;
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      visited[x][y] = 2;
    }

    int done = 0;
    while (head < tail && !done) {
      d = q[head].dist;
      x = q[head].x;
      y = q[head++].y;

      for (int i = 0; i < 4 && !done; i++) {
	short nx = x+dx[i], ny = y+dy[i];
	if (0 <= nx && nx <= 2000 && 0 <= ny && ny <= 2000) {
	  if (visited[nx][ny] == 2) {
	    cout << d+1 << endl;
	    done = 1;
	  } else if (!visited[nx][ny]) {
	    visited[nx][ny] = 1;
	    q[tail++] = Node(d+1, nx, ny);
	  }
	}
      }
    }
  }
  return 0;
}
