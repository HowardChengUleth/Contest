#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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
  FenwickTree(ll n = 0)
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
  FenwickTree(ll val[], ll n)
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
  void incEntry(int idx, ll val)
  {
    //    assert(0 <= idx && idx < N);
    if (idx == 0) {
      tree[idx] += val;
    } else {
      do {
	tree[idx] += val;
	idx += idx & (-idx);
      } while (idx < (ll)tree.size());
    }
  }

  // return the cumulative sum val[0] + val[1] + ... + val[idx]
  ll cumulativeSum(ll idx) const
  {
    //    assert(0 <= idx && idx < (int)tree.size());
    ll sum = tree[0];
    while (idx > 0) {
      sum += tree[idx];
      idx &= idx-1;
    }
    return sum;
  }

  // return the entry indexed by idx
  ll getEntry(ll idx) const
  {
    assert(0 <= idx && idx < N);
    ll val, parent;
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
  ll getIndex(ll sum) const
  {
    ll orig = sum;
    if (sum < tree[0]) return -1;
    sum -= tree[0];
    
    ll idx = 0;
    ll bitmask = iBM;

    while (bitmask != 0 && idx < (int)tree.size()-1) {
      ll tIdx = idx + bitmask;
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
  ll N, iBM;
  vector<ll> tree;
};

int main()
{
  /*
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  */
  int N, Q;
  scanf("%d %d", &N, &Q);
  //  printf("N = %d, Q = %d\n", N, Q);

  FenwickTree ft(N);
  while (Q--) {
    char op;
    ll i, d;

    scanf(" %c", &op);
    //    printf("op = %c, ", op);
    if (op == '+') {
      scanf("%lld %lld", &i, &d);
      //      printf("i = %d, d = %d\n", i, d);
      ft.incEntry(i, d);
    } else {
      scanf("%lld", &i);
      //      printf("i = %d\n", i);
      ll ans = (i ? ft.cumulativeSum(i-1) : 0);
      printf("%lld\n", ans);
    }
  }

  return 0;
}
