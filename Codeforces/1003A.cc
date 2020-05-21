#include <bits/stdc++.h>

using namespace std;

// the answer is just the maximum frequency of any coin

int main()
{
  int freq[101] = {0};

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    freq[a]++;
  }
  cout << *max_element(freq+1, freq+101) << endl;

  return 0;
}
