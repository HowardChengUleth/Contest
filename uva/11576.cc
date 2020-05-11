#include <iostream>
#include <string>

using namespace std;

void solve()
{
  int k, w;
  cin >> k >> w;

  int ans = 0;
  if (w == 0) {
    cout << ans << endl;
    return;
  }

  string word;
  cin >> word;
  ans += k;
  w--;
  while (w--) {
    string next;
    cin >> next;
    
    for (int i = 0; i < k; i++) {
      if (word.find(next.substr(0, k-i), i) != string::npos) {
	break;
      }
      ans++;
    }
    word = next;
  }
  
  cout << ans << endl;
}

int main()
{
  int n;
  cin >> n;
  while (n--) 
    solve();
  return 0;
}
