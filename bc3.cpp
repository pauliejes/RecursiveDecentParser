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
#include<ctype.h>
using namespace std;

/* Global declarations */
/* Variables */
char lexeme [100];  
char nextChar;     
int lexLen;
FILE *in_fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

void expr();
void term();
void factor();
void error(const char *);

/* Character classes */
int charClass;
#define LETTER 0
#define DIGIT 1
#define OPERATOR 99

/* Token codes */
int token;
int nextToken;
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/******************************************************/
/* main driver */
int main(void) {
   /* Open the input data file and process its contents */
   if ((in_fp = fopen("front.in", "r")) == NULL)
      printf("ERROR - cannot open front.in \n");
   else {
      getChar();
      do {
        lex();
        expr();
      } while (nextToken != EOF);
 
   }
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 and return the token */
int lookup(char ch) 
{
   switch (ch) {
      case '(':
                addChar();
                nextToken = LEFT_PAREN;
                break;
      case ')':
                addChar();
                nextToken = RIGHT_PAREN;
                break;
      case '+':
                addChar();
                nextToken = ADD_OP;
                break;
      case '-':
                addChar();
                nextToken = SUB_OP;
                break;
      case '*':
                addChar();
                nextToken = MULT_OP;
                break;
      case '/':
                addChar();
                nextToken = DIV_OP;
                break;
      default:
                addChar();
                nextToken = EOF;
                break;
 
   }
   return nextToken;
}


/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() 
{
   if (lexLen <= 98) {
      lexeme[lexLen++] = nextChar;
      lexeme[lexLen] = '\0';
   } else
      printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
   input and determine its character class 
   Two globals are set
   nextChar - the next character scanned from the input.
   charClass - the category of the character - LETTER, DiGIT, OPERATOR
*/
void getChar() 
{
   if ((nextChar = getc(in_fp)) != EOF) {
      if (isalpha(nextChar))
         charClass = LETTER;
      else if (isdigit(nextChar))
         charClass = DIGIT;
      else 
         charClass = OPERATOR;
   } else
      charClass = EOF;
}
/*****************************************************/
/* getNonBlank - remove white space characters.
   call getChar until it returns a non-whitespace 
   character.
   nextChar will be set to the next non-whitespace char.
*/
void getNonBlank() 
{
   while (isspace(nextChar))
      getChar();
}


/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex() 
{
   lexLen = 0;
   getNonBlank();
   switch (charClass) {
      /* Parse identifiers - once you find the first
         letter, read and add char by char to lexeme. */
      case LETTER:
                   addChar();
                   getChar();
                   /* After first char, you may use either char or digits */ 
                   while (charClass == LETTER || charClass == DIGIT) {
                      addChar();
                      getChar();
                   }
                   nextToken = IDENT;
                   break;

      /* Parse integer literals - once you find the first
         digit, read and add digits to lexeme. */
      case DIGIT:
                   addChar();
                   getChar();
                   while (charClass == DIGIT) {
                      addChar();
                      getChar();
                   }
                   nextToken = INT_LIT;
                   break;

      /* Parentheses and operators */
      case OPERATOR:
                   /* Call lookup to identify the type of operator */
                   lookup(nextChar);
                   getChar();
                   break;
      /* EOF */
      case EOF:
                   nextToken = EOF;
                   lexeme[0] = 'E';
                   lexeme[1] = 'O';
                   lexeme[2] = 'F';
                   lexeme[3] = '\0';
                   break;
                   
   } /* End of switch */


   printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
   return nextToken;
} 


/* expr
   Parses strings in the language generated by the rule:
   <expr> -> <term> {(+ | -) <term>}
 */
void expr() 
{
   printf("Enter <expr>\n");

   /* Parse the first term */
   term();

   /* As long as the next token is + or -, get
      the next token and parse the next term */
   while (nextToken == ADD_OP || nextToken == SUB_OP) {
      lex();
      term();
   }
   printf("Exit <expr>\n");

} /* End of function expr */


/* term
 *  Parses strings in the language generated by the rule:
 *  <term> -> <factor> {(* | /) <factor>)
 */
void term() 
{
   printf("Enter <term>\n");
   /* Parse the first factor */
   factor();
   /* As long as the next token is * or /, get the
      next token and parse the next factor */
   while (nextToken == MULT_OP || nextToken == DIV_OP) {
      lex();
      factor();
   }
   printf("Exit <term>\n");

} /* End of function term */


/* factor
 * Parses strings in the language generated by the rule:
 * 
 *   <factor> -> id | int_constant | ( <expr  )
 *
 */
void factor() 
{
   printf("Enter <factor>\n");
   /* Determine which RHS */
   if (nextToken == IDENT || nextToken == INT_LIT)
      /* Get the next token */
      lex();

   /* If the RHS is ( <expr> ), call lex to pass over the left 
      parenthesis, call expr and check for the right parenthesis */
   else if (nextToken == LEFT_PAREN) {
         lex();
         expr();
         if (nextToken == RIGHT_PAREN)
            lex();
         else
            error("Right without left paren");
   } else {
   /* It was not an id, an integer literal, or a left
       parenthesis */
       error("expected an id, integer, or a left paren");
   } /* End of else */
   printf("Exit <factor>\n");;
}/* End of function factor */

void error(const char *message)
{
   printf("Error: %s\n",message);
}
