#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.c"
//#include "oldSyntax2.c"
#include "syntax.c"


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
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

  } else {
    printf("\n\n\n\n\n\n\n\n"); 
    printf("OFFENDING LINE IS ON LINE NUMBER: %d\n", lineNum);
    printf("OFFENDING LINE IS: %s\n", line);
    line[result-2] = '\0';
    printf("THE ERROR IS INDICATED BY THREE CONSECUTIVE ASTERISKS: %s\n", line);
    int length = strlen(line);
    char *secondHalf = &line[length+1];
    printf("***");
    printf("%s\n", secondHalf);

    // JUST CLEAR A FEW LINES.
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
  syntaxCheck(line, lineNum);

  while(!feof(file_ptr)) {
    // GET NEXT LINE.
    fgets(line, 299, file_ptr);
    lineNum++;
    syntaxCheck(line, lineNum);

  }
  fclose(file_ptr);

  return 0;
}

