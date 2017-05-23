%{
#include "scan.h"
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%s COMMENT

%%

<INITIAL>\{              {BEGIN COMMENT;}
<COMMENT>\} 		       {BEGIN INITIAL;}
<COMMENT>.               {/* skip COMMENT */}
<INITIAL>"if"            {return IF;}
<INITIAL>"then"          {return THEN;}
<INITIAL>"else"          {return ELSE;}
<INITIAL>"end"           {return END;}
<INITIAL>"repeat"        {return REPEAT;}
<INITIAL>"until"         {return UNTIL;}
<INITIAL>"read"          {return READ;}
<INITIAL>"write"         {return WRITE;}
<INITIAL>":="            {return ASSIGN;}
<INITIAL>"="             {return EQ;}
<INITIAL>"<"             {return LT;}
<INITIAL>"+"             {return PLUS;}
<INITIAL>"-"             {return MINUS;}
<INITIAL>"*"             {return TIMES;}
<INITIAL>"/"             {return OVER;}
<INITIAL>"("             {return LPAREN;}
<INITIAL>")"             {return RPAREN;}
<INITIAL>";"             {return SEMI;}
<INITIAL>{number}        {return NUM;}
<INITIAL>{identifier}    {return ID;}
{newline}       		 {lineno++;}
{whitespace}    		 {/* skip whitespace */}
<INITIAL>.               {return ERROR;}

%%

int yywrap(){return 1;}

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  return currentToken;
}

void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case IF:
    case THEN:
    case ELSE:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
      printf(
         "reserved word: %s\n",tokenString);
      break;
    case ASSIGN: printf(":=\n"); break;
    case LT: printf("<\n"); break;
    case EQ: printf("=\n"); break;
    case LPAREN: printf("(\n"); break;
    case RPAREN: printf(")\n"); break;
    case SEMI: printf(";\n"); break;
    case PLUS: printf("+\n"); break;
    case MINUS: printf("-\n"); break;
    case TIMES: printf("*\n"); break;
    case OVER: printf("/\n"); break;
    case ENDFILE: printf("EOF\n"); break;
    case NUM:
      printf(
          "NUM, val= %s\n",tokenString);
      break;
    case ID:
      printf(
          "ID, name= %s\n",tokenString);
      break;
    case ERROR:
      printf(
          "ERROR: %s\n",tokenString);
      break;
    default: /* should never happen */
      printf("Unknown token: %d\n",token);
  }
}