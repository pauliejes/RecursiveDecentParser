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
#include"symTable.h"



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
    stmt_list();
    //expr();
  } while (nextToken != EOF);

   //}
}

/* stmt_list
   Parses strings in the language generated by the rule:
   <stmt_list> -> <stmt> NEWLINE
   <stmt_list> -> <stmt_list> <stmt> NEWLINE
*/ 

void stmt_list() 
{
   printf("Enter <stmt_list>\n");
   //process statement
   cout << "       = " << stmt() << endl;
   while(nextToken == NEWLINE) {
     cout << "loop\n";
     getChar();
     lex();
     cout << "       = " << stmt() << endl;
   }
   printf("Exit <stmt_list>\n");
}


/* stmt
   Parses strings in the language generated by the rule:
   <stmt> -> IDENT = <expr>
   <stmt> -> <expr>
*/

int stmt()
{
   printf("Enter <stmt>\n");
   int return_val;
   //for assignment statements
   if(nextToken == IDENT) {
      //get the next token
      Symbol_ptr var_to_assign = symbolTable.insert(lexeme);
      return_val = expr();
      while (nextToken == ASSIGN_OP) {
         lex();
         return_val = expr();
         cout << "return_val = " << return_val << endl;
         var_to_assign->putval(return_val);
      }
   } else {
      //plane expressions
      cout << "else\n";
      return_val = expr();
      cout << "ereturn_val = " << return_val << endl;
   }
   cout << "Exit <stmt>  return: " << return_val << endl;
   return return_val;
}


/* expr
   Parses strings in the language generated by the rule:
   <expr> -> <term> {(+ | -) <term>}
 */
int expr()
{
   int return_val;
   printf("Enter <expr>\n");

   /* Parse the first term */
   return_val = term();

   /*while (nextToken == ASSIGN_OP) {
      lex();
      term();
   }*/
   /* As long as the next token is + or -, get
      the next token and parse the next term */
   while (nextToken == ADD_OP || nextToken == SUB_OP) {
      lex();
      return_val = term();
   }
   cout << "Exit <expr>  return: " << return_val << endl;  
   return return_val;

} /* End of function expr */


/* term
 *  Parses strings in the language generated by the rule:
 *  <term> -> <factor> {(* | /) <factor>)
 *  <term> -> <factor>
 *  <term> -> - <factor>
 */
int term()
{
   int return_val;
   printf("Enter <term>\n");
   /* Parse the first factor */
   if (nextToken == SUB_OP) {
      lex();
      return_val = factor();
   } else {
      return_val = factor();
   }
   /* As long as the next token is * or /, get the
      next token and parse the next factor */
   while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP || nextToken == POW_OP) {
      lex();
      return_val = factor();
   }

   cout << "Exit <term>  return: " << return_val << endl;
   return return_val;

} /* End of function term */

/* factor
 * Parses strings in the language generated by the rule:
 *
 *   <factor> -> id | int_constant | ( <expr  )
 *
 */
int factor()
{
   int return_val;
   printf("Enter <factor>\n");
   /* Determine which RHS */
   if (nextToken == IDENT) {
      cout << "ident lexeme = " << lexeme << endl;
      //look up the ident in the symbol table
      Symbol_ptr ident_node = symbolTable.insert(lexeme);
      lex();
      return_val = ident_node->getval();
   } else if (nextToken == INT_LIT){
      /* Get the next token d*/
      return_val = atoi(lexeme);
      lex();

   /* If the RHS is ( <expr> ), call lex to pass over the left
      parenthesis, call expr and check for the right parenthesis */
   } else if (nextToken == LEFT_PAREN) {
         lex();
         return_val = expr();
         if (nextToken == RIGHT_PAREN)
            lex();
         else
            error("Right without left paren");
   } else {
   /* It was not an id, an integer literal, or a left
       parenthesis */
       error("expected an id, integer, or a left paren");
   } /* End of else */
   cout << "Exit <factor> return:" << return_val << endl;
   return return_val;
}/* End of function factor */

void error(const char *message)
{
   printf("Error: %s\n",message);
}
