#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 1 "tiny.y"

#include "y.tab.h"
#include "scan.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAXRESERVED 8

/*定义语法树节点*/
typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type; 
   } TreeNode;

#define YYSTYPE TreeNode *

/*函数声明*/
TreeNode * newStmtNode(StmtKind);
TreeNode * newExpNode(ExpKind);
char * copyString( char * );
TreeNode * parse(void);
void printTree( TreeNode * );

/*全局变量声明*/
int lineno;

char * savedName; 
int savedLineNo;  
TreeNode * savedTree;
#line 67 "y.tab.c"

#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define IF 257
#define THEN 258
#define ELSE 259
#define END 260
#define REPEAT 261
#define UNTIL 262
#define READ 263
#define WRITE 264
#define ID 265
#define NUM 266
#define ASSIGN 267
#define EQ 268
#define LT 269
#define PLUS 270
#define MINUS 271
#define TIMES 272
#define OVER 273
#define LPAREN 274
#define RPAREN 275
#define SEMI 276
#define ERROR 277
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    2,    2,    2,    2,    3,
    3,    4,    9,    5,    6,    7,    8,    8,    8,   10,
   10,   10,   11,   11,   11,   12,   12,   12,   12,
};
static const short yylen[] = {                            2,
    1,    3,    1,    1,    1,    1,    1,    1,    1,    5,
    7,    4,    0,    4,    2,    2,    3,    3,    1,    3,
    3,    1,    3,    3,    1,    3,    1,    1,    1,
};
static const short yydefred[] = {                         0,
    9,    0,    0,    0,    0,   13,    0,    0,    3,    4,
    5,    6,    7,    8,   29,   28,   27,    0,    0,    0,
    0,   25,    0,   15,   16,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    2,   26,    0,
    0,    0,    0,    0,   23,   24,   12,   14,    0,   10,
    0,   11,
};
static const short yydgoto[] = {                          7,
    8,    9,   10,   11,   12,   13,   14,   19,   26,   20,
   21,   22,
};
static const short yysindex[] = {                      -232,
    0, -252, -232, -250, -252,    0,    0, -264,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -252, -241, -260,
 -245,    0, -257,    0,    0, -246, -232, -237, -232, -252,
 -252, -252, -252, -252, -252, -252, -252,    0,    0, -253,
 -234, -234, -245, -245,    0,    0,    0,    0, -232,    0,
 -258,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,   30,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   44,
    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   63,   68,   20,   39,    0,    0,    0,    0,    0,    0,
    0,    0,
};
static const short yygindex[] = {                         0,
   -3,   18,    0,    0,    0,    0,    0,   -2,    0,   10,
   15,    8,
};
#define YYTABLESIZE 344
static const short yytable[] = {                         23,
   22,   52,   25,   15,   36,   49,   50,   30,   31,   32,
   33,   27,   16,   17,   24,   28,   29,   27,   27,   20,
   37,   18,   27,    1,    2,   40,   34,   35,    3,    1,
    4,    5,    6,   47,   48,   32,   33,   39,   21,   41,
   42,   45,   46,   19,   38,   51,   43,   44,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   18,    0,    0,    0,    0,   17,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   22,   22,
   22,    0,   22,    0,    0,    0,    0,    0,   22,   22,
   22,   22,    0,    0,    0,   22,   22,   20,   20,   20,
    0,   20,    0,    0,    0,    0,    0,   20,   20,   20,
   20,    0,    0,    0,   20,   20,   21,   21,   21,    0,
   21,   19,   19,   19,    0,   19,   21,   21,   21,   21,
    0,    0,    0,   21,   21,    0,    0,    0,   19,   19,
   18,   18,   18,    0,   18,   17,   17,   17,    0,   17,
    0,    0,    0,    0,    0,    0,    0,   18,   18,    0,
    0,    0,   17,   17,
};
static const short yycheck[] = {                          3,
    0,  260,    5,  256,  262,  259,  260,  268,  269,  270,
  271,  276,  265,  266,  265,   18,  258,  276,  276,    0,
  267,  274,  276,  256,  257,   29,  272,  273,  261,    0,
  263,  264,  265,   36,   37,  270,  271,  275,    0,   30,
   31,   34,   35,    0,   27,   49,   32,   33,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,    0,   -1,   -1,   -1,   -1,    0,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  258,  259,
  260,   -1,  262,   -1,   -1,   -1,   -1,   -1,  268,  269,
  270,  271,   -1,   -1,   -1,  275,  276,  258,  259,  260,
   -1,  262,   -1,   -1,   -1,   -1,   -1,  268,  269,  270,
  271,   -1,   -1,   -1,  275,  276,  258,  259,  260,   -1,
  262,  258,  259,  260,   -1,  262,  268,  269,  270,  271,
   -1,   -1,   -1,  275,  276,   -1,   -1,   -1,  275,  276,
  258,  259,  260,   -1,  262,  258,  259,  260,   -1,  262,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  275,  276,   -1,
   -1,   -1,  275,  276,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 277
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"IF","THEN","ELSE","END","REPEAT",
"UNTIL","READ","WRITE","ID","NUM","ASSIGN","EQ","LT","PLUS","MINUS","TIMES",
"OVER","LPAREN","RPAREN","SEMI","ERROR",
};
static const char *yyrule[] = {
"$accept : program",
"program : stmt_seq",
"stmt_seq : stmt_seq SEMI stmt",
"stmt_seq : stmt",
"stmt : if_stmt",
"stmt : repeat_stmt",
"stmt : assign_stmt",
"stmt : read_stmt",
"stmt : write_stmt",
"stmt : error",
"if_stmt : IF exp THEN stmt_seq END",
"if_stmt : IF exp THEN stmt_seq ELSE stmt_seq END",
"repeat_stmt : REPEAT stmt_seq UNTIL exp",
"$$1 :",
"assign_stmt : ID $$1 ASSIGN exp",
"read_stmt : READ ID",
"write_stmt : WRITE exp",
"exp : simple_exp LT simple_exp",
"exp : simple_exp EQ simple_exp",
"exp : simple_exp",
"simple_exp : simple_exp PLUS term",
"simple_exp : simple_exp MINUS term",
"simple_exp : term",
"term : term TIMES factor",
"term : term OVER factor",
"term : factor",
"factor : LPAREN exp RPAREN",
"factor : NUM",
"factor : ID",
"factor : error",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 171 "tiny.y"


int yyerror(char * message)
{ printf("Syntax error at line %d: %s\n",lineno,message);
  printf("Current token: ");
  printToken(yychar,tokenString);
  return 0;
}

static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

static indentno = 0;

#define INDENT indentno+=2
#define UNINDENT indentno-=2

static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    printf(" ");
}

