/* @JUDGE_ID: 1102NT 560 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Bignum[21];

typedef struct {
  Bignum *A;
  int n, size;
} Heap;

int cmp(Bignum x, Bignum y)
{
  int i;

  for (i = 20; i >= 0; i--) {
    if (x[i] != y[i]) {
      return y[i] - x[i];
    }
  }
  return 0;
}

void copy(Bignum x, Bignum y)
{
  int i;
  for (i = 0; i < 21; i++) {
    x[i] = y[i];
  }
}

void clear(Bignum x)
{
  int i;
  for (i = 0; i < 21; i++) {
    x[i] = 0;
  }
}

void read_num(Bignum x)
{
  char buffer[1024];
  int i, j;

  scanf("%s", buffer);
  assert(strlen(buffer) <= 21);
  clear(x);
  for (i = strlen(buffer)-1, j = 0; i >= 0; i--, j++) {
    x[j] = buffer[i] - '0';
  }
}

void write_num(Bignum x)
{
  int i, lead_zero;

  lead_zero = 1;
  for (i = 20; i >= 0; i--) {
    if (x[i] != 0) {
      lead_zero = 0;
      putchar(x[i] + '0');
    } else if (!lead_zero) {
      putchar('0');
    }
  }
  if (lead_zero) {
    printf("0");
  }
  printf("\n");
}

int divide(Bignum x, int d, Bignum res)
{
  int i, rem;
 
  clear(res);
  rem = 0;
  for (i = 20; i >= 0; i--) {
    rem *= 10;
    res[i] = (rem + x[i]) / d;
    rem = (rem + x[i]) - d*res[i];
  }
  return rem;
}

int substring(Bignum x, int index, int num)
{
  int i;

  for (i = 1; i < num; i++) {
    if (x[index-i] != x[index]) {
      return 0;
    }
  }
  return 1;
}

void shrink(Bignum x, int index, int num)
{
  int i;

  assert(index+num <= 21);
  for (i = index; i < 21; i++) {
    x[i] = (i+num < 21) ? x[i+num] : 0;
  }
}

void init_heap(Heap *heap, int init_size)
{
  heap->A = malloc(init_size * sizeof(*(heap->A)));
  assert(heap->A);
  heap->n = 0;
  heap->size = init_size;
}

void free_heap(Heap *heap) 
{
  if (heap->size > 0) {
    free(heap->A);
    heap->n = 0;
    heap->size = 0;
  }
}

void up_heap(Heap *heap, int k)
{
  Bignum v;

  copy(v, heap->A[k]);
  assert(0 <= k && k < heap->n);
  while (k > 0 && cmp(v, heap->A[(k-1)/2]) < 0) {
    copy(heap->A[k], heap->A[(k-1)/2]);
    k = (k-1)/2;
  }
  copy(heap->A[k], v);
}

void down_heap(Heap *heap, int k)
{
  int j;
  Bignum v;

  copy(v, heap->A[k]);
  while (2*k+1 < heap->n) {
    j = 2*k+1;
    if (j+1 < heap->n && cmp(heap->A[j], heap->A[j+1]) > 0) {
      j++;
    }
    if (cmp(v, heap->A[j]) <= 0) {
      break;
    }
    copy(heap->A[k], heap->A[j]);
    k = j;
  }
  copy(heap->A[k], v);
}

void insert(Heap *heap, Bignum item)
{
  if (heap->n == heap->size) {
    heap->size += 10;
    heap->A = realloc(heap->A, heap->size*sizeof(*(heap->A)));
    assert(heap->A);
  }
  copy(heap->A[heap->n], item);
  up_heap(heap, heap->n++);
}

void delete(Heap *heap, Bignum item)
{
  copy(item, heap->A[0]);
  copy(heap->A[0], heap->A[--(heap->n)]);
  down_heap(heap, 0);
}

void do_case(Bignum x)
{
  Heap heap;
  Bignum curr, prev, t1, t2;
  int okay, rem, found, prev_init, index, i, len;

  copy(curr, x);
  init_heap(&heap, 100);
  prev_init = okay = 0;
  while (!okay) {
    if (!prev_init || cmp(prev, curr)) {
      prev_init = 1;
      okay = 1;
      copy(prev, curr);

      /* check if it is zero */
      clear(t1);
      if (!cmp(t1, curr)) {
	break;
      }
      
      /* try dividing by 3 and 7 */
      if (!(rem = divide(curr, 3, t1))) {
	insert(&heap, t1);
	okay = 0;
      }
      if (!(rem = divide(curr, 7, t1))) {
	insert(&heap, t1);
	okay = 0;
      }
      
      /* find 3 and 7 */
      for (i = 0; i < 21; i++) {
	if (curr[i] == 3 || curr[i] == 7) {
	  copy(t1, curr);
	  shrink(t1, i, 1);
	  insert(&heap, t1);
	  okay = 0;
	}
      }
      
      /* find the most significant digit */
      for (index = 20; index >= 0 && !curr[index]; index--)
	;

      /* find substrings of length 3 */
      found = 0;
      for (i = index; i >= 2; i--) {
	if (substring(curr, i, 3)) {
	  copy(t1, curr);
	  shrink(t1, i-2, 3);
	  if (!found || cmp(t1, t2)) {
	    insert(&heap, t1);
	    found = 1;
	    copy(t2, t1);
	  }
	  okay = 0;
	}
      }

      /* find substrings of length 7 */
      found = 0;
      for (i = index; i >= 6; i--) {
	if (substring(curr, i, 7)) {
	  copy(t1, curr);
	  shrink(t1, i-6, 7);
	  if (!found || cmp(t1, t2)) {
	    insert(&heap, t1);
	    found = 1;
	    copy(t2, t1);
	  }
	  okay = 0;
	}
      }
    } 
    if (!okay) {
      delete(&heap, curr);
    }
  }
  free_heap(&heap);
  write_num(curr);
}


int main(void)
{
  int n;
  Bignum x;

  scanf("%d", &n);
  while (n-- > 0) {
    read_num(x);
    do_case(x);
  }

  return 0;
}
