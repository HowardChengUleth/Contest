#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int digits(int n)
{
  int ans = 0;
  while (n > 0) {
    n /= 10;
    ans++;
  }
  return ans;
}

int main(void)
{
  vector<long long> chunk_len;
  vector<long long> total;
  
  chunk_len.push_back(0);
  total.push_back(0);
  for (int n = 1; total[n-1] <= INT_MAX; n++) {
    chunk_len.push_back(chunk_len[n-1] + digits(n));
    total.push_back(total[n-1] + chunk_len[n]);
  }
  
  int t;
  cin >> t;
  while (t-- > 0) {
    int i;
    cin >> i;

    int chunk;
    for (chunk = 0; total[chunk] < i; chunk++)
      ;
    int to_go = i - total[chunk-1];
    if (to_go <= 1*9) {
      cout << to_go << endl;
      continue;
    }
    to_go -= 1*9;
    if (to_go <= 2*(99-9)) {
      int v = (to_go-1)/2 + 10;
      cout << ((to_go % 2) ? v/10 : v%10) << endl;
      continue;
    }
    to_go -= 2*(99-9);
    if (to_go <= 3*(999-99)) {
      int v = (to_go-1)/3 + 100;
      if (to_go % 3 == 1) {
	cout << v/100 << endl;
      } else if (to_go % 3 == 2) {
	cout << (v/10) % 10 << endl;
      } else {
	cout << v%10 << endl;
      }
      continue;
    }
    to_go -= 3*(999-99);
    if (to_go <= 4*(9999-999)) {
      int v = (to_go-1)/4 + 1000;
      if (to_go % 4 == 1) {
	cout << v/1000 << endl;
      } else if (to_go % 4 == 2) {
	cout << (v/100) % 10 << endl;
      } else if (to_go % 4 == 3) {
	cout << (v/10) % 10 << endl;
      } else {
	cout << v%10 << endl;
      }
      continue;
    }
    to_go -= 4*(9999-999);
    int v = (to_go-1)/5 + 10000;
    if (to_go % 5 == 1) {
      cout << v/10000 << endl;
    } else if (to_go % 5 == 2) {
      cout << (v/1000) % 10 << endl;
    } else if (to_go % 5 == 3) {
      cout << (v/100) % 10 << endl;
    } else if (to_go % 5 == 4) {
      cout << (v/10) % 10 << endl;
    } else {
      cout << v%10 << endl;
    }
    
  }

  return 0;
}
