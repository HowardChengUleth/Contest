// This problem can be solved by a greedy algorithm: always choosing
// the longest segment that has some character in common.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int longest_segment(const string strand[], int start, int n)
{
  bool mask[26];  // which of the 26 letters are present
  fill(mask, mask+26, true);
  int mask_count = 26;  // how many are present

  int len = 0;
  while (start+len < n && mask_count > 0) {
    bool newmask[26];
    fill(newmask, newmask+26, false);
    for (unsigned int i = 0; i < strand[start+len].length(); i++) {
      newmask[strand[start+len][i]-'a'] = true;
    }
    for (int i = 0; i < 26; i++) {
      if (mask[i] && !newmask[i]) {
	mask[i] = false;
	mask_count--;
      }
    }
    if (mask_count > 0) {
      len++;
    }
  }

  return len;
}

void solve_case(void)
{
  int n;
  cin >> n;

  string strand[10000];
  for (int i = 0; i < n; i++) {
    cin >> strand[i];
  }

  int segments = 0;
  int start = 0;
  while (start < n) {
    int len = longest_segment(strand, start, n);
    start += len;
    segments++;
  }
  cout << segments-1 << endl;
}

int main(void)
{
  int t;
  cin >> t;
  while (t-- > 0) {
    solve_case();
  }
  return 0;
}
