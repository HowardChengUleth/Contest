#include <bits/stdc++.h>

using namespace std;

// the idea is that you need an alternating 0 and 1 to get the
// transitions required.  Any additional 0s and 1s can just be inserted
// into some "chunks"
//
// if there is an odd number of transitions, the number of 0s and 1s chunks
// are the same.
//
// if there is an even number of transitions, the number of 0s and 1s chunks
// is different by 1, so we start with whichever number is more

int main()
{
  int a, b, x;
  cin >> a >> b >> x;

  if (x % 2) {
    // just print 010101...
    while (x > 1) {
      cout << "01";
      a--;
      b--;
      x -= 2;
    }
    cout << string(a, '0') << string(b, '1') << endl;
  } else {
    // I am making it so that there are always more 0s than 1s (or equal),
    // and flipping the result if needed
    bool flip = (b > a);
    if (flip) {
      swap(a,b);
    }

    string ans = "010";
    x -= 2;
    a -= 2;
    b--;
    
    while (x > 0) {
      ans += "10";
      x -= 2;
      a--;
      b--;
    }

    ans.insert(1, string(b, '1'));
    ans += string(a, '0');
    if (flip) {
      for (auto &c : ans) {
	c = (c =='0') ? '1' : '0';
      }
    }
    cout << ans << endl;
  }

  

  return 0;
}
