#include <bits/stdc++.h>

using namespace std;

int main()
{
  int t, s, n;
  cin >> t >> s >> n;

  int top = s;
  int last;
  cin >> last;

  for (int i = 1; i < n; i++) {
    int next;
    cin >> next;

    int elapsed = next - last;
    top = max(top - elapsed, 0);
    top = s - top;
    
    last = next;
  }

  top = max(top - (t - last), 0);
  cout << top << endl;
  
  return 0;
}
