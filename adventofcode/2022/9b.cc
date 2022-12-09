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

void make_move(pii worm[10], char dir)
{
  worm[0].first += dx[dir];
  worm[0].second += dy[dir];

  for (int i = 0; i < 9; i++) {
    auto &head = worm[i];
    auto &tail = worm[i+1];

    if (touching(head, tail)) continue;

    int dx2 = 0, dy2 = 0;
    
    if (head.first != tail.first) {
      dx2 = (head.first > tail.first) ? 1 : -1;
    }
    if (head.second != tail.second) {
      dy2 = (head.second > tail.second) ? 1 : -1;
    } 

    tail.first += dx2;
    tail.second += dy2;
  }
  tailpos.insert(worm[9]);
}

int main()
{
  // head = 0, tail = 9
  pii worm[10];
  tailpos.insert(worm[9]);

  dx['L'] = -1;
  dx['R'] = 1;
  dy['U'] = 1;
  dy['D'] = -1;

  char dir;
  int steps;
  while (cin >> dir >> steps) {
    for (int i = 0; i < steps; i++) {
      make_move(worm, dir);
    }
  }

  cout << tailpos.size() << endl;
  
  return 0;
}
