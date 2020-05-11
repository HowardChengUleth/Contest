#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Array
{
  string name;
  int B, elem_size, D;
  int L[11], U[11];

  int addr(int *i) const
  {
    int C[11];

    C[D] = elem_size;
    for (int d = D-1; d >= 1; d--) {
      C[d] = C[d+1]*(U[d+1] - L[d+1] + 1);
    }
    C[0] = B;
    for (int d = 1; d <= D; d++) {
      C[0] -= C[d]*L[d];
    }

    int ans = C[0];
    for (int d = 1; d <= D; d++) {
      ans += C[d]*i[d];
    }
    return ans;
  }

  void print(int *i) const
  {
    cout << name << '[';
    for (int d = 1; d <= D; d++) {
      cout << i[d];
      if (d < D) {
	cout << ", ";
      }
    }
    cout << "] = " << addr(i) << endl;
  }
};

istream &operator>>(istream &is, Array &A)
{
  is >> A.name >> A.B >> A.elem_size >> A.D;
  for (int i = 1; i <= A.D; i++) {
    is >> A.L[i] >> A.U[i];
  }
  return is;
}

int main(void)
{
  int N, R;
  cin >> N >> R;

  vector<Array> vec(N);
  for (int i = 0; i < N; i++) {
    cin >> vec[i];
  }

  for (int k = 0; k < R; k++) {
    string name;
    cin >> name;
    
    int j = 0;
    while (vec[j].name != name) {
      j++;
    }
    
    int i[11];
    for (int t = 1; t <= vec[j].D; t++) {
      cin >> i[t];
    }

    vec[j].print(i);
  }
  return 0;
}
