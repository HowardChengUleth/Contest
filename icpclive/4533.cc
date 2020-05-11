#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

void apply(const vector<int> &lhs, const vector<int> &rhs, int op,
	   vector<int> &result)
{
  for (int i = 0; i < lhs.size(); i++) {
    for (int j = 0; j < rhs.size(); j++) {
      int a = lhs[i], b = rhs[j];
      switch (op) {
      case 0:
	result.push_back(a+b);
	break;
      case 1:
	result.push_back(a-b);
	break;
      case 2:
	result.push_back(a*b);
	break;
      case 3:
	if (b != 0 && a % b == 0) {
	  result.push_back(a/b);
	}
	break;
      default:
	assert(false);
      }
    }
  }
}

void compute(int A[], int op[], int n, vector<int> &result)
{
  if (n == 1) {
    result.push_back(A[0]);
    return;
  }

  for (int i = 1; i <= n-1; i++) {
    vector<int> lhs;
    compute(A, op, i, lhs);
    vector<int> rhs;
    compute(A+i, op+i, n-i, rhs);
    apply(lhs, rhs, op[i-1], result);
  }
  sort(result.begin(), result.end());
  result.erase(unique(result.begin(), result.end()), result.end());
}

int main(void)
{
  int case_num = 1;
  int A[4];
  int op[3];

  while (cin >> A[0] >> A[1] >> A[2] >> A[3] && 
	 (A[0] || A[1] || A[2] || A[3])) {
    cout << "Case " << case_num++ << ": ";

    vector<int> result;
    sort(A, A+4);
    do {
      for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	  for (int k = 0; k < 4; k++) {
	    op[0] = i;
	    op[1] = j;
	    op[2] = k;
	    compute(A, op, 4, result);
	  }
	}
      }
    } while (next_permutation(A, A+4));

    int best_start = 0, best_end = 0;
    int i, j;
    for (i = 0; i < result.size(); i = j) {
      for (j = i+1; j < result.size() && result[j] == result[j-1]+1; j++)
	;
      int best_len = best_end - best_start + 1;
      int new_len = j - i;
      if (best_len < new_len || (best_len == new_len && i > best_start)) {
	best_start = i;
	best_end = j-1;
      }
    }
    cout << result[best_start] << " to " << result[best_end] << endl;
  }
  return 0;
}
