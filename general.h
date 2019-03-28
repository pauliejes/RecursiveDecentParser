#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include "symTable.h"

#ifndef _GENERAL_H_
#define _GENERAL_H_
/* Global declarations */
/* Variables */
extern char lexeme [100];
extern char nextChar;
extern int lexLen;
extern Symbol_table symbolTable;

/* Character classes */
extern int charClass;
#define LETTER 0
#define DIGIT 1
#define OPERATOR 99
#define NEWLINE_CLASS 100

/* Token codes */
extern int token;
extern int nextToken;

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define POW_OP 26
#define LEFT_PAREN 27
#define RIGHT_PAREN 28
#define QUIT 29
#define DUMP 30
#define NEWLINE 31


#endif