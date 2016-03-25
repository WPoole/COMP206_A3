#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "parse.c"

// All #define variables.
#define NUM_COMMANDS 8

// Need character array here to temporarily store the next token.
char currToken[13];


// HELPER SETTER FUNCTION.
void setCurrToken(char *token) {
  strcpy(currToken, token);
}

// LIST OF LEGAL COMMANDS.
char *commands[NUM_COMMANDS] = {"TAKEASTEP", "LEFT", "RIGHT", "PICKUP", "DROP", "DETECTMARKER", "TURNON", "TURNOFF"};

// LEGAL EXPRESSIONS.
// 1. REPEAT n TIMES comma-separated-list-of-commands END
char *repeat[3] = {"REPEAT","TIMES","END"};

// 2. WHILE NOT DETECTMARKER DO comma-separated-list-of-commands END
char *whileNot[5] = {"WHILE","NOT","DETECTMARKER","DO","END"};

// ISVALIDCOMMAND()
int isValidCommand(char *token) {
  int i = 0;
  while(i<NUM_COMMANDS) {
    if(!strcmp(commands[i], token)) {
      return 1;
    }
    i++;
  }
  return 0;
}


// ISVALIDEXPRESSION()
int isValidExpression(char *expression) {
  // GET FIRST TOKEN AND SET TO currToken.
  setCurrToken(nextToken());  
  printf("CURRENT TOKEN IS: %s\n", currToken);
  printf("Repeat[0] is: %s\n", repeat[0]);
  printf("WhileNot[0] is: %s\n", whileNot[0]);  
  printf("strcmp(currToken, repeat[0]) is: %d\n", strcmp(currToken, repeat[0]));
  printf("strcmp(currToken, whileNot[0]) is: %d\n", strcmp(currToken, whileNot[0]));  

  int i = 0;  

  // CHECK IF FIRST WORD MATCHES WITH A VALID EXPRESSION (EITHER "REPEAT"
  // OR "WHILE").
  if(strcmp(currToken, repeat[0]) && strcmp(currToken, whileNot[0])) {
    printf("Invalid Expression\n\n");
    return 0;
  } else if(!strcmp(currToken, repeat[0])) {
    // IF THE FIRST WORD IS "REPEAT", WE WILL BE MAKING COMPARISONS
    // WITH THE "repeat" ARRAY.
    
  } else if(!strcmp(currToken, whileNot[0])) {
    // IF THE FIRST WORD IS "WHILE", WE WILL BE MAKING COMPARISONS
    // WITH THE "whileNot" ARRAY.

  }




  printf("Valid Expression\n\n");
  return 1;

}
