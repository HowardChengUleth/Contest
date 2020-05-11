#include <iostream>
#include <cctype>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

map<int, int> fibindex;

void solve()
{
  char buffer[1000];
  fill(buffer, buffer+1000, ' ');

  int N;
  cin >> N;

  int fib[1000];
  for (int i = 0; i < N; i++) {
    cin >> fib[i];
  }
  cin.ignore(1);

  string line;
  getline(cin, line);
  int k = 0;
  for (int i = 0; i < line.length() && k < N; i++) {
    if (!isupper(line[i])) continue;
    buffer[fibindex[fib[k++]]] = line[i];
  }

  for (int i = 999; i >= 0; i--) {
    if (buffer[i] == ' ') {
      buffer[i] = 0;
    } else {
      break;
    }
  }

  cout << buffer << endl;
}

int main(void)
{
  fibindex[1] = 0;
  fibindex[2] = 1;

  int pos = 2;
  int prev1 = 2;
  int prev2 = 1;
  for (int i = 0; (long long)prev1 + prev2 < (1ULL << 31); i++) {
    int curr = prev1 + prev2;
    fibindex[curr] = pos++;
    prev2 = prev1;
    prev1 = curr;
  }
  
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
