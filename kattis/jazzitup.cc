#include <bits/stdc++.h>

using namespace std;

const int MAX = 100000;
bool isprime[MAX+1];
vector<int> primes;

void genprimes()
{
  isprime[0] = isprime[1] = false;
  fill(isprime+2, isprime+MAX+1, true);

  for (int i = 2; i <= MAX; i++) {
    if (!isprime[i]) {
      continue;
    }
    primes.push_back(i);
    for (long long k = (long long)i*i; k <= MAX; k += i) {
      isprime[k] = false;
    }
  }
}

int main()
{
  genprimes();

  int n;
  cin >> n;

  int i;
  for (i = 0; n % primes[i] == 0; i++)
    ;

  cout << primes[i] << endl;
  return 0;
}
