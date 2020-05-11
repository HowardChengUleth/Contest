#include <iostream>
#include <algorithm>
#include <cassert>

// nodes are labeled by triples:
//
// level (0 = innermost, N-1 = outermost)
// start angle, end angle (counterclockwise, and it may be that
//                         end angle < start angle)
//
// a special node with level N is the outside

using namespace std;

typedef pair<int, pair<int,int> > tiii;

// for some reason I can't get it accepted with these set to 10...
const int MAX_N = 20;
const int MAX_WALL = 20;
const int MAX_GATE = 20;
const int MAX_ROOM = MAX_N*MAX_WALL + 1;
tiii room[MAX_ROOM];
int num_rooms;
bool adj[MAX_ROOM][MAX_ROOM];
int ang[MAX_ROOM][MAX_ROOM];

void add_room(int level, int start, int end)
{
  room[num_rooms++] = make_pair(level, make_pair(start, end));
}

bool search(int from, bool visited[], int path[], int path_len)
{
  visited[from] = true;
  path[path_len] = from;

  if (from == 0) {
    return true;
  }
  
  for (int i = 0; i < num_rooms; i++) {
    if (adj[from][i] && !visited[i]) {
      if (search(i, visited, path, path_len+1)) {
	return true;
      }
    }
  }
  return false;
}

bool do_case(int id)
{
  int N;
  cin >> N;
  if (!N) return false;

  assert(1 <= N && N <= 10);
  cout << "Case " << id << ":";

  num_rooms = 0;
  int num_gate[MAX_N] = {0};
  int gate[MAX_N][MAX_GATE];

  for (int i = 0; i < N; i++) {
    cin >> num_gate[i];
    assert(0 <= num_gate[i] && num_gate[i] <= 10);
    for (int j = 0; j < num_gate[i]; j++) {
      cin >> gate[i][j];
    }

    int num_walls;
    cin >> num_walls;
    assert(i > 0 || num_walls == 0);
    assert(num_walls <= 10);
    int wall[MAX_WALL];
    for (int j = 0; j < num_walls; j++) {
      cin >> wall[j];
    }
    sort(wall, wall+num_walls);

    if (num_walls <= 1) {
      add_room(i, 0, 360);
    } else {
      for (int j = 0; j < num_walls; j++) {
	add_room(i, wall[j], wall[(j+1)%num_walls]);
      }
    }
  }
  add_room(N, 0, 360);

  assert(num_rooms <= 10*10 + 1);
  
  for (int i = 0; i < num_rooms; i++) {
    int start1 = room[i].second.first;
    int end1 = room[i].second.second;
    for (int j = i+1; j < num_rooms; j++) {
      adj[i][j] = adj[j][i] = 0;
      if (abs(room[i].first - room[j].first) != 1) continue;

      int inner = min(room[i].first, room[j].first);
      int start2 = room[j].second.first;
      int end2 = room[j].second.second;

      // find a gate
      for (int k = 0; k < num_gate[inner]; k++) {
	if (((start1 <= end1 && start1 <= gate[inner][k] &&
	      gate[inner][k] <= end1) ||
	     (end1 < start1 &&
	      !(end1 < gate[inner][k] && gate[inner][k] < start1))) &&
	    ((start2 <= end2 && start2 <= gate[inner][k] &&
	      gate[inner][k] <= end2) ||
	     (end2 < start2 &&
	      !(end2 < gate[inner][k] && gate[inner][k] < start2)))) {
	  adj[i][j] = adj[j][i] = 1;
	  ang[i][j] = ang[j][i] = gate[inner][k];
	}
      }
    }
  }

  int path[MAX_ROOM];
  bool visited[MAX_ROOM] = {0};
  if (!search(num_rooms-1, visited, path, 0)) {
    cout << " No solution";
  } else {
    for (int i = 0; path[i] != 0; i++) {
      int from = path[i], to = path[i+1];
      cout << ' ' << ang[from][to];
      if (room[from].first < room[to].first) {
	cout << " OUT";
      } else {
	cout << " IN";
      }
    }
  }
  cout << endl;
  
  return true;
}

int main()
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
