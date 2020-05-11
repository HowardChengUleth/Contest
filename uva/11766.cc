#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> Reading;

template<typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
  return os << "(" << p.first << ", " << p.second << ")";
}

bool do_case(int case_num)
{
  int N;
  cin >> N;
  if (N == 0) {
    return false;
  }

  cout << "Case " << case_num << ": ";
  Reading reading[1500];
  int n = 0;
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    if (a + b >= N) {
      // obviously invalid
      continue;
    }
    reading[n++] = make_pair(a, b);
  }
  sort(reading, reading+n);

  // make the list into triples of the form (a, b, k) where k is the
  // number of cars with the reading (a, b)
  pair<Reading, int> group[1500];
  int g_n = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0 || reading[i] != group[g_n-1].first) {
      group[g_n++] = make_pair(reading[i], 1);
    } else {
      group[g_n-1].second++;
    }
  }
  
  if (g_n == 0) {
    // no valid readings
    cout << N << endl;
    return true;
  }

  // For each triple (a, b, k), they must represent a group of N - a - b 
  // cars that are tied for positions a+1 to N-b (assuming that any one of 
  // them is correct).  Therefore, each group can have min(k, N-a-b) cars
  // that are correct at the maximum.

  // transform the first component into the positions it can represent,
  // and second component stores the maximum number of correct readings
  // in the group.
  for (int i = 0; i < g_n; i++) {
    Reading &r = group[i].first;
    int a = r.first, b = r.second;
    r.first++;
    r.second = N - r.second;
    group[i].second = min(group[i].second, N-a-b);
  }
  sort(group, group+g_n);

  // now we are going to find a non-overlapping subset of positions so
  // that the sum of min(k, N-a-b) is maximum.  We do this by dynamic
  // programming: best_sum[i] = the best way to do this with group 0..i,
  // where group[i] must be used
  
  int best_sum[1500];
  // the first one is easy, just use it
  best_sum[0] = group[0].second;
  for (int i = 1; i < g_n; i++) {
    // try using this group by itself
    best_sum[i] = group[i].second;

    // now try using this group together 
    for (int j = 0; j < i; j++) {
      if (group[j].first.second < group[i].first.first) {
	best_sum[i] = max(best_sum[i], best_sum[j] + group[i].second);
      }
    }
  }

  cout << N - *max_element(best_sum, best_sum+g_n) << endl;

  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;

  return 0;
}
