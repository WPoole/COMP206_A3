#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.c"

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

  // TESTING nextToken()
  nextToken();





  // WHY DOESN'T THIS BREAK AT ANY POINT? IS "\r" NOT A THING ON MAC?
  for(int i=0; i<300; i++) {
    if(line[i] == '\n') {
      printf("You found '\n'!");
      break;
    }
    printf("%c\n", line[i]);

  }

  while(!feof(file_ptr)) {
    printf("%s\n", line);
    fgets(line, 299, file_ptr);
  }
  fclose(file_ptr);

  return 0;
}

