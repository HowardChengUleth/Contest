/*
 * Fenwick Tree
 *
 * Author: Howard Cheng
 * Reference:
 *
 *   Fenwick, P.M. "A New Data Structure for Cumulative Frequency Tables."
 *   Software---Practice and Experience, 24(3), 327-336 (March 1994).
 *
 * This code has been tested on UVa 11610.
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
#include <iostream>

using namespace std;

class FenwickTree
{
public:
  FenwickTree(int n = 0)
    : N(n), tree(n)
  {
    int k = 1;
    while (k < N) {
      k *= 2;
    }
    iBM = k;
    fill(tree.begin(), tree.end(), 0);
  }

  // initialize the tree with the given array of values
  FenwickTree(int val[], int n)
  {
    initialize(val, n);
  }

  // initialize the tree with the given array of values
  void initialize(int val[], int n)
  {
    N = n;
    int k = 1;
    while (k < N) {
      k *= 2;
    }
    iBM = k;
    
    tree.resize(k+1);
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
  // NOTE: the index returned can be greater than the length of the original
  //       array.  If that is not wanted, take the minimum of the original
  //       N-1 and the result (if it's not -1).
  int getIndex(int sum) const
  {
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
    } else {
      return idx;
    }
  }
  
private:
  int N, iBM;
  vector<int> tree;
};

void solve()
{
  int K;
  cin >> K;

  int ones[50001];
  ones[0] = 0;
  fill(ones+1, ones+K+1, 1);
  FenwickTree tree(ones, K+1);

  for (int i = 0; i < K; i++) {
    int coeff;
    cin >> coeff;
    int index = tree.getIndex(coeff) + 1;
    if (i) cout << ' ';
    cout << index;
    tree.incEntry(index, -1);
  }
  cout << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
