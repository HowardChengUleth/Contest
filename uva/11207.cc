#include <iostream>
#include <algorithm>

using namespace std;

int len(int a, int b)
{
  if (a > b) return len(b, a);

  a *= 4;
  b *= 4;
  int ans = a/2;
  if (b >= 4*a) {
    ans = max(ans, a);
  } else {
    ans = max(ans, b/4);
  }
  return ans;
}

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  int a, b;
  cin >> a >> b;
  int best_len = len(a, b);
  int best_index = 1;

  //  cout << "1: " << best_len << endl;
  
  for (int i = 2; i <= n; i++) {
    cin >> a >> b;
    int t = len(a, b);
    if (t > best_len) {
      best_index = i;
      best_len = t;
    }
    //    cout << i << ": " << t << endl;
  }
  cout << best_index << endl;
  
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
