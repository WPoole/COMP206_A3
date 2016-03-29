#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "syntax.h"



void toUpperCase(char *input) {
  int length = strlen(input);
  for(int i=0; i<length; i++) {
    if(input[i] >= 'a' && input[i] <= 'z') {
      input[i] = input[i] - 32;
    }
  }
  printf("THE UPDATED EXPRESSION IS: %s\n", input);
}


// FUNCTION FOR DETERMINING WHAT KIND OF ERROR MESSAGE TO PRINT.
void printError(char *line) {

  // OPTION 1: ATTEMPTED REPEAT EXPRESSION.
  char *repeat = strstr(line, "REPEAT");
  if(repeat != NULL) {
    printf("Error - The syntax for a valid 'Repeat' loop is the following: \n");
    printf("REPEAT n TIMES Comma-Separated-List-Of-Commands END\n");
    printf("Where 'n' IS AN INTEGER.\n");
    return;
  }

  // OPTION 2: ATTEMPTED WHILE EXPRESSION.
  char *whileNot = strstr(line, "WHILE");
  if(whileNot != NULL) {
    printf("Error - The syntax for a valid 'While' loop is the following: \n");
    printf("WHILE NOT DETECTMARKER DO Comma-Separated-List-Of-Commands END\n");
    return;
  }

  // OPTION 3: ATTEMPTED SAY EXPRESSION.
  char *say = strstr(line, "SAY");
  if(say != NULL) {
    printf("Error - The syntax for a valid 'Say' expression is the following: \n");
    printf("SAY 'Enter a message here that you want to say'\n");
    return;
  }

  // OPTION 4: ATTEMPTED COMMAND.
  char *takeastep = strstr(line, "TAKEASTEP");
  char *left = strstr(line, "LEFT");
  char *right = strstr(line, "RIGHT");
  char *pickup = strstr(line, "PICKUP");
  char *drop = strstr(line, "DROP");
  char *detectmarker = strstr(line, "DETECTMARKER");
  char *turnon = strstr(line, "TURNON");
  char *turnoff = strstr(line, "TURNOFF");
  if((takeastep != NULL) || (left != NULL) || (right != NULL) || (pickup != NULL) || (drop != NULL) || (detectmarker != NULL) || (turnon != NULL) || (turnoff != NULL)) {
    printf("Error - The syntax for a valid Command is the following: \n");
    printf("Command\n");
    printf("There should not be anything on either side of the command other than white space.\n");
    return;
  }

  // OPTION 5: NOT REALLY SURE.
  printf("Error - Unrecognized expression or command.\n");
  printf("Examples of valid expressions and commands are shown here:\n");
  printf("REPEAT n TIMES Comma-Separated-List-Of-Commands END\n");
  printf("WHILE NOT DETECTMARKER DO Comma-Separated-List-Of-Commands END\n");
  printf("SAY 'Enter a message here that you want to say'\n");
  printf("Command\n");

}


// FUNCTION THAT WILL RUN TO DO THE SYNTAX CHECK AND OUTPUT ERROR MESSAGES IF NEEDED.
void syntaxCheck(char *line, int lineNum) {

  initBuffer(line);
  int result = isValidExpression(line);
  printf("THE INDEX OF THE ERROR IS: %d\n", result);

  if(result == 0) {
    printf("\n\n\n\n\n\n\n\n"); 
    printf("LINE %d WAS TOTALLY FINE!!!\n", lineNum);
    printf("THE WELL-WRITTEN LINE IS: %s", line);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

  } else if(result == 1) { 
    printf("\n\n\n\n\n\n\n\n"); 
    printf("OFFENDING LINE IS ON LINE NUMBER: %d\n", lineNum);
    printf("OFFENDING LINE IS: %s\n", line);
    printf("THE ERROR IS INDICATED BY THREE CONSECUTIVE ASTERISKS: ***%s\n", line);
    printError(line);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

  } else {
    printf("\n\n\n\n\n\n\n\n"); 
    printf("OFFENDING LINE IS ON LINE NUMBER: %d\n", lineNum);
    printf("OFFENDING LINE IS: %s\n", line);
    line[result-2] = '\0';
    printf("THE ERROR IS INDICATED BY THREE CONSECUTIVE ASTERISKS: %s", line);
    int length = strlen(line);
    char *secondHalf = &line[length+1];
    printf("***");
    printf("%s\n", secondHalf);
    printError(line);

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  }
}





int main(int argc, char *argv[]) { 

  if(argc != 2) {  
    printf("Error: Please input a single valid path to a file.\nPlease type: ./a.out VALID_PATH_TO_FILE \n");
    return 1;
  }

  char *filepath = argv[1];
  
  FILE *file_ptr;
  char line[300];

  file_ptr = fopen(filepath, "rt");

  if (file_ptr == NULL) {
    printf("Error: File pointer is set to NULL.\n");
    return 1;
  }

  // VARIABLE TO KEEP TRACK OF LINE NUMBER WE'RE ON.
  int lineNum = 1;
  fgets(line, 299, file_ptr);

  printf("LINE BEFORE MODIFICATION IS: %s\n", line);
  toUpperCase(line);
  printf("LINE AFTER MODIFICATION IS: %s\n", line);

  syntaxCheck(line, lineNum);

  while(!feof(file_ptr)) {
    // GET NEXT LINE.
    fgets(line, 299, file_ptr);

    printf("LINE BEFORE MODIFICATION IS: %s\n", line);
    toUpperCase(line);
    printf("LINE AFTER MODIFICATION IS: %s\n", line);

    lineNum++;
    syntaxCheck(line, lineNum);

  }
  fclose(file_ptr);


printf("THE COMPARISON GAVE: %d\n", strcmpi("heLlO", "hELlO"));

  return 0;
}












