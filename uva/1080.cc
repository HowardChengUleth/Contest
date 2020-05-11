#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

int N, G, U;
int u[20];
int B;
int input[300][10];
int output[300][20];

struct Gate
{
  char type;
  string in1, in2;
  int error;  // 0 = good, 1 = invert, 2 = gives 0, 3 = gives 1
  void read()
  {
    cin >> type >> in1;
    if (type != 'n') {
      cin >> in2;
    } else {
      in2 = in1;
    }
    error = 0;
  }

  int eval(int input[]);  
};

Gate gate[20];

int num(string name)
{
  int val = name[1] - '0';
  if (name.length() > 2) {
    val = val*10 + name[2] - '0';
  }
  return val;
}

int Gate::eval(int input[])
{
  if (error == 2) {
    return 0;
  } else if (error == 3) {
    return 1;
  }
  
  int val1, val2;
  if (in1[0] == 'i') {
    val1 = input[num(in1)];
  } else {
    val1 = gate[num(in1)].eval(input);
  }
  
  if (type != 'n') {
    if (in2[0] == 'i') {
      val2 = input[num(in2)];
    } else {
      val2 = gate[num(in2)].eval(input);
    }
  }
  
  int ans;
  switch (type) {
  case 'n':
    ans = !val1;
    break;
  case 'a':
    ans = val1 && val2;
    break;
  case 'o':
    ans = val1 || val2;
    break;
  case 'x':
    ans = (val1 && !val2) || (!val1 && val2);
    break;
  }
  
  if (error) {
    return !ans;
  } else {
    return ans;
  }
}


bool equal(int a, int b)
{
  return (!a && !b) || (a && b);
}

bool check()
{
  int temp_out[20];
  for (int b = 0; b < B; b++) {
    for (int i = 1; i <= U; i++) {
      temp_out[i] = gate[u[i]].eval(input[b]);
    }

    for (int i = 1; i <= U; i++) {
      if (!equal(temp_out[i], output[b][i])) {
	return false;
      }
    }
  }

  return true;
}

const string error_msg[] = {
  "",
  "inverted",
  "stuck at 0",
  "stuck at 1"
};

bool solve(int id)
{
  cin >> N >> G >> U;
  if (!N && !G && !U) return false;
  assert(1 <= N && N <= 8);
  assert(1 <= G && G <= 19);
  assert(1 <= U && U <= 19);
  for (int i = 1; i <= G; i++) {
    gate[i].read();
  }

  for (int i = 1; i <= U; i++) {
    cin >> u[i];
  }

  cin >> B;
  assert(1 <= B && B <= (1 << N));
  for (int i = 0; i < B; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> input[i][j];
    }
    for (int j = 1; j <= U; j++) {
      cin >> output[i][j];
    }
  }
  
  cout << "Case " << id << ": ";
  if (check()) {
    cout << "No faults detected" << endl;
    return true;
  }
  int bad_gate = -1;
  int bad_error = -1;
  for (int i = 1; i <= G; i++) {
    for (int k = 1; k <= 3; k++) {
      gate[i].error = k;
      if (check()) {
	if (bad_gate != -1) {
	  cout << "Unable to totally classify the failure" << endl;
	  return true;
	}
	bad_gate = i;
	bad_error = k;
      }
    }
    gate[i].error = 0;
  }
  if (bad_error == -1) {
    cout << "Unable to totally classify the failure" << endl;
  } else {
    cout << "Gate " << bad_gate << " is failing; output "
	 << error_msg[bad_error] << endl;
  }
  
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;

  return 0;
}
