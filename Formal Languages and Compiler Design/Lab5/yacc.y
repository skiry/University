%{
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1

#define TIP_INT 1
#define TIP_REAL 2
#define TIP_CAR 3

double stiva[20];
int sp;

void push(double x)
{ stiva[sp++]=x; }

double pop()
{ return stiva[--sp]; }

%}

%union {
  	int l_val;
	char *p_val;
}

%token BEGINN
%token CONST
%token PRINT
%token READ
%token THEN
%token VAR

%token identifier
%token constant
%token startprogram
%token endprogram
%token ASSIGN
%token GT
%token LT
%token GE
%token LE
%token EQ
%token DIFF
%token POW
%token MUL
%token DIV
%token ADD
%token SUB
%token CBO
%token CBC
%token CPO
%token CPC
%token OPO
%token OPC
%token DD
%token COMMA
%token IF
%token ELSE
%token read
%token write
%token true
%token false
%token declare
%token and
%token or
%token DO
%token WHILE
%token integer
%token CHAR
%token string
%token array
%token mainf
%token give


%token ID
%token <p_val> CONST_INT
%token <p_val> CONST_REAL
%token <p_val> CONST_CAR
%token CONST_SIR

%token INTEGER
%token REAL

%token ATRIB
%token NE

%left '+' '-'
%left DIV MOD '*' '/'
%left OR
%left AND
%left NOT

%start CODE


%%
CODE: startprogram PROGRAM END
	{ 
		printf("Started\n"); 
	};
END: endprogram 
	{ 
		printf("Reached end of program\n"); 
	};
PROGRAM: MAIN 
	{
		printf("Main function\n"); 
	};
FUNCTIONS: declare FUNCTION FUNCTIONS | epsilon ;
MAIN: declare MAIN_FUNCTION ;
MAIN_FUNCTION: mainf OPO PARAMETERS OPC DD CBO BODY CBC ;
FUNCTION: identifier OPO PARAMETERS OPC DD CBO BODY CBC ;
PARAMETERS: identifier PARAMETERS_TAIL | epsilon ;
PARAMETERS_TAIL: COMMA PARAMETERS | DEFAULT_PARAMETERS | epsilon ;
DEFAULT_PARAMETERS: ASSIGN EXPRESSION ;

BODY: VARIABLE_DECL BODY2 | ASSIGNMENT BODY2 | CONDITIONAL BODY2 | LOOP BODY2 | IO_STMT BODY2 | give ANY_VALUE BODY2 ;
BODY2: BODY | epsilon ;
ASSIGNMENT: identifier ASSIGN EXPRESSION ;

VARIABLE_DECL: INTEGER_DECL ;
INTEGER_DECL: integer identifier INTEGER_HELPER ;
INTEGER_HELPER: ASSIGN ANY_VALUE | epsilon;
CHAR_DECL: CHAR identifier | CHAR identifier ASSIGN ANY_VALUE ;
STRING_DECL: string identifier | string identifier ASSIGN ANY_VALUE ;

ARRAY_DECL: array identifier ARRAY_HELPER ;
ARRAY_HELPER: ASSIGN ARRAY_IMPL | epsilon ;
ARRAY_IMPL: CPO ELEMS CPC ;
ELEMS: ANY_VALUE ELEMS2 | ELEMS2 ;
ELEMS2: COMMA ELEMS | epsilon ;

EXPRESSION : B A | FUNCTION_CALL ;
FUNCTION_CALL: identifier OPO PARAMETERS OPC ;
A : OPERATION B A | epsilon ;
C : OPERATION D C | epsilon ;
B : D C ;
D : OPO EXPRESSION OPC | ANY_VALUE ;

CONDITIONAL: IF COMPARISON DD CBO BODY CBC ELIFS;
ELIFS: ELIF | epsilon ;
ELIF: ELSE IF COMPARISON DD CBO BODY CBC ;
COMPARISON: EXPRESSION RELATION EXPRESSION  | COMPARISON LOGICAL COMPARISON ;
LOGICAL: and | or ;
RELATION: GT | LT | GE | LE | EQ | DIFF ;
OPERATION: POW | MUL | DIV | SIGN ;
SIGN: ADD | SUB ;

IO_STMT: read OPO identifier COMMA ANY_VALUE OPC | write OPO ANY_VALUE COMMA ANY_VALUE OPC ;

LOOP: WHILE WHILE_CONDITION DO DD CBO BODY CBC | DO DD CBO BODY CBC WHILE WHILE_CONDITION ;
WHILE_CONDITION: COMPARISON | BOOLEAN ;

ANY_VALUE: identifier | constant ;
BOOLEAN: true | false ;
epsilon: ;

%%

yyerror(char *s)
{
  printf("%s lala\n", s);
}


extern FILE *yyin;

main(int argc, char **argv)
{
  if(argc>1) yyin = fopen(argv[1], "r");
  if((argc>2)&&(!strcmp(argv[2],"-d"))) yydebug = 1;
  if(!yyparse()) fprintf(stderr,"\tO.K.\n");
}
