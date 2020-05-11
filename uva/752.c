/* @JUDGE_ID: 1102NT 752 C "" */
/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N        16
#define MAX_NODES   341

typedef struct {
  int intensity;             /* -1 if non-leaf */
  int child[4];
} Node;

int n;
int image1[MAX_N][MAX_N], image2[MAX_N][MAX_N];
Node tree1[MAX_NODES], tree2[MAX_NODES];

void read_tree(Node *tree)
{
  int leafs, num_nodes, i, k, t;

  num_nodes = 0;
  for (i = 1; i <= n; i *= 2) {
    num_nodes += i*i;
  }

  for (i = 0; i < num_nodes/4; i++) {
    tree[i].intensity = -1;
    for (k = 0; k < 4; k++) {
      tree[i].child[k] = 4*i+k+1;
    }
  }

  t = scanf("%d", &leafs);
  assert(t == 1 && 0 < leafs && leafs <= n*n);
  for (i = 0; i < leafs; i++) {
    t = scanf("%d", &k);
    assert(t == 1);

    t = scanf("%d", &(tree[k].intensity));
    assert(t == 1 && 0 <= tree[k].intensity && tree[k].intensity <= 255);

    /* check that all nodes above are internal nodes */
    while (k) {
      k = (k-1)/4;
      assert(tree[k].intensity == -1);
    }
  }
}

void decode_image(Node *tree, int image[MAX_N][MAX_N], int row, int col, 
		  int size, int root, int scramble)
{
  int i, j, r, c;

  assert(size > 0);
  
  if (tree[root].intensity == -1) {
    /* internal node */
    decode_image(tree, image, row, col, size/2, 
		 tree[root].child[0], scramble);
    decode_image(tree, image, row, col+size/2, size/2, 
		 tree[root].child[1], scramble);
    decode_image(tree, image, row+size/2, col, size/2, 
		 tree[root].child[2], scramble);
    decode_image(tree, image, row+size/2, col+size/2, size/2, 
		 tree[root].child[3], scramble);
  } else {
    /* leaf */
    for (i = row; i < row+size; i++) {
      for (j = col; j < col+size; j++) {
	if (!scramble) {
	  image[i][j] = tree[root].intensity;
	} else {
	  r = image1[i][j] / n;
	  c = image1[i][j] % n;
	  image[r][c] = tree[root].intensity;
	}
      }
    }
  }
}

void solve_case(void)
{
  int cases, k, i, j, t;

  t = scanf("%d", &cases);
  assert(t == 1 && cases > 0);

  for (k = 0; k < cases; k++) {
    t = scanf("%d", &n);
    assert(t == 1);
    assert(n == 1 || n == 2 || n == 4 || n == 8 || n == 16);
    
    read_tree(tree1);
    read_tree(tree2);

    decode_image(tree1, image1, 0, 0, n, 0, 0);
    decode_image(tree2, image2, 0, 0, n, 0, 1);

    if (k) {
      printf("\n");
    }
    printf("Case %d\n\n", k+1);

    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	printf("%4d", image2[i][j]);
      }
      printf("\n");
    }
  }
}

int main(void)
{
  solve_case();
  return 0;
}
