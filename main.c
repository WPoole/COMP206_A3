#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.c"
//#include "oldSyntax2.c"
#include "syntax.c"

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
    printf("Error: File pointer is set to NULL.");
    return 1;
  }

  fgets(line, 299, file_ptr);

  // TESTING initBuffer()
  initBuffer(line);
  printf("buffer: %s\n", buffer);


  // TESTING isValidExpression()
  int result = isValidExpression(line);
  printf("\n\nERROR OCCURRED AT INDEX: %d\n\n", result);
  printf("%s\n", line);
  line[result-1] = '*';
  printf("%s\n", line);

  // JUST CLEAR A FEW LINES.
  printf("\n\n\n\n");

  // TESTING nextToken()
  // nextToken();
  // printf("Has Next Token?: %d\n", hasNextToken());
  // nextToken();
  // printf("Has Next Token?: %d\n", hasNextToken());
  // nextToken();
  // printf("Has Next Token?: %d\n", hasNextToken());
  // nextToken();
  // printf("Has Next Token?: %d\n", hasNextToken());
  // nextToken();
  // printf("Has Next Token?: %d\n", hasNextToken());
  // nextToken();
  // printf("Has Next Token?: %d\n", hasNextToken());

  // IS "\r" NOT A THING ON MAC?


  // TESTING isValidCommand()
  char testCommand[13] = {'D','E','T','E','C','T','M','A','R','K','E','R','\0'};
  printf("Is it a valid command?: %d\n", isValidCommand(testCommand));



  // TESTING isValidExpression()
  





  while(!feof(file_ptr)) {
    printf("%s\n", line);
    fgets(line, 299, file_ptr);
  }
  fclose(file_ptr);

  return 0;
}