void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          printf("If\n");
          break;
        case RepeatK:
          printf("Repeat\n");
          break;
        case AssignK:
          printf("Assign to: %s\n",tree->attr.name);
          break;
        case ReadK:
          printf("Read: %s\n",tree->attr.name);
          break;
        case WriteK:
          printf("Write\n");
          break;
        default:
          printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          printf("Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          printf("Const: %d\n",tree->attr.val);
          break;
        case IdK:
          printf("Id: %s\n",tree->attr.name);
          break;
        default:
          printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else printf("Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}

main(int argc, char * argv[])
{
	lineno = 0;
	TreeNode * syntaxTree;
	syntaxTree = parse();
	printTree(syntaxTree);
	return 0;
}


#line 463 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 58 "tiny.y"
	{ savedTree = yystack.l_mark[0];}
break;
case 2:
#line 61 "tiny.y"
	{ YYSTYPE t = yystack.l_mark[-2];
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = yystack.l_mark[0];
                     yyval = yystack.l_mark[-2]; }
                     else yyval = yystack.l_mark[0];
                 }
break;
case 3:
#line 69 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 4:
#line 71 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 5:
#line 72 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 6:
#line 73 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 7:
#line 74 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 8:
#line 75 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 9:
#line 76 "tiny.y"
	{ yyval = NULL; }
break;
case 10:
#line 79 "tiny.y"
	{ yyval = newStmtNode(IfK);
                   yyval->child[0] = yystack.l_mark[-3];
                   yyval->child[1] = yystack.l_mark[-1];
                 }
break;
case 11:
#line 84 "tiny.y"
	{ yyval = newStmtNode(IfK);
                   yyval->child[0] = yystack.l_mark[-5];
                   yyval->child[1] = yystack.l_mark[-3];
                   yyval->child[2] = yystack.l_mark[-1];
                 }
break;
case 12:
#line 91 "tiny.y"
	{ yyval = newStmtNode(RepeatK);
                   yyval->child[0] = yystack.l_mark[-2];
                   yyval->child[1] = yystack.l_mark[0];
                 }
break;
case 13:
#line 96 "tiny.y"
	{ savedName = copyString(tokenString);
                   savedLineNo = lineno; }
break;
case 14:
#line 99 "tiny.y"
	{ yyval = newStmtNode(AssignK);
                   yyval->child[0] = yystack.l_mark[0];
                   yyval->attr.name = savedName;
                   yyval->lineno = savedLineNo;
                 }
break;
case 15:
#line 106 "tiny.y"
	{ yyval = newStmtNode(ReadK);
                   yyval->attr.name =
                     copyString(tokenString);
                 }
break;
case 16:
#line 112 "tiny.y"
	{ yyval = newStmtNode(WriteK);
                   yyval->child[0] = yystack.l_mark[0];
                 }
break;
case 17:
#line 117 "tiny.y"
	{ yyval = newExpNode(OpK);
                   yyval->child[0] = yystack.l_mark[-2];
                   yyval->child[1] = yystack.l_mark[0];
                   yyval->attr.op = LT;
                 }
break;
case 18:
#line 123 "tiny.y"
	{ yyval = newExpNode(OpK);
                   yyval->child[0] = yystack.l_mark[-2];
                   yyval->child[1] = yystack.l_mark[0];
                   yyval->attr.op = EQ;
                 }
break;
case 19:
#line 128 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 20:
#line 131 "tiny.y"
	{ yyval = newExpNode(OpK);
                   yyval->child[0] = yystack.l_mark[-2];
                   yyval->child[1] = yystack.l_mark[0];
                   yyval->attr.op = PLUS;
                 }
break;
case 21:
#line 137 "tiny.y"
	{ yyval = newExpNode(OpK);
                   yyval->child[0] = yystack.l_mark[-2];
                   yyval->child[1] = yystack.l_mark[0];
                   yyval->attr.op = MINUS;
                 }
break;
case 22:
#line 142 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 23:
#line 145 "tiny.y"
	{ yyval = newExpNode(OpK);
                   yyval->child[0] = yystack.l_mark[-2];
                   yyval->child[1] = yystack.l_mark[0];
                   yyval->attr.op = TIMES;
                 }
break;
case 24:
#line 151 "tiny.y"
	{ yyval = newExpNode(OpK);
                   yyval->child[0] = yystack.l_mark[-2];
                   yyval->child[1] = yystack.l_mark[0];
                   yyval->attr.op = OVER;
                 }
break;
case 25:
#line 156 "tiny.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 26:
#line 159 "tiny.y"
	{ yyval = yystack.l_mark[-1]; }
break;
case 27:
#line 161 "tiny.y"
	{ yyval = newExpNode(ConstK);
                   yyval->attr.val = atoi(tokenString);
                 }
break;
case 28:
#line 164 "tiny.y"
	{ yyval = newExpNode(IdK);
                   yyval->attr.name =
                         copyString(tokenString);
                 }
break;
case 29:
#line 168 "tiny.y"
	{ yyval = NULL; }
break;
#line 841 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
