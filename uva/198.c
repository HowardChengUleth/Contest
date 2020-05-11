/*

1995-96 ACM International Collegiate Programming Contest
Southwestern European Regional Contest
ETH Zurich, Switzerland
December 9, 1995


Problem: Calculator

Idea and first implementation:	Hans Domjan, Contest Secretary
Implementation:					Manuel Bleichenbacher, Head Judge

Source file: calculator.c / calculator.p
Input file: calculator.in
Output file: calculator.out

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>


typedef enum {
  FALSE = 0,
  TRUE = 1
} bool;

typedef enum {
  tEOF, tCR,
  tAssign,
  tPRINT, tRESET,
  tOpenPar, tClosePar,
  tPlus, tMinus,
  tTimes,
  tVar, tNumber,
  tError
} TokenEnum;

typedef struct {
  TokenEnum	token;
  char*		var;
  int			number;
} Token;

typedef struct Node {
  TokenEnum		token;
  struct Node*	left;
  struct Node*	right;
  int				number;
  char*			var;
} Node;

typedef struct {
  char*		name;
  Node*		node;
  bool		visited;
} Symbol;


#define SYMTAB_MAX	2000
Symbol	gSymtab[SYMTAB_MAX];
int		gSymtabCnt = 0;

Token	gToken;

FILE*	fout;


void next_token();

Node* new_Node(TokenEnum tok);
int find_symbol(char* name);
int evaluate(Node* node, bool* undef);

void File();
#define Line MyLine
void Line();
void Assignment();
void Print();
void Reset();
void Expression(Node** node);
void Term(Node** node);
void Factor(Node** node);
void Integer(Node** node);


void next_token()
{
  static FILE*	fin;
  static int		nextchar = 0;
  static char		buf[1024];
	
  int		i;
	
  if (nextchar == EOF) {
    gToken.token = tEOF;
    return;
  }
		
  if (fin == NULL) {
    fin = stdin;
    assert(fin != 0);
    nextchar = fgetc(fin);
  }
	
  while (nextchar != EOF && nextchar != '\n'
	 && isspace(nextchar))
    nextchar = fgetc(fin);
	
  switch( nextchar ) {
	
  case EOF:
    fclose(fin);
    gToken.token = tEOF;
    return;
	
  case ':':
    nextchar = fgetc(fin);
    if (nextchar == '=')
      gToken.token = tAssign;
    else
      gToken.token = tError;
    break;
	
  case '(':	gToken.token = tOpenPar;	break;
  case ')':	gToken.token = tClosePar;	break;
  case '+':	gToken.token = tPlus;		break;
  case '-':	gToken.token = tMinus;		break;
  case '*':	gToken.token = tTimes;		break;
  case '\n':	gToken.token = tCR;			break;
	
  default:
    if ( isalnum(nextchar) ) {
      buf[0] = nextchar; i=1;
      while ( isalnum(nextchar = fgetc(fin)) )
	buf[i++] = nextchar;
      buf[i++] = '\0';
			
      if ( isalpha(buf[0]) ) {	/* variable */
	if (strcmp(buf, "PRINT") == 0)
	  gToken.token = tPRINT;
	else if (strcmp(buf, "RESET") == 0)
	  gToken.token = tRESET;
	else {
	  gToken.var = (char*) malloc(i);
	  strcpy( gToken.var, buf );
	  gToken.token = tVar;
	}
				
      } else {	/* number */
	sscanf(buf, "%d", &gToken.number);
	gToken.token = tNumber;
      }
      return;
    }
    gToken.token = tError;
  }
  nextchar = fgetc(fin);
}

Node* new_Node(TokenEnum tok)
{
  Node* node;
	
  node = (Node*) malloc( sizeof(Node) );
  node->token = tok;
  node->left = NULL;
  node->right = NULL;
  node->number = 0;
  node->var = NULL;
  return node;
}

int find_symbol(char* name)
{
  int i;
	
  for (i=0; i < gSymtabCnt; i++)
    if ( strcmp(name, gSymtab[i].name) == 0 )
      return i;
	
  return -1;
}


