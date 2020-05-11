#include <iostream>
#include <string>

using namespace std;

bool isprime(int n)
{
  if (n > 2 && n % 2 == 0) {
    return false;
  }

  for (int d = 3; d*d <= n; d += 2) {
    if (n % d == 0) return false;
  }
  return true;
}

int main(void)
{
  int primes[1000];
  int num_primes = 0;

  for (int n = 2; n <= 1000; n++) {
    if (isprime(n)) {
      primes[num_primes++] = n;
    }
  }

  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cout << "Case " << i << ": ";
    int n, k;
    string s;
    cin >> n >> s;
    k = s.length();

    unsigned long long ans = 1;
    bool over = false;
    for (int t = 0; t < num_primes; t++) {
      int p = primes[t];
      if (p > n) break;
      int count = 0;
      for (int m = n % k; m <= n; m += k) {
	if (m == 0) continue;
	//	cout << "=> " << m << endl;
	int x = m;
	while (x % p == 0) {
	  x /= p;
	  count++;
	}
      }

      if (ans <= 1000000000000000000LL / (count+1)) {
	ans *= (count+1);
      } else {
	over = true;
	break;
      }
    }
    if (over) {
      cout << "Infinity" << endl;
    } else {
      cout << ans << endl;
    }
  }
  
  return 0;
}
