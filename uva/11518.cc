#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void knock(vector<int> push[], bool fallen[], int z)
{
  if (fallen[z]) {
    return;
  }
  fallen[z] = true;
  for (vector<int>::iterator it = push[z].begin(); it != push[z].end(); ++it) {
    knock(push, fallen, *it);
  }
}

void solve_case(void)
{
  int n, m, l;
  cin >> n >> m >> l;

  vector<int> push[10001];
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    push[x].push_back(y);
  }
  
  bool fallen[10001];
  fill(fallen+1, fallen+n+1, false);

  for (int i = 0; i < l; i++) {
    int z;
    cin >> z;
    knock(push, fallen, z);
  }

  int count = 0;
  for (int i = 1; i <= n; i++) {
    if (fallen[i]) {
      count++;
    }
  }
  cout << count << endl;

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
