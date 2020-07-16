#include <iostream>
#include <string>
#include <algorithm>

// Instead of doing any reversing, just keep track of the current start and
// end of the list, and which way we are looking

using namespace std;

int A[100000];

void solve()
{
  string s;
  cin >> s;

  int n;
  cin >> n;
  
  char c;
  cin >> c;
  for (int i = 0; i < n; i++) {
    if (i) cin >> c;
    cin >> A[i];
  }
  cin >> c;

  int start = 0, end = n-1, dir = 1;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == 'R') {
      dir *= -1;
      swap(start, end);
    } else {
      int size = 1 + ((dir > 0) ? (end - start) : (start - end));
      if (size == 0) {
	cout << "error" << endl;
	return;
      }

      start += dir;
    }
  }

  cout << "[";
  for (int i = start; i != end + dir; i += dir) {
    if (i != start) cout << ',';
    cout << A[i];
  }
  cout << "]" << endl;

}

int main()
{
  int n;
  cin >> n;
  while (n--)
    solve();
  return 0;
}
