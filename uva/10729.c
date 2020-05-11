/* @JUDGE_ID: 1102NT 10729 C "" */

#include <stdio.h>
#include <string.h>

/* 
 * we will build a graph with adjacency list representation (each edge
 * is represented in both directions.  The neighbours in the list are
 * listed in counter-clockwise order.
 *
 * We know that there are at most 200 nodes.
 */

typedef struct {
  char label;
  int deg;
  int nbr[200];
  int nbr_i[200];   
  /* "back pointer": if a node x has nbr[j] = node y, then node x is
   * found in the nbr array of y at position nbr_i[j]. See equivalent()
   * to see how the back pointer is used. */
} Node;

Node tree1[200], tree2[200];
int num1, num2;

/*
 * parse the substring str[start..end-1]
 *
 * parent: the node number of parent
 * parent_i: where the current root will be added in parent's nbr array
 * tree: the array of Nodes storing the tree
 * num: pointer to variable storing number of nodes so far
 *
 * returns the node number of the root
 *
 */

int parse(char *str, int start, int end, int parent, int parent_i, 
	  Node *tree, int *num)
{
  int node = (*num)++;
  int level = 1;   /* keeps track of bracket level */
  int i, t;

  /* set up the root of the tree */
  tree[node].label = str[start++];
  tree[node].deg = 0;
  if (parent != -1) {  /* parent = -1 if there is no parent (root of tree */
    tree[node].nbr[tree[node].deg] = parent;
    tree[node].nbr_i[tree[node].deg++] = parent_i;
  }
  if (str[start++] != '(') {
    /* no children */
    return node;
  }
  
  /* process the children */
  for (i = start; i < end; i++) {
    if (str[i] == '(') level++;

    /* need to keep track of level so we don't get , inside subtrees */
    if (str[i] == ',' && level == 1) {
      t = parse(str, start, i, node, tree[node].deg, tree, num);
      tree[node].nbr[tree[node].deg] = t;

      /* parent always get added first */
      tree[node].nbr_i[tree[node].deg++] = 0;

      start = i+1;   /* move past the processed part */
    }
    if (str[i] == ')') {

      /* only process if it's not inside subtrees */
      if (level == 1) {
	t = parse(str, start, i, node, tree[node].deg, tree, num);
	
	/* parent always get added first */
	tree[node].nbr[tree[node].deg] = t;
	tree[node].nbr_i[tree[node].deg++] = 0;
	
	start = i+1;	
      }
      level--;
    }
  }
  return node;
}

/*
 * check that two subtrees at root1 and root2 are equivalent
 *
 * from1 and from2 are the indices of the parents of root1 and root2 in the 
 * root1/root2's nbr array.  "parent" refers to the parent in the traversal
 * process here.  Basically, we fix the orientation of the drawing by
 * starting to match the children immediately to the right of the parent.
 *
 */

int equivalent(int root1, int from1, int root2, int from2)
{
  int i1, i2;

  /* if label is different or have different degrees, quit */
  if (tree1[root1].label != tree2[root2].label ||
      tree1[root1].deg != tree2[root2].deg) {
    return 0;
  }
  
  /* I have to start looking at children one node after where I came
     from.  This normalizes the orientation */
  i1 = (from1+1) % tree1[root1].deg;
  i2 = (from2+1) % tree2[root2].deg;

  /* go around in a circle to check all children */
  while (i1 != from1) {
    if (!equivalent(tree1[root1].nbr[i1], tree1[root1].nbr_i[i1],
		    tree2[root2].nbr[i2], tree2[root2].nbr_i[i2])) {
      return 0;
    }
    i1 = (i1+1) % tree1[root1].deg;
    i2 = (i2+1) % tree2[root2].deg;
  }
  return 1;
}

/*
 * Check the two trees assuming the roots are root1 and root2.
 *
 * Because there are no parents in the traversal yet, we can't do what we
 * did above.  Therefore, we try all possible ways of matching the
 * children
 *
 */

int check_roots(int root1, int root2)
{
  int start1, start2, i1, i2;
  int i, bad;

  /* if label is different or have different degrees, quit */
  if (tree1[root1].label != tree2[root2].label ||
      tree1[root1].deg != tree2[root2].deg) {
    return 0;
  }
  
  if (tree1[root1].deg == 0) {
    /* both are isolated vertices */
    return 1;
  }

  /* 
   * need to try all different match-ups of children: this checks to see
   * if we can match the child of root1 at start1 to the child of root2
   * at start2
   */
  start1 = 0;
  for (start2 = 0; start2 < tree2[root2].deg; start2++) {

    /* now that we have fixed the orientation, check all children */
    bad = 0;
    for (i = 0; i < tree2[root2].deg && !bad; i++) {
      i1 = (start1+i) % tree1[root1].deg;
      i2 = (start2+i) % tree2[root2].deg;
      bad |= !equivalent(tree1[root1].nbr[i1], tree1[root1].nbr_i[i1],
			 tree2[root2].nbr[i2], tree2[root2].nbr_i[i2]);
    }

    /* we found an equivalence.  Say yes */
    if (!bad) {
      return 1;
    }
  }

  /* all possibilities exhausted.  Say no */
  return 0;
}

int main(void)
{
  int cases;
  char str1[201], str2[201];
  int i;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%s %s", str1, str2);
    num1 = num2 = 0;
    parse(str1, 0, strlen(str1), -1, -1, tree1, &num1);
    parse(str2, 0, strlen(str2), -1, -1, tree2, &num2);

    /* need to find all possible ways to match two roots */
    for (i = 0; i < num1; i++) {
      if (check_roots(i, 0)) {
	break;
      }
    }
    printf("%s\n", (i < num1) ? "same" : "different");
  }
  return 0;
}
