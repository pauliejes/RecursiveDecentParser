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
