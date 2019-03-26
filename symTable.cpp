/*
  Calculator.cpp - A simple arithmetic interpreter.
  Name: R. Shore
  Class: CSC-4510

  The program demonstrates two main components of
  an interpreter/compiler.
  1) A lexical analyzer to scan the input for
     LETTERs, DIGITs, or OPERATORs

     An IDENT consist of a LETTER followed by
     a LETTER or DIGIT (max 99 characters)

     AN INT_LIT consists of a sequence of DIGITs
     (max 99 digits).

     An OPERATOR =, +, -, *, /, (, )
     lexeme[] holds the item read from source
     nextToken holds the type

  2) A recursive descent parser
     The Grammar - EBNF description

     <expr> → <term> {(+ | -) <term>}
     <term> → <factor> {(* | /) <factor>}
     <factor> → id | int_constant | ( <expr>  )

     NOTE: the recusive descent starts at <expr>
 */

#include<iostream>
#include<stdio.h>
#include"general.h"
#include"lex.h"
#include"topDownParser.h"



using namespace std;


/******************************************************/
/* main driver */
int main(void) {
   /* Open the input data file and process its contents */
   // if ((in_fp = fopen("front.in", "r")) == NULL)
   //    printf("ERROR - cannot open front.in \n");
   // else {
  getChar();
  do {
    lex();
    expr();
  } while (nextToken != EOF);

   //}
}
