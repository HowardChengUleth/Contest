#include <iostream>
#include <iomanip>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_LIGHTS = 100;

struct Light {
  int g, y, r;
  bool visited, fringe;
  int arrive;         // earliest time that we can arrive
  int leave;          // earliest time that we can leave at full speed
  
  Light()
  {
    visited = fringe = false;
    arrive = leave = -1;
  }
};

istream &operator>>(istream &is, Light &light)
{
  return is >> light.g >> light.y >> light.r;
}

int G[MAX_LIGHTS][MAX_LIGHTS];
int n, m, s, e;

void update_fringe(int v, Light light[])
{
  for (int w = 0; w < n; w++) {
    if (G[v][w] < 0) continue;

    int new_arrival = light[v].leave + G[v][w];
    int new_leave;
    int cycle_len = light[w].g + light[w].y + light[w].r;
    int cycle_arr = new_arrival % cycle_len;
    if (cycle_arr < light[w].g + light[w].y) {
      new_leave = new_arrival;
    } else {
      new_leave = (new_arrival + (cycle_len-1)) / cycle_len * cycle_len + 5;
    }

    if (!light[w].fringe) {
      light[w].arrive = new_arrival;
      light[w].leave = new_leave;
    } else {
      light[w].arrive = min(light[w].arrive, new_arrival);
      light[w].leave = min(light[w].leave, new_leave);
    }
    light[w].fringe = true;
  }
}

bool do_case(void)
{
  Light light[MAX_LIGHTS];

  cin >> n >> m >> s >> e;
  if (!n && !m && !s && !e) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    cin >> light[i];
  }

  for (int i = 0; i < n; i++) {
    fill(G[i], G[i]+n, -1);
  }
  for (int i = 0; i < m; i++) {
    int l1, l2, t;
    cin >> l1 >> l2 >> t;
    G[l1][l2] = G[l2][l1] = t;
  }

  // run a modified Dijkstra
  light[s].arrive = 0;
  light[s].leave = 5;
  light[s].visited = true;

  update_fringe(s, light);
  while (true) {
    int min_index = -1;
    for (int v = 0; v < n; v++) {
      if (light[v].visited || !light[v].fringe) continue;
      if (min_index == -1 || light[v].leave < light[min_index].leave) {
	min_index = v;
      }
    }
    if (min_index == -1) {
      break;
    }
    light[min_index].visited = true;
    update_fringe(min_index, light);
  }

  cout << light[e].arrive/60 << ":"
       << setw(2) << setfill('0') << light[e].arrive%60 << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
