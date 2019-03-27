#include<iostream>
#include<stdio.h>
#include<ctype.h>

#ifndef _TOP_DOWN_PARSER_H_
#define _TOP_DOWN_PARSER_H_
/* Function declarations */
void expr();
void term();
void factor();
void error(const char *);

#endif