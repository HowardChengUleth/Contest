#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cstdlib>

using namespace std;

int main(void)
{
  int n, g;
  cin >> n >> g;

  map<string, int> party;
  for (int i = 0; i < n; i++) {
    string name;
    int d, f;
    char ch;
    cin >> name >> d >> ch >> f;
    party[name] = d*10+f;
  }

  cin.ignore(1);
  for (int i = 1; i <= g; i++) {
    cout << "Guess #" << i << " was ";
    string line;
    getline(cin, line);

    istringstream iss(line);
    string op;
    string token;
    int sum = 0;
    int rhs = 0;
    while (iss >> token) {
      if (token == "+") continue;
      if (token == "=" || token == "<" || token == ">" ||
	  token == ">=" || token == "<=") {
	op = token;
      } else if (party.find(token) == party.end()) {
	rhs = atoi(token.c_str()) * 10;
      } else {
	sum += party[token];
      }
    }

    if ((op == "=" && sum == rhs) ||
	(op == "<" && sum < rhs) ||
	(op == ">" && sum > rhs) ||
	(op == "<=" && sum <= rhs) ||
	(op == ">=" && sum >= rhs)) {
      cout << "correct." << endl;
    } else {
      cout << "incorrect." << endl;
    }
  }
  
  return 0;
}
