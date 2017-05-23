/****************************************************/
/* File: parse.c                                    */
/* The parser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode * stmt_sequence(void);
static TreeNode * statement(void);
static TreeNode * if_stmt(void);
static TreeNode * repeat_stmt(void);
static TreeNode * assign_stmt(void);
static TreeNode * read_stmt(void);
static TreeNode * write_stmt(void);
static TreeNode * exp(void);
static TreeNode * simple_exp(void);
static TreeNode * term(void);
static TreeNode * factor(void);

static void syntaxError(char * message)
{ fprintf(listing,"\n>>> ");
  fprintf(listing,"Syntax error at line %d: %s",lineno,message);
  Error = TRUE;
}

static void match(TokenType expected)
{ if (token == expected) token = getToken();
  else {
    syntaxError("unexpected token -> ");
    printToken(token,tokenString);
    fprintf(listing,"      ");
  }
}

TreeNode * stmt_sequence(void)
{ TreeNode * t = statement();
  
  TreeNode * p = t;
  
  while ((token!=ENDFILE) && (token!=END) &&
         (token!=ELSE) && (token!=UNTIL))
  { TreeNode * q;
    match(SEMI);
    q = statement();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else // now p cannot be NULL either 
      { p->sibling = q;
        p = q;
      }
    }
  }
  
  return t;
}

TreeNode * statement(void)
{ TreeNode * t = NULL;

  switch (token) {
    case IF : t = if_stmt(); break;
    case REPEAT : t = repeat_stmt(); break;
    case ID : t = assign_stmt(); break;
    case READ : t = read_stmt(); break;
    case WRITE : t = write_stmt(); break;
    default : syntaxError("unexpected token -> ");
              printToken(token,tokenString);
              token = getToken();
              break;
  } //end case 
  
  return t;
}

TreeNode * if_stmt(void)
{ TreeNode * t = newStmtNode(IfK);
/*
 insert your code 
  */
  return t;
}

TreeNode * repeat_stmt(void)
{ TreeNode * t = newStmtNode(RepeatK);
/*
 insert your code 
  */
  return t;
}

TreeNode * assign_stmt(void)
{ TreeNode * t = newStmtNode(AssignK);
/*
  insert your code 
  */
  return t;
}

TreeNode * read_stmt(void)
{ TreeNode * t = newStmtNode(ReadK);
/*
  insert your code
  */
  return t;
}

TreeNode * write_stmt(void)
{ TreeNode * t = newStmtNode(WriteK);
/*
  insert your code 
  */
  return t;
}

TreeNode * exp(void)
{ TreeNode * t = simple_exp();
/*
  insert your code 
  */
  return t;
}

TreeNode * simple_exp(void)
{ TreeNode * t = term();
/*
  insert your code 
  */
  return t;
}

TreeNode * term(void)
{ TreeNode * t = factor();
/*
  insert your code 
  */
  return t;
}

TreeNode * factor(void)
{ TreeNode * t = NULL;
/*
  insert your code 
    */
  return t;
}

/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly 
 * constructed syntax tree
 */
TreeNode * parse(void)
{ TreeNode * t;

  token = getToken();
  t = stmt_sequence();
  if (token!=ENDFILE)
    syntaxError("Code ends before file\n");
    
  return t;
}
