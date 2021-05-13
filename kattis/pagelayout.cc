#include <bits/stdc++.h>

using namespace std;

struct Rect
{
  int w, h, x, y;

  void read()
  {
    cin >> w >> h >> x >> y;
  }

  int area() const
  {
    return w*h;
  }
};

bool intersect(const Rect &R1, const Rect &R2)
{
  if (R1.x > R2.x) {
    return intersect(R2, R1);
  }
  if (R1.x + R1.w <= R2.x) {
    return false;
  }
  if (R1.y + R1.h <= R2.y || R2.y + R2.h <= R1.y) {
    return false;
  }
  return true;
}

Rect rect[20];
bool collide[20][20];

int search(bool chosen[], int index, int n)
{
  if (index == n) {
    return 0;
  }

  int S = search(chosen, index+1, n);
  bool good = true;
  for (int i = 0; i < index; i++) {
    good &= !(chosen[i] && collide[i][index]);
  }
  if (good) {
    chosen[index] = true;
    S = max(S, search(chosen, index+1, n) + rect[index].area());
    chosen[index] = false;
  }

  return S;
}

bool solve()
{
  int n;
  cin >> n;
  if (!n)
    return false;

  for (int i = 0; i < n; i++) {
    rect[i].read();
  }
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      collide[i][j] = collide[j][i] = intersect(rect[i], rect[j]);
    }
  }

  bool chosen[20] = {false};
  cout << search(chosen, 0, n) << endl;

  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
