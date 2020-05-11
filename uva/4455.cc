#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;

// First, let G_1 be the graph whose vertices are all suffixes of length 1
// appearing in S, T, and any of the rules (both LHS and RHS).  There is
// a directed edge of weight 1 if there is a rule (of length 1) that takes
// that one suffix to the next.  Compute all-pairs shortest distances.
// Note that the number of vertices here is not large (at most 2NR+2) so even
// Floyd's algorithm would do.
//
// Now we construct G_2 with vertices being all relevant suffixes of length
// 2 (again, there are not many).  Ignore any suffix from rules of length 1.
// The edge weights are now 1 if there is a rule (of length 2) that takes one
// suffix to the next.  Also, if the first letters two suffices are the same,
// then the edge weight between the two vertices is the distance of that pair
// in G_1.  Compute all-pairs shortest distances, and now you know the best
// way to transform suffixes of length 2.
//
// Repeat for G_k for increasing k until you have the length of the string.
// You will have to take care of the impossible case, of course. 

void add_suffix(map<string, int> &suffix_index, 
		string suffix[202], const string &s, unsigned int len)
{
  if (s.length() < len) {
    return;
  }
  string t = s.substr(s.length()-len, len);
  if (suffix_index.find(t) == suffix_index.end()) {
    int index = suffix_index.size();
    suffix_index[t] = index;
    suffix[index] = t;
  }
}

void add_suffixes(map<string, int> &suffix_index, string suffix[202],
		  int NR, const pair<string, string> rule[100], 
		  const string &S, const string &T,
		  unsigned int len)
{
  suffix_index.clear();
  for (int i = 0; i < NR; i++) {
    add_suffix(suffix_index, suffix, rule[i].first, len);
    add_suffix(suffix_index, suffix, rule[i].second, len);
  }
  add_suffix(suffix_index, suffix, S, len);
  add_suffix(suffix_index, suffix, T, len);
}

void floyd(long long D[202][202], int n)
{
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (D[i][k] < 0) continue;
      for (int j = 0; j < n; j++) {
	if (D[k][j] < 0) continue;
	long long d = D[i][k] + D[k][j];
	if (D[i][j] < 0 || d < D[i][j]) {
	  D[i][j] = d;
	}
      }
    }
  }
}

void form_graph(long long D[2][202][202], int curr, int NR, 
		const pair<string, string> rule[100],
		map<string, int> suffix_index[2],
		const string suffix[2][202],
		unsigned int len)
{
  int n = suffix_index[curr].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      D[curr][i][j] = -1;
    }
    D[curr][i][i] = 0;
  }
  for (int i = 0; i < NR; i++) {
    if (rule[i].first.length() != len) continue;
    int from = suffix_index[curr][rule[i].first];
    int to = suffix_index[curr][rule[i].second];
    D[curr][from][to] = 1;
  }
  if (len > 1) {
    for (int i = 0; i < n; i++) {
      const string &from = suffix[curr][i];
      for (int j = 0; j < n; j++) {
	const string &to = suffix[curr][j];
	if (from[0] != to[0]) continue;
	if (D[curr][i][j] >= 0) continue;

	int prev = 1-curr;
	int prev_from = suffix_index[prev][from.substr(1, len-1)];
	int prev_to = suffix_index[prev][to.substr(1, len-1)];
	D[curr][i][j] = D[prev][prev_from][prev_to];
      }
    }
  }
}

void solve(const string &S, const string &T, int NR, 
	   const pair<string, string> rule[100])
{
  long long D[2][202][202];
  map<string, int> suffix_index[2];
  string suffix[2][202];   // reverse mapping

  int curr = 0;
  for (unsigned int len = 1; len <= S.length(); len++) {
    add_suffixes(suffix_index[curr], suffix[curr], NR, rule, S, T, len);
    form_graph(D, curr, NR, rule, suffix_index, suffix, len);
    floyd(D[curr], suffix_index[curr].size());
    curr = 1-curr;
  }

  curr = 1-curr;   // move back to the previous step
  long long d = D[curr][suffix_index[curr][S]][suffix_index[curr][T]];
  if (d < 0) {
    cout << "No solution" << endl;
  } else {
    cout << d << endl;
  }
}

int main(void)
{
  string S, T;
  int NR;
  int case_num = 1;
  pair<string, string> rule[100];
  
  while (cin >> S >> T >> NR && S.find('.') == string::npos) {
    cout << "Case " << case_num++ << ": ";
    for (int i = 0; i < NR; i++) {
      cin >> rule[i].first >> rule[i].second;
    }
    solve(S, T, NR, rule);
  }

  return 0;
}
