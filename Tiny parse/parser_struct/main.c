/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
int Error=FALSE;

main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  strcpy(pgm,argv[1]) ;
  source = fopen(pgm,"r");
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nTINY COMPILATION: %s\n",pgm); 
//  while (getToken()!=ENDFILE);
  syntaxTree = parse();

   fprintf(listing,"\nSyntax tree:\n");
   printTree(syntaxTree);
  fclose(source);
  return 0;
}

