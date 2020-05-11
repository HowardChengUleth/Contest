#include <iostream>

using namespace std;

int best_factors[10];

bool better(int *f1, int *f2)
{
  int total1, total2;

  total1 = total2 = 0;
  for (int i = 0; i < 10; i++) {
    total1 += f1[i];
    total2 += f2[i];
  }
  if (total1 != total2) {
    if (total1 == 0) {
      return false;
    } else if (total2 == 0) {
      return true;
    } else {
      return total1 < total2;
    }
  }
  for (int i = 0; i < 10; i++) {
    if (f1[i] != f2[i]) {
      return f1[i] > f2[i];
    }
  }
  return false;
}

void solve(int N, int *factors, int start)
{
  if (N < 10) {
    factors[N]++;
    if (better(factors, best_factors)) {
      for (int i = 0; i < 10; i++) {
	best_factors[i] = factors[i];
      }
    }
    factors[N]--;
  }

  for (int i = start; i <= 9; i++) {
    if (N % i == 0) {
      factors[i]++;
      solve(N/i, factors, i);
      factors[i]--;
    }
  }
}



int main(void)
{
  int sets;
  int N;
  int factors[10];
  
  cin >> sets;
  while (sets-- > 0) {
    cin >> N;
    for (int i = 0; i < 10; i++) {
      best_factors[i] = factors[i] = 0;
    }
    if (N) {
      solve(N, factors, 2);
      bool printed = false;
      for (int i = 0; i < 10; i++) {
	for (int j = 0; j < best_factors[i]; j++) {
	  printed = true;
	  cout << i;
	}
      }
      if (!printed) {
	cout << -1;
      }
    } else {
      cout << "10";
    }
    cout << endl;
  }

  return 0;
}
