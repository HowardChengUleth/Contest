/* @JUDGE_ID: 1102NT 10511 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CLUB 500
#define MAX_NODE 1+1+MAX_CLUB+1000+1000 /* src, sink, clubs, people, parties */

/* some macros to map the node indices */
#define SRC 0
#define SINK 1
#define PERSON(x)  (2+(x))
#define PARTY(x)   (1002+(x))
#define CLUB(x)    (2002+(x))
#define PERSONI(x) ((x)-2)
#define PARTYI(x)  ((x)-1002)
#define CLUBI(x)   ((x)-2002)

typedef struct {
    int deg;
    int *nbrs, *cap;
} Node;

char person[1000][81];
char party[1000][81];
char club[MAX_CLUB][81];
int n_person, n_party, n_club;

Node graph[MAX_NODE];

void allocate_graph(void)
{
  int i;
  
  graph[SRC].nbrs = malloc(MAX_CLUB*sizeof(int));
  graph[SRC].cap = malloc(MAX_CLUB*sizeof(int));
  graph[SINK].nbrs = malloc(1000*sizeof(int));
  graph[SINK].cap = malloc(1000*sizeof(int));
  assert(graph[SRC].nbrs && graph[SRC].cap);
  assert(graph[SINK].nbrs && graph[SINK].cap);
  
  for (i = 0; i < 1000; i++) {
    graph[PERSON(i)].nbrs = malloc(50*sizeof(int));
    graph[PARTY(i)].nbrs = malloc(1002*sizeof(int));
    graph[PERSON(i)].cap = malloc(50*sizeof(int));
    graph[PARTY(i)].cap = malloc(1002*sizeof(int));
    assert(graph[PERSON(i)].nbrs && graph[PERSON(i)].cap);
    assert(graph[PARTY(i)].nbrs && graph[PARTY(i)].cap);
  }
  for (i = 0; i < MAX_CLUB; i++) {
    graph[CLUB(i)].nbrs = malloc(1001*sizeof(int));
    graph[CLUB(i)].cap = malloc(1001*sizeof(int));
    assert(graph[CLUB(i)].nbrs && graph[CLUB(i)].cap);
  }
}

void clear_graph(void)
{
  int i;

  for (i = 0; i < MAX_NODE; i++) {
    graph[i].deg = 0;
  }
}

void add_edge(int u, int v, int cap)
{
  graph[u].nbrs[graph[u].deg] = v;
  graph[u].cap[graph[u].deg++] = cap;
  graph[v].nbrs[graph[v].deg] = u;
  graph[v].cap[graph[v].deg++] = 0;
}

int find1(char A[1000][81], int n, char *p)
{
  int i;
  
  for (i = 0; i < n; i++) {
    if (!strcmp(A[i], p)) {
      return i;
    }
  }
  return -1;
}

int find2(char A[MAX_CLUB][81], int n, char *p)
{
  int i;
  
  for (i = 0; i < n; i++) {
    if (!strcmp(A[i], p)) {
      return i;
    }
  }
  return -1;
}

void read_case(void)
{
  char buffer[1024], *p;
  int person_ind, party_ind, club_ind;
  int i;

  n_person = n_party = n_club = 0;
  clear_graph();
  
  while (fgets(buffer, 1024, stdin) && buffer[0] != '\n') {
    p = strtok(buffer, " \n");
    assert(p);
    if ((person_ind = find1(person, n_person, p)) < 0) {
      person_ind = n_person;
      strcpy(person[n_person++], p);
      assert(n_person <= 1000);
    }
    
    p = strtok(0, " \n");
    assert(p);
    if ((party_ind = find1(party, n_party, p)) < 0) {
      party_ind = n_party;
      strcpy(party[n_party++], p);
      assert(n_party <= 1000);
    }
    add_edge(PERSON(person_ind), PARTY(party_ind), 1);
    
    while ((p = strtok(0, " \n"))) {
      if ((club_ind = find2(club, n_club, p)) < 0) {
	club_ind = n_club;
	strcpy(club[n_club++], p);
	assert(n_club <= MAX_CLUB);
      }
      add_edge(CLUB(club_ind), PERSON(person_ind), 1);
    }
  }

  for (i = 0; i < n_club; i++) {
    add_edge(SRC, CLUB(i), 1);
  }
  for (i = 0; i < n_party; i++) {
    add_edge(PARTY(i), SINK, (n_club-1)/2);
  }
}

int augmenting_path(Node *graph, int s, int t, int *path, char *visited,
		    int minflow)
{
  int i, v, flow;
  
  if (s == t) {
    return -1;
  }
  for (i = 0; i < graph[s].deg; i++) {
    v = graph[s].nbrs[i];
    if (graph[s].cap[i] >= minflow && !visited[v]) {
      path[0] = i;
      visited[v] = 1;
      if ((flow = augmenting_path(graph, v, t, path+1, visited, minflow))) {
	if (flow == -1) {
	  return graph[s].cap[i];
	} else {
	  return (flow < graph[s].cap[i]) ? flow : graph[s].cap[i];
	}
      }
    }
  }
  return 0;
}

void push_path(Node *graph, int s, int t, int *path, int flow)
{
  int v, w;
  int i, j;

  for (v = s, i = 0; v != t; v = w, i++) {
    w = graph[v].nbrs[path[i]];
    graph[v].cap[path[i]] -= flow;
    for (j = 0; j < graph[w].deg; j++) {
      if (graph[w].nbrs[j] == v) {
	graph[w].cap[j] += flow;
	break;
      }
    }
  }
}

int network_flow(int s, int t)
{
  char visited[MAX_NODE];
  int path[MAX_NODE];
  int flow = 0, f = 1;
  int i, minflow;

  memset(visited, 0, MAX_NODE);
  while (f) {
    minflow = 0;
    for (i = 0; i < graph[s].deg; i++) {
      if (minflow < graph[s].cap[i]) {
	minflow = graph[s].cap[i];
      }
    }
    for (f = 0; minflow; minflow /= 2) {
      memset(visited, 0, MAX_NODE);
      if (f = augmenting_path(graph, s, t, path, visited, minflow)) {
	push_path(graph, s, t, path, f);
	flow += f;
	break;
      }
    }
  }

  return flow;
}

void print_flow(void)
{
  int i, j, person_ind;

  for (i = 0; i < n_club; i++) {
    for (j = 0; j < graph[CLUB(i)].deg; j++) {
      if (graph[CLUB(i)].cap[j] == 0) {
	person_ind = graph[CLUB(i)].nbrs[j];
	printf("%s %s\n", person[PERSONI(person_ind)], club[i]);
	break;
      }
    }
  }
}

int main(void)
{
  int T, flow;

  allocate_graph();
  scanf("%d\n", &T);
  while (T-- > 0) {
    read_case();
    flow = network_flow(SRC, SINK);
    if (flow >= n_club) {
      print_flow();
    } else {
      printf("Impossible.\n");
    }
    
    if (T > 0) {
      printf("\n");
    }
  }
  
  return 0;
}


