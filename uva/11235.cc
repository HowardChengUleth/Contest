#include <iostream>
#include <cmath>
#include <utility>
#include <map>

using namespace std;

ostream &operator<<(ostream &os, const pair<int,int> &p)
{
  return os << "(" << p.first << ", " << p.second << ")";
}

bool do_case()
{
  int n, q;
  cin >> n >> q;
  if (n == 0) return false;

  int a[100000];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  int seg_size = (int)floor(sqrt(n));

  // first component is the element
  // second component is the frequency
  pair<int, int> front[320], back[320], overall[320];

  int seg_id = 0;
  for (int start = 0; start < n; start += seg_size) {
    int end = min(start + seg_size, n);

    front[seg_id] = make_pair(a[start], 1);
    for (int i = start+1; i < end && a[i] == a[start]; i++) {
      front[seg_id].second++;
    }

    back[seg_id] = make_pair(a[end-1], 1);
    for (int i = end-2; i >= start && a[i] == a[end-1]; i--) {
      back[seg_id].second++;
    }

    overall[seg_id] = make_pair(-1, 0);
    int j;
    for (int i = start; i < end; i = j) {
      for (j = i+1; j < end && a[j] == a[i]; j++)
	;
      if (j-i > overall[seg_id].second) {
	overall[seg_id] = make_pair(a[i], j-i);
      }
    }

    seg_id++;
  }

  while (q--) {
    int i, j;
    cin >> i >> j;
    i--; j--;            // 0-based

    int i_segid = i / seg_size;
    int j_segid = j / seg_size;
    int i_inner = i % seg_size;
    int j_inner = j % seg_size;

    int max_freq = 0;

    // easy case: a[i] == a[j]
    if (a[i] == a[j]) {
      cout << j-i+1 << endl;
      continue;
    }

    // easy case: in same segment
    if (i_segid == j_segid) {
      int jj;
      for (int ii = i; ii <= j; ii = jj) {
	for (jj = ii+1; jj <= j && a[jj] == a[ii]; jj++)
	  ;
	max_freq = max(max_freq, jj-ii);
      }
      cout << max_freq << endl;
      continue;
    }

    // look for the best including a[i]
    int count = 0;
    int end = min((i_segid+1) * seg_size, n);
    int it;

    for (it = i; it < end && a[it] == a[i]; it++)
      ;
    count = it - i;
    while (it < n && a[it] == a[i]) {
      it += seg_size;
    }
    it -= seg_size;
    if (it >= i) {
      count = it - i + front[it/seg_size].second;
    }
    max_freq = max(max_freq, count);

    // look for the best including a[j]
    if (a[j] != a[j_segid*seg_size] ||
	front[j_segid].second <= j_inner) {
      // just scan backwards
      for (it = j; it >= j_segid*seg_size && a[it] == a[j]; it--)
	;
      count = j - it;
    } else {
      count = j_inner+1;
      for (it = j_segid*seg_size-1; it >= 0 && a[it] == a[j]; it -= seg_size)
	;
      it += seg_size;
      if (it <= j) {
	count = j - it + back[it/seg_size].second;
      }
    }
    max_freq = max(max_freq, count);

    // look for the best in the segment of a[i]
    end = min((i_segid+1)*seg_size, n);

    int jj;
    for (it = i; it < end; it = jj) {
      for (jj = it + 1; jj < end && a[jj] == a[it]; jj++)
	;
      max_freq = max(max_freq, jj-it);
    }

    // look for the best in the segment of a[j]
    for (it = j_segid*seg_size; it <= j; it = jj) {
      for (jj = it+1; jj <= j && a[jj] == a[it]; jj++)
	;
      max_freq = max(max_freq, jj-it);
    }

    // look for the best in the middle
    for (int k = i_segid+1; k < j_segid; k++) {
      max_freq = max(max_freq, overall[k].second);
    }

    // look for ones to merge
    end = min((i_segid+1)*seg_size, n);
    pair<int,int> last(a[end-1], min(back[i_segid].second, end-i));
    max_freq = max(max_freq, last.second);
    for (int k = i_segid+1; k < j_segid; k++) {
      end = min((k+1)*seg_size, n);
      if (a[k*seg_size] == last.first) {
	last.second += front[k].second;
	max_freq = max(max_freq, last.second);
      }
      if (a[end-1] != last.first) {
	last = make_pair(a[end-1], back[k].second);
      }
    }
    if (last.first == a[j_segid*seg_size]) {
      last.second += min(front[j_segid].second, j_inner+1);
      max_freq = max(max_freq, last.second);
    }
    max_freq = max(max_freq, min(front[j_segid].second, j_inner+1));
    
    cout << max_freq << endl;
    
  }
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
