#include <iostream>
#include <map>

using namespace std;

bool firable(const map<int, int> &transition, const int tokens[])
{
  for (map<int,int>::const_iterator it = transition.begin();
       it != transition.end(); ++it) {
    if (it->first < 0 && tokens[-(it->first)-1] < it->second) {
      return false;
    }
  }
  return true;
}

int find_firable(const map<int, int> transition[], const int tokens[], 
		 int NT)
{
  for (int i = 0; i < NT; i++) {
    if (firable(transition[i], tokens)) {
      return i;
    }
  }
  return NT;
}

void fire(const map<int, int> &transition, int tokens[])
{
  for (map<int,int>::const_iterator it = transition.begin();
       it != transition.end(); ++it) {
    if (it->first < 0) {
      tokens[-(it->first)-1] -= it->second;
    } else if (it->first) {
      tokens[it->first-1] += it->second;
    }
  }
}

void print_tokens(const int tokens[], int NP)
{
  cout << "Places with tokens:";
  for (int i = 0; i < NP; i++) {
    if (tokens[i] > 0) {
      cout << ' ' << i+1 << " (" << tokens[i] << ")";
    }
  }
  cout << endl;
}

bool do_case(int case_num)
{
  int NP;

  cin >> NP;
  if (NP == 0) {
    return false;
  }

  cout << "Case " << case_num << ": ";

  int tokens[100];
  for (int i = 0; i < NP; i++) {
    cin >> tokens[i];
  }

  int NT;
  cin >> NT;
  map<int, int> transition[100];
  for (int i = 0; i < NT; i++) {
    int x;
    while (cin >> x && x != 0) {
      transition[i][x]++;
    }
  }

  int NF;
  cin >> NF;

  int step = 0;
  while (step < NF) {
    int index = find_firable(transition, tokens, NT);
    if (index >= NT) {
      cout << "dead after " << step << " transitions" << endl;
      print_tokens(tokens, NP);
      cout << endl;
      return true;
    }
    fire(transition[index], tokens);
    step++;
  }
  cout << "still live after " << NF << " transitions" << endl;
  print_tokens(tokens, NP);
  cout << endl;

  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
