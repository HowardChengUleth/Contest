#include <bits/stdc++.h>

using namespace std;

bool check_byr(string s)
{
  if (s.length() != 4) return false;
  for (auto c : s) {
    if (!isdigit(c)) return false;
  }
  int yr = stoi(s);
  return (1920 <= yr && yr <= 2002);
}

bool check_iyr(string s)
{
  if (s.length() != 4) return false;
  for (auto c : s) {
    if (!isdigit(c)) return false;
  }
  int yr = stoi(s);
  return (2010 <= yr && yr <= 2020);
}

bool check_eyr(string s)
{
  if (s.length() != 4) return false;
  for (auto c : s) {
    if (!isdigit(c)) return false;
  }
  int yr = stoi(s);
  return (2020 <= yr && yr <= 2030);
}

bool check_hgt(string s)
{
  int n = s.length();
  string unit = s.substr(n-2);
  if (!(unit == "cm" || unit == "in")) return false;

  for (auto c : s.substr(0, n-2)) {
    if (!isdigit(c)) return false;
  }
  
  int h = stoi(s.substr(0,n-2));

  if (unit == "cm") {
    return 150 <= h && h <= 193;
  } else {
    return 59 <= h && h <= 76;
  }
}

bool check_hcl(string s)
{
  if (s.length() != 7) return false;
  if (s[0] != '#') return false;
  for (int i = 1; i < 7; i++) {
    if (!isdigit(s[i]) && !('a' <= s[i] && s[i] <= 'f'))
      return false;
  }
  return true;
}

bool check_ecl(string s)
{
  const string valid[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  return find(valid, valid+7, s) != valid+7;
}

bool check_pid(string s)
{
  if (s.length() != 9) return false;
  for (auto c : s) {
    if (!isdigit(c)) return false;
  }
  return true;
}

const string field[] = {"byr", "iyr", "eyr", "hgt",
			"hcl", "ecl", "pid", "cid"};

typedef bool (*check_func)(string s);

check_func func[] = {check_byr, check_iyr, check_eyr, check_hgt,
		     check_hcl, check_ecl, check_pid};


bool validA(string entry)
{
  bool present[8] = {false};
  
  istringstream iss(entry);
  string f;

  while (iss >> f) {
    f = f.substr(0,3);
    int index = find(field, field+8, f) - field;
    if (index == 8) continue;
    present[index] = true;
  }

  return count(present, present+7, false) == 0;
}

bool validB(string entry)
{
  bool present[8] = {false};
  
  istringstream iss(entry);
  string f;

  while (iss >> f) {
    string tag = f.substr(0,3);
    int index = find(field, field+8, tag) - field;
    if (index >= 7) continue;
    present[index] = true;
    if (!func[index](f.substr(4))) {
      return false;
    }
  }

  return count(present, present+7, false) == 0;
}

int main()
{
  string line;
  int countA = 0;
  int countB = 0;
  
  while (getline(cin, line)) {
    string entry = line;
    while (getline(cin, line) && line != "") {
      entry += " ";
      entry += line;
    }

    if (validA(entry)) {
      countA++;
    }
    if (validB(entry)) {
      countB++;
    }
  }

  cout << "A: " << countA << endl;
  cout << "B: " << countB << endl;

  return 0;
}
