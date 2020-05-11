#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>

using namespace std;
#include <vector>
#include <cassert>

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

int revprime[80000];
int divisors[80000];
int numrp = 0;

int getdivisors(int n)
{
  int count = 0;

  while ((n & 1) == 0) {
    n >>= 1;
    count++;
  }

  for (int p = 3; p*p <= n; p += 2) {
    while (n % p == 0) {
      n /= p;
      count++;
    }
  }
  if (n > 1) {
    count++;
  }
  return count;
}

void genprimes()
{
  bool prime[1000000];
  fill(prime+2, prime+1000000, true);
  prime[0] = prime[1] = false;
  for (int p = 2; p < 1000000; p++) {
    if (!prime[p]) continue;

    int x = 0, y = p;
    for (int i = 0; i < 7; i++) {
      x = x*10 + y % 10;
      y /= 10;
    }
    revprime[numrp++] = x;

    for (int k = p+p; k < 1000000; k += p) {
      prime[k] = false;
    }
  }

  sort(revprime, revprime+numrp);

  for (int i = 0; i < numrp; i++) {
    divisors[i] = getdivisors(revprime[i]);
  }
}

FenwickTree sum_tree, count_tree;

void build_tree()
{
  int count[80000];
  fill(count, count+numrp, 1);
  sum_tree.initialize(divisors, numrp);
  count_tree.initialize(count, numrp);
}

int query(int index)
{
  int findex = count_tree.getIndex(index) + 1;
  assert(count_tree.cumulativeSum(findex) == index+1);
  return sum_tree.cumulativeSum(findex);
}

void del(int val)
{
  int idx = lower_bound(revprime, revprime+numrp, val) - revprime;
  sum_tree.incEntry(idx, -divisors[idx]);
  count_tree.incEntry(idx, -1);
}

int main(void)
{
  genprimes();

  build_tree();

  char ch;
  int x;
  while (cin >> ch >> x) {
    if (ch == 'q') {
      cout << query(x) << endl;
    } else if (ch == 'd') {
      del(x);
    }
  }
  return 0;
}
