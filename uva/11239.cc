#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

bool is_project(const string line)
{
  for (int i = 0; i < line.length(); i++) {
    if (islower(line[i]))
      return false;
  }
  return true;
}

void solve_case(string line)
{
  map<string, string> student;
  string project;
  int num_project = 0;

  map<string, int> count;

  while (line[0] != '1') {
    if (is_project(line)) {
      project = line;
      count[project] = 0;
      num_project++;
    } else {
      if (student[line] == "") {
	//	cout << "project = " << project << ", student = " << line << endl;
	student[line] = project;
      } else if (student[line] != project) {
	student[line] = "bad project";  // lowercase ==> invalid project
      }
    }
    getline(cin, line);
  }

  for (map<string,string>::const_iterator it = student.begin();
       it != student.end(); ++it) {
    if (is_project(it->second)) {
      count[it->second]++;
    }
  }

  vector< pair<int, string> > result(num_project);
  int k = 0;
  for (map<string,int>::const_iterator it = count.begin();
       it != count.end(); ++it) {
    result[k].first = -it->second;
    result[k++].second = it->first;
  }
  sort(result.begin(), result.end());

  for (k = 0; k < num_project; k++) {
    cout << result[k].second << " " << -result[k].first << endl;
  }

}

int main(void)
{
  string line;

  while (getline(cin, line) && line[0] != '0') {
    solve_case(line);
  }

  return 0;
}
