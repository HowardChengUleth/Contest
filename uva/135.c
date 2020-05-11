/* @JUDGE_ID: 1102NT 135 C "" */

/* Authored by Zac Friggstad on May 11, 2004 */

#include <stdio.h>

/*
 * hardcoded difference sets
 * most are from http://www.ccrwest.org/diffsets/diff_sets/baumert.html
 */

int one[] = {0};
int two[] = {0, 1};
int three[] = {1, 2, 4};
int four[] = {0, 1, 3, 9};
int six[] = {1, 5, 11, 24, 25, 27};
int eight[] = {0, 1, 6, 15, 22, 26, 45, 55};
int twelve[] = {1, 10, 11, 13, 27, 31, 68, 75, 83, 110, 115, 121};
int fourteen[] = {1, 13, 20, 21, 23, 44, 61, 72, 77, 86, 90, 116,
		  122, 169};
int eighteen[] = {0, 1, 3, 30, 37, 50, 55, 76, 98, 117, 129, 133,
		  157, 189, 199, 222, 293, 299};
int twenty[] = {0, 1, 19, 28, 96, 118, 151, 153, 176, 202, 240, 254,
		290, 296, 300, 307, 337, 361, 366, 369};
int twentyfour[] = {1, 23, 52, 90, 108, 120, 152, 163, 173, 178, 186, 223,
		    232, 272, 359, 407, 411, 431, 438, 512, 513, 515, 529, 548};
int thirty[] = {1, 24, 29, 69, 151, 167, 216, 234, 259, 263, 295, 321,
		329, 414, 488, 543, 582, 599, 645, 659, 683, 689, 696, 716,
		731, 819, 820, 822, 831, 841};
int thirtytwo[] = {0, 1, 3, 13, 101, 127, 154, 169, 204, 210, 226, 235,
		   259, 289, 297, 317, 356, 434, 474, 478, 495, 538, 570, 584,
		   589, 607, 618, 654, 749, 756, 801, 920}; 

int main()
{
   int k, n, i, j;
   int first = 1;
   int *differenceSet[33];

   /* associate possible k values with the difference sets */
   differenceSet[1] = one;
   differenceSet[2] = two;
   differenceSet[3] = three;
   differenceSet[4] = four;
   differenceSet[6] = six;
   differenceSet[8] = eight;
   differenceSet[12] = twelve;
   differenceSet[14] = fourteen;
   differenceSet[18] = eighteen;
   differenceSet[20] = twenty;
   differenceSet[24] = twentyfour;
   differenceSet[30] = thirty;
   differenceSet[32] = thirtytwo;

   while (scanf("%d", &k) == 1)
   {
      /* display blank line if this is not our firse time running this loop */
      if (!first) printf("\n");
      first = 0;

      /* calculate our modulus */
      n = k * k - k + 1;

      /*
       * display the SBIBD based on the corresponding difference set
       * since the answer must be in the range [1,n], and not [0,n), then
       * we take the residue after we display
       */
      for (i = 0; i < n; ++i)
	 for (j = 0; j < k; ++j)
	 {
            printf("%d%c", ++differenceSet[k][j], (j + 1 == k ? '\n' : ' '));
	    differenceSet[k][j] = (differenceSet[k][j] % n);
	 }
   }
   
   return 0;
}
