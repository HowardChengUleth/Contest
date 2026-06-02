#include <bits/stdc++.h>

using namespace std;

int main()
{
  int h[6], h1, h2;
  for (int i = 0; i < 6; i++) {
    cin >> h[i];
  }
  cin >> h1 >> h2;
  sort(begin(h), end(h));
  
  do {
    if (is_sorted(h, h+3, greater<int>()) &&
	is_sorted(h+3, h+6, greater<int>()) &&
	accumulate(h, h+3, 0) == h1 &&
	accumulate(h+3, h+6, 0) == h2) {
      for (int i = 0; i < 6; i++) {
	cout << h[i] << ' ';
      }
      cout << endl;
      
      break;
    }
  } while (next_permutation(begin(h), end(h)));



  return 0;
}
