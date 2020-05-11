//
// Note: for each inlet/outlet, we only have to simulate what happens for
//       twice the period.  After that history will simply repeat.  Since
//       there are multiple inlets/outlets, we need to simulate for the
//       LCM of 2* all periods.
//
//       Once we have figured out what happens for the LCM, we can skip
//       ahead quickly to the period that actually matters (if it exists).

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

long long gcd(long long a, long long b)
{
  while (b) {
    long long r = a % b;
    a = b;
    b = r;
  }
  return a;
}

long long lcm(long long a, long long b)
{
  long long g = gcd(a, b);
  return (a/g)*b;
}

long long lcm(long long A[12], long long N)
{
  long long ans = 1;
  for (int i = 0; i < N; i++) {
    ans = lcm(ans, A[i]);
  }
  return ans;
}

// LCM of 2 * {1, 2, 3, ..., 12} <= 55440
const int MAX_STEPS = 55440;

// simulate it for "steps".  period and rate are the input.  
//
// maxtotal[i] is the maximum we can get in a tank (if we start at 0)
//             in the period from the start to after step (i+1)
// mintotal[i] same except for minimum
// end[i]      what is in the tank after step (i+1)
void simulate(long long steps, long long N, const long long period[], 
	      const long long rate[], 
	      long long maxtotal[], long long mintotal[], long long end[])
{
  bool on[12];
  fill(on, on+N, true);
  
  long long counter[12];
  fill(counter, counter+12, 0);

  long long curr = 0;
  for (int i = 0; i < steps; i++) {
    long long totalrate = 0;
    for (int j = 0; j < N; j++) {
      if (on[j]) {
	totalrate += rate[j];
      }
      counter[j]++;
      if (counter[j] == period[j]) {
	counter[j] = 0;
	on[j] = !on[j];
      }
    }

    curr += totalrate;
    end[i] = curr;

    if (i == 0) {
      // I want the min/max to never go above/below 0, because the
      // capacity is 0 at the start of the period
      maxtotal[i] = max(curr, 0LL);
      mintotal[i] = min(curr, 0LL);
    } else {
      maxtotal[i] = max(maxtotal[i-1], curr);
      mintotal[i] = min(mintotal[i-1], curr);
    }
  }
}

double compute(long long target, long long startK, long long maxtotal[], 
	       long long mintotal[], 
	       long long end[], long long period_len)
{
  if (startK == target) 
    return 0;

  long long prevK = startK;
  for (int i = 0; i < period_len; i++) {
    long long newK = startK + end[i];
    long long lower = min(prevK, newK);
    long long upper = max(prevK, newK);
    if (lower <= target && target <= upper) {
      return (double)(target - prevK)/(newK - prevK) + i;
    }
    prevK = newK;
  }

  // we should never get here
}

int main(void)
{
  int N, K;
  int case_num = 1;
  while (cin >> N >> K && (N != 0 || K != 0)) {
    // read input
    long long period[12], rate[12];
    for (int i = 0; i < N; i++) {
      cin >> period[i] >> rate[i];
    }
    long long target;
    cin >> target;

    // simulate for 2*LCM steps
    long long period_len = 2*lcm(period, N);
    long long maxtotal[MAX_STEPS], mintotal[MAX_STEPS], end[MAX_STEPS];
    simulate(period_len, N, period, rate, maxtotal, mintotal, end);

    cout << "Case " << case_num++ << ": ";

    // figure out how many periods to skip
    double t;
    long long E = end[period_len-1];  // change in tank after one period
    if (E == 0) {
      // no change, so either we hit target in first period or we never hit it
      if (K + mintotal[period_len-1] <= target && 
	  target <= K + maxtotal[period_len-1]) {
	t = compute(target, K, maxtotal, mintotal, end, period_len);
      } else {
	cout << "Impossible." << endl;
	continue;
      }
    } else {
      long long upper, lower;
      if (E > 0) {
	upper = floor((double)(target - K - mintotal[period_len-1]) / E);
	lower = ceil((double)(target - K - maxtotal[period_len-1]) / E);
      } else {
	upper = floor((double)(target - K - maxtotal[period_len-1]) / E);
	lower = ceil((double)(target - K - mintotal[period_len-1]) / E);
      }
      lower = max(lower, 0LL);

      if (upper < lower) {
	cout << "Impossible." << endl;
	continue;
      } else {
	t = compute(target, K + lower * E, maxtotal, mintotal, end, period_len)
	  + lower * period_len;
      }
    }
    cout << fixed << setprecision(8) << t << endl;
  }
  return 0;
}
