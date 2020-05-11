// A006534 in The On-Line Encyclopedia of Integer Sequences
#include <iostream>

using namespace std;

int ans[17] = {0, 1, 1, 1, 4, 6, 19, 43, 120, 307, 866, 2336, 
               6588, 18373, 52119, 147700, 422016};

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    int N;
    cin >> N;
    cout << "Case #" << i << ": " << ans[N] << endl;
  }
  return 0;
}
