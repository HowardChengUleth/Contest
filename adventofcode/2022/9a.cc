#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
set<pii> tailpos;

int dx[256], dy[256];

bool touching(pii head, pii tail)
{
  int dx = abs(head.first - tail.first);
  int dy = abs(head.second - tail.second);
  return max(dx,dy) <= 1;
}

void make_move(pii &head, pii &tail, char dir)
{
  head.first += dx[dir];
  head.second += dy[dir];

  if (touching(head, tail)) return;

  int dx2 = 0, dy2 = 0;

  if (head.first != tail.first) {
    dx2 = (head.first > tail.first) ? 1 : -1;
  }
  if (head.second != tail.second) {
    dy2 = (head.second > tail.second) ? 1 : -1;
  } 

  tail.first += dx2;
  tail.second += dy2;
  tailpos.insert(tail);
}

int main()
{
  pii head(0,0), tail(0,0);
  tailpos.insert(tail);

  dx['L'] = -1;
  dx['R'] = 1;
  dy['U'] = 1;
  dy['D'] = -1;

  char dir;
  int steps;
  while (cin >> dir >> steps) {
    for (int i = 0; i < steps; i++) {
      make_move(head, tail, dir);
    }
  }

  cout << tailpos.size() << endl;
  
  return 0;
}
