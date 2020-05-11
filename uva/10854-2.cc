//@BEGIN_OF_SOURCE_CODE
//Authored by Zac Friggstad on June 2, 2005
//@JUDGE_ID: 34458JY 10854 C "Recursive Descent"

#include <stdio.h>

char token[11];

long long int block()
{
   unsigned long long int tmp;
   
   switch (token[0])
   {
      case 'S':
	 scanf("%s", token);
	 return block();
      case 'I':
	 scanf("%s", token);
	 tmp = block();
	 scanf("%s", token);
	 tmp += block();
	 scanf("%s", token);
	 return tmp * block();
      default:
	 return 1;
   }
}

int main()
{
   int num;
   num = scanf("%s", token);
   
   while(scanf("%s", token) != -1)
      printf("%lld\n", block());
   
   return 0;
}

//@END_OF_SOURCE_CODE
//judge@uva.es

