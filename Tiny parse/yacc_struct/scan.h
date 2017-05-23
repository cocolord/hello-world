#ifndef _SCAN_H_
#define _SCAN_H_

#include "y.tab.h"
#define ENDFILE 0
#define MAXTOKENLEN 40
typedef int TokenType;

#define FALSE 0
#define TRUE 1

extern int lineno;

#define MAXTOKENLEN 40
char tokenString[MAXTOKENLEN + 1];

TokenType getToken(void);
void printToken(TokenType, const char*);

#endif
