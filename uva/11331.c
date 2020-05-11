/*
 * This is basically bicoloring:
 *
 * For each connected component, start with a vertex and color it with 1.
 * Using DFS, the neighbours are colored 2, then their neighbours are
 * colored 1, etc.  If we see a conflict (e.g. a neighbour should be colored
 * 1 but is already assigned color 2.  This can only happen in an odd-length
 * cycle), then we cannot do it.
 *
 * If we are still okay after this, then each component is separated into
 * two colors.  We need to assign the cows to color 1 or color 2.  The bulls
 * will take the other color.  The question is whether we can assign
 * cows to each component so that the sum is correct.  This is done by
 * dynamic programming.
 *
 */

#include <stdio.h>

int nbr[2000][1999];
int deg[2000];
int comp_size[2000];
int c1_size[2000];       /* size of color 1 in component */
int num_comps;
int color[2000];
int a, b, c;
int possible[2][1001];

int DFS(int v, int col, int *c1_count)
{
  int i, w;
  int sum = 1, t;

  if ((color[v] = col) == 1) {
    (*c1_count)++;
  }
  for (i = 0; i < deg[v]; i++) {
    w = nbr[v][i];
    if (color[w]) {
      /* conflict */
      if (color[w] == color[v]) {
	return -1;
      }
    } else {
      /* do DFS on neighbours, switching color */
      if ((t = DFS(w, 3-col, c1_count)) == -1) {
	return -1;
      }
      sum += t;
    }
  }
  return sum;
}

int main(void)
{
  int n, i, j, u, v, index;
  int bad;
  
  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%d %d %d", &b, &c, &a);
    for (i = 0; i < b+c; i++) {
      deg[i] = 0;
      color[i] = 0;
    }
    for (i = 0; i < a; i++) {
      scanf("%d %d", &u, &v);
      u--; v--;
      nbr[u][deg[u]++] = v;
      nbr[v][deg[v]++] = u;
    }
    
    /* first do DFS */
    num_comps = 0;
    bad = 0;
    for (i = 0; i < b+c && !bad; i++) {
      if (!color[i]) {
	c1_size[num_comps] = 0;
	if ((comp_size[num_comps] = DFS(i, 1, c1_size+num_comps)) < 0) {
	  bad = 1;
	}
	num_comps++;
      }
    }
    
    /* if there is only one type of cows/bulls, this can only be done
       if every vertex is its own component. */
    if ((!b || !c) && num_comps != b+c) {
      bad = 1;
    }

    if (!bad) {
      /* do dynamic programming to see if we can sum up to the total number
	 of cows by seeing the possible sum after assigning cows to both
	 colors in each component.  I need to keep track of two vectors of
	 possibilities: one for the result up to the previous component, and
	 one for the result up to the current component (pointed to by index)
      */

      /* nothing is possible at the beginning except 0 */
      index = 0;
      possible[index][0] = possible[1-index][0] = 1;
      for (i = 1; i <= b; i++) {
	possible[index][i] = 0;
	possible[1-index][i] = 0;
      }
      
      for (j = 0; j < num_comps; j++) {
	for (i = 0; i < b; i++) {
	  /* for each one that was possible, try adding the number of
	     color 1 and color 2 vertices in the current component */
	  if (!possible[index][i]) continue;
	  possible[1-index][i] = 1;
	  if (i + c1_size[j] <= b) {
	    /* try color 1 */
	    possible[1-index][i + c1_size[j]] = 1;
	  }
	  if (i + comp_size[j] - c1_size[j] <= b) {
	    /* try color 2 */
	    possible[1-index][i + comp_size[j] - c1_size[j]] = 1;
	  }
	}
	index = 1-index;
	if (possible[index][b]) break;    /* we found it */
      }
      if (j < num_comps) {
	printf("yes\n");
      } else {
	printf("no\n");
      }
    } else {
      printf("no\n");
    }
  }
  return 0;
}

