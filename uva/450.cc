#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

class Person {
private:
  string title, first, last, addr, dept, homephone, workphone, box;

public:
  Person(const string &d, const string &line)
    : dept(d)
  { 
    char *c_line = new char[line.length()+1];
    strcpy(c_line, line.c_str());

    title = strtok(c_line, ",");
    first = strtok(0, ",");
    last = strtok(0, ",");
    addr = strtok(0, ",");
    homephone = strtok(0, ",");
    workphone = strtok(0, ",");
    box = strtok(0, ",");
    delete[] c_line;
  }

  bool operator<(const Person &p) const
  {
    return last < p.last;
  }

  friend ostream &operator<<(ostream &os, const Person &p);

};

ostream &operator<<(ostream &os, const Person &p)
{
  os << "----------------------------------------" << endl;
  os << p.title << " " << p.first << " " << p.last << endl;
  os << p.addr << endl;
  os << "Department: " << p.dept << endl;
  os << "Home Phone: " << p.homephone << endl;
  os << "Work Phone: " << p.workphone << endl;
  os << "Campus Box: " << p.box << endl;
  return os;
}


int main(void)
{
  int num_depts;
  vector<Person> v;

  cin >> num_depts;
  cin.ignore();
  
  while (num_depts-- > 0) {
    string dept;
    getline(cin, dept);
    
    string record;
    while (getline(cin, record) && record != "") {
      Person p(dept, record);
      v.push_back(p);
    }
  }

  sort(v.begin(), v.end());
  for (unsigned int i = 0; i < v.size(); i++) {
    cout << v[i];
  }
  return 0;
}
