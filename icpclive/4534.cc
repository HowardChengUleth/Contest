#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <cmath>

using namespace std;

double known_prob[5], unknown_prob[5];
int n;

double calc_prob(bool rem[], int rem_size, 
		 int known_left[], int unknown_left[]);

double round(double x)
{
  return floor(x * 1000 + 0.5) / 1000;
}

double get_known_prob(int i, int known_left[], int unknown_left[])
{
  double total_prob = known_prob[i] * known_left[i] +
    unknown_prob[i] * unknown_left[i];
  if (known_left[i] > 0) {
    return known_prob[i] / total_prob;
  } else {
    return 0;
  }
}

double get_unknown_prob(int i, int known_left[], int unknown_left[])
{
  double total_prob = known_prob[i] * known_left[i] +
    unknown_prob[i] * unknown_left[i];
  if (unknown_left[i] > 0) {
    return unknown_prob[i] / total_prob;
  } else {
    return 0;
  }
}


double make_guess(bool rem[], int rem_size, 
		  int known_left[], int unknown_left[], bool guess[])
{
  double ans = 0;
  int kl[5], ul[5];

  copy(known_left, known_left+n, kl);
  copy(unknown_left, unknown_left+n, ul);

  for (int i = 0; i < n; i++) {
    if (!rem[i]) continue;
    if (guess[i]) {
      kl[i]--;
    } else {
      ul[i]--;
    }
  }

  // try all possible way of getting at least 1 guess correct
  for (int subset = 1; subset < (1 << rem_size); subset++) {
    bool correct[5];
    int s = subset;

    // the probability that this happens
    double p = 1;

    for (int i = 0; i < n; i++) {
      if (!rem[i]) continue;
      correct[i] = s & 1;
      s >>= 1;
      if (guess[i]) {
	if (correct[i]) {
	  p *= get_known_prob(i, known_left, unknown_left);
	} else {
	  p *= 1 - get_known_prob(i, known_left, unknown_left);
	}
      } else {
	if (correct[i]) {
	  p *= get_unknown_prob(i, known_left, unknown_left);
	} else {
	  p *= 1 - get_unknown_prob(i, known_left, unknown_left);
	}
      }
    }

    // now recurse
    bool newrem[5];
    int newremsize = 0;
    for (int i = 0; i < n; i++) {
      newremsize += (newrem[i] = rem[i] && !correct[i]);
    }
    
    assert(rem_size > newremsize);
    ans += p * calc_prob(newrem, newremsize, kl, ul);
  }

  return ans;
}

double calc_prob(bool rem[], int rem_size, 
		 int known_left[], int unknown_left[])
{
  // base case
  if (rem_size == 0) {
    return 1;
  }
  if (rem_size == 1) {
    int i = 0;
    while (!rem[i]) {
      i++;
    }
    if (known_left[i] + unknown_left[i] == 0) {
      return 0;
    }

    return max(get_known_prob(i, known_left, unknown_left),
	       get_unknown_prob(i, known_left, unknown_left));
  }

  // not base case, try all possible guesses
  double ans = 0;
  for (int g = 0; g < (1 << rem_size); g++) {
    bool guess[5];
    bool good = true;
    int gg = g;
    for (int i = 0; i < n; i++) {
      if (!rem[i]) continue;
      if ((guess[i] = gg & 1)) {
	good &= (known_left[i] > 0);
      } else {
	good &= (unknown_left[i] > 0);
      }
      gg >>= 1;
    }
    if (good) {
      ans = max(ans, 
		make_guess(rem, rem_size, known_left, unknown_left, guess));
    }
  }
  
  return ans;
}

bool do_case(void)
{
  cin >> n;
  if (n == 0) {
    return false;
  }

  int known_left[5], unknown_left[5];

  for (int i = 0; i < n; i++) {
    int m, l;
    double p;
    cin >> m >> l >> p;
    known_left[i] = l;
    unknown_left[i] = m-l;
    known_prob[i] = (known_left[i]) ? p / known_left[i] : 0.0;
    unknown_prob[i] = (unknown_left[i]) ? (1 - p) / unknown_left[i] : 0.0;
  }

  bool rem[5];
  fill(rem, rem+n, true);
  double ans = calc_prob(rem, n, known_left, unknown_left);
  ans = round(ans);
  cout << setprecision(3) << ans << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
