#include <iostream>

using namespace std;

struct Crane
{
  int x, y, r;

  bool hit(const Crane &c) const
  {
    return (x-c.x)*(x-c.x)+(y-c.y)*(y-c.y) <= (r+c.r)*(r+c.r);
  }
};

istream &operator>>(istream &is, Crane &c)
{
  return is >> c.x >> c.y >> c.r;
}

int max_area(Crane *crane, bool *chosen, int start, int N)
{
  if (start >= N) {
    return 0;
  }

  int ans = max_area(crane, chosen, start+1, N);
  
  for (int i = 0; i < start; i++) {
    if (chosen[i] && crane[i].hit(crane[start])) {
      return ans;
    }
  }
  chosen[start] = true;
  ans = max(crane[start].r*crane[start].r + 
	    max_area(crane, chosen, start+1, N), ans);
  chosen[start] = false;
  return ans;
}

void solve_case(void)
{
  int N;
  cin >> N;

  Crane crane[15];
  for (int i = 0; i < N; i++) {
    cin >> crane[i];
  }

  bool chosen[15];
  fill(chosen, chosen+N, false);
  cout << max_area(crane, chosen, 0, N) << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve_case();
  }
  return 0;
}
  
