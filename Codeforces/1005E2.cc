#include <bits/stdc++.h>

using namespace std;

// We could start with the same idea as E1, but we will quickly realize
// that it does not work.
//
// The conditions we have before was U-L = 0 or 1.  But the problem now is
// that there can be multiple values of m, so it is harder to make sure
// that you choose two end points enclosing at least 1 m, and if there are
// multiple m's in the range then the conditions need to be modified.
//
// But we can modify the idea slightly and see what we get.  If instead
// of just our definitions of U and L being number of elements > and < m,
// We also have M = number of elements == m in an interval.
//
// Then M is the median in this range of L+M+U elements iff
//      L+M >= U        (median is at most m)
// and  U+M > L         (median is at least m)
//
// or   0 < U-L+M <= 2*M
//
// It turns out that it is too hard to keep track of the inequality
// when both sides have variables, so we will only look at U-L+M > 0.
// This will tell us only the number of intervals whose median is at
// least m.  Call this f(m).  If we do this again for f(m+1), the
// answer we want is f(m) - f(m+1).
//
// For f(m) we use a diff array that keeps a partial sum of U-L+M values.
//
// For each diff[i], we want to know how many j < i such that
// 0 < diff[i]-diff[j] (and count 1 more if 0 < diff[i]).
//
// When we see diff[i], we want to know how many j < i such that
// diff[j] < diff[i].  Note that -n <= diff[i] <= n, so we can easily
// use an array freq indexed by the values of diff to see how often each
// value occurs.  If we compute the partial sums of freq, we can easily
// determine the number of values of diff less than a certain value.
// Because we will be updating diff and freq and partial sums as we scan
// from left to right, we will use a fenwick tree to represent freq
// its partial sums.

/*
 * Fenwick Tree
 *
 * Author: Howard Cheng
 * Reference:
 *
 *   Fenwick, P.M. "A New Data Structure for Cumulative Frequency Tables."
 *   Software---Practice and Experience, 24(3), 327-336 (March 1994).
 *
 * This code has been tested on UVa 11525 and 11610.
 *
 * Fenwick trees are data structures that allows the maintainence of
 * cumulative sum tables dynamically.  The following operations
 * are supported:
 *
 * - Initialize the tree from a list of N integers:                 O(N log N)
 *
 * - Read the cumulative sum at index 0 <= k < N:                   O(log k)
 *
 * - Read the entry at index 0 <= k < N:                            O(log N)
 *
 * - Increment/decrement an entry at index 0 <= k < N in the list:  O(log N)
 *
 * - Given a value, find an index such that the cumulative sum at
 *   that position is the value:                                    O(log N)
 *
 * The space usage is at most 2*N for N input entries.
 *
 * NOTE: it is assumed that all entries are non-negative (even after a
 *       decrement operation).
 *
 */

#include <vector>
#include <cassert>

using namespace std;

class FenwickTree
{
public:
  FenwickTree(int n = 0)
    : N(n), tree(n)
  {
    iBM = 1;
    while (iBM < N) {
      iBM *= 2;
    }
    tree.resize(iBM+1);
    fill(tree.begin(), tree.end(), 0);
  }

  // initialize the tree with the given array of values
  FenwickTree(int val[], int n)
    : N(n)
  {
    iBM = 1;
    while (iBM < N) {
      iBM *= 2;
    }
    
    tree.resize(iBM+1);
    fill(tree.begin(), tree.end(), 0);
    for (int i = 0; i < n; i++) {
      assert(val[i] >= 0);
      incEntry(i, val[i]);
    }
  }

  // increment the entry at position idx by val (use negative val for
  // decrement).  All affected cumulative sums are updated.
  void incEntry(int idx, int val)
  {
    assert(0 <= idx && idx < N);
    if (idx == 0) {
      tree[idx] += val;
    } else {
      do {
	tree[idx] += val;
	idx += idx & (-idx);
      } while (idx < (int)tree.size());
    }
  }

  // return the cumulative sum val[0] + val[1] + ... + val[idx]
  int cumulativeSum(int idx) const
  {
    assert(0 <= idx && idx < (int)tree.size());
    int sum = tree[0];
    while (idx > 0) {
      sum += tree[idx];
      idx &= idx-1;
    }
    return sum;
  }

  // return the entry indexed by idx
  int getEntry(int idx) const
  {
    assert(0 <= idx && idx < N);
    int val, parent;
    val = tree[idx];
    if (idx > 0) {
      parent = idx & (idx-1);
      idx--;
      while (parent != idx) {
	val -= tree[idx];
	idx &= idx-1;
      }
    }
    return val;
  }

  // return the largest index such that the cumulative frequency is
  // what is given, or -1 if it is not found
  //
  int getIndex(int sum) const
  {
    int orig = sum;
    if (sum < tree[0]) return -1;
    sum -= tree[0];
    
    int idx = 0;
    int bitmask = iBM;

    while (bitmask != 0 && idx < (int)tree.size()-1) {
      int tIdx = idx + bitmask;
      if (sum >= tree[tIdx]) {
	idx = tIdx;
	sum -= tree[tIdx];
      }
      bitmask >>= 1;
    }

    if (sum != 0) {
      return -1;
    }

    idx = min(N-1, idx);
    return (cumulativeSum(idx) == orig) ? idx : -1;
  }
  
private:
  int N, iBM;
  vector<int> tree;
};


int n;
int a[200000];
long long f(int m)
{
  int diff[200000];
  FenwickTree ft(2*n+1);
  long long ans = 0;
  
  for (int i = 0; i < n; i++) {
    int last = (i == 0) ? 0 : diff[i-1];
    diff[i] = last;
    if (a[i] >= m) diff[i]++;
    else diff[i]--;

    if (diff[i] > 0) {
      // special case: [0,i]
      ans++;
    }
    if (diff[i] > -n) {
      ans += ft.cumulativeSum(diff[i]-1+n);
    }
    ft.incEntry(diff[i]+n, 1);
  }
  return ans;
}

int main()
{
  int m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  cout << f(m) - f(m+1) << endl;
  return 0;
}