int evaluate(Node* node, bool* undef)
{
  int n;
	
  if (node->token == tNumber)
    return node->number;
  if (node->token == tTimes)
    return evaluate(node->left, undef)
      * evaluate(node->right, undef);
  if (node->token == tPlus)
    return evaluate(node->left, undef)
      + evaluate(node->right, undef);
  if (node->token == tMinus)
    return evaluate(node->left, undef)
      - evaluate(node->right, undef);
  if (node->token == tVar) {
    n = find_symbol(node->var);
    if (n == -1) {		/* not yet defined */
      *undef = TRUE;
      return 0;
    }
    if (gSymtab[n].visited) {	/* cycle in expression */
      *undef = TRUE;
      return 0;
    }
    gSymtab[n].visited = TRUE;
    return evaluate(gSymtab[n].node, undef);
  }
  assert(FALSE);
  return 0;
}


void File()
{
  next_token();
  while (gToken.token != tEOF)
    Line();
}
	
void Line()
{
  if (gToken.token == tVar)
    Assignment();
  else if (gToken.token == tPRINT)
    Print();
  else if (gToken.token == tRESET)
    Reset();
	
  assert(gToken.token == tCR);
  next_token();
}
	
void Assignment()
{
  Node* node;
  int n;
  char* var;
	
  assert(gToken.token == tVar);
  var = gToken.var;
  next_token();
  assert(gToken.token == tAssign);
  next_token();
  Expression(&node);

  n = find_symbol(var);
  if (n == -1) {
    n = gSymtabCnt;
    gSymtabCnt++;
  }
	
  gSymtab[n].node = node;
  gSymtab[n].name = var;
}
	
void Print()
{
  int i, n;
  bool undef = FALSE;
	
  assert(gToken.token == tPRINT);
  next_token();
  assert(gToken.token == tVar);
  next_token();
	
  for (i=0; i<gSymtabCnt; i++)
    gSymtab[i].visited = FALSE;
	
  n = find_symbol(gToken.var);
  if (n == -1)
    undef = TRUE;
  else {
    gSymtab[n].visited = TRUE;
    i = evaluate(gSymtab[n].node, &undef);
  }
	
  if (undef)
    fprintf(fout, "UNDEF\n");
  else
    fprintf(fout, "%d\n", i);
}

void Reset()
{
  assert(gToken.token == tRESET);
  next_token();
  gSymtabCnt = 0;
}

void Expression(Node** node)
{
  Node *left, *right;
  TokenEnum	op;
	
  Term(&left);
  while ( gToken.token == tPlus ||
	  gToken.token == tMinus ) {
    op = gToken.token;
    next_token();
    Term(&right);
    *node = new_Node(op);
    (*node)->left = left;
    (*node)->right = right;
    left = *node;
  }
  *node = left;
}

void Term(Node** node)
{
  Node *left, *right;
	
  Factor(&left);
  while (gToken.token == tTimes) {
    next_token();
    Term(&right);
    *node = new_Node(tTimes);
    (*node)->left = left;
    (*node)->right = right;
    left = *node;
  }
  *node = left;
}

void Factor(Node** node)
{
  if (gToken.token == tNumber ||
      gToken.token == tMinus)
    Integer(node);
  else if (gToken.token == tVar) {
    *node = new_Node(tVar);
    (*node)->var = gToken.var;
    next_token();
  } else {
    assert(gToken.token == tOpenPar);
    next_token();
    Expression(node);
    assert(gToken.token == tClosePar);
    next_token();
  }
}

void Integer(Node** node)
{
  if (gToken.token == tMinus) {
    next_token();
    assert(gToken.token == tNumber);
    *node = new_Node(tNumber);
    (*node)->number = -gToken.number;
    next_token();
  } else if (gToken.token == tNumber) {
    *node = new_Node(tNumber);
    (*node)->number = gToken.number;
    next_token();
  } else
    assert(FALSE);
}
	

int main(int argc, char* argv[])
{
  fout = stdout;
  assert (fout != 0);
  File();

  return 0;
}

