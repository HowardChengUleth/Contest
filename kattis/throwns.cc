#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, k;
  cin >> n >> k;

  stack<int> pos;
  int curr = 0;
  pos.push(curr);
  for (int i = 0; i < k; i++) {
    string undo;
    int arg;
    if (cin >> arg) {
      curr = (curr + arg) % n;
      if (curr < 0) curr += n;
      pos.push(curr);
    } else {
      cin.clear();
      cin >> undo >> arg;
      while (arg--) {
	pos.pop();
	curr = pos.top();
      }
    }
  }
  cout << pos.top() << endl;
  
  return 0;
}
