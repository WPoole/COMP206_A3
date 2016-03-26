#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global buffer array for each line.
char buffer[300];

// Character array to be returned by nextToken().
char returnMe[13];

// Pointer p1 will be used to move across the buffer
char *p1;

// Integer variable to keep track of number of characters seen.
int charsSeen = 1;


// initBuffer()
void initBuffer(char *inputLine) {
  strcpy(buffer, inputLine); 
  
  // Set p1 to start of buffer.
  p1 = &buffer;
  printf("Size of string is: %d\n", strlen(buffer));
}


// hasNextToken()
int hasNextToken() {
  printf("THE LENGTH OF THE BUFFER IS: %d\n",strlen(buffer));
  if(charsSeen >= strlen(buffer)) {
    // Return 0 (false) if there is no next token.
    printf("No more tokens.\n");
    return 0;
  } else {
    printf("Still some tokens.\n");
    return 1;
  }
}


// nextToken()
char *nextToken() {
  if(p1[0] == '\n') {
    printf("You are returning NULL\n");
    return NULL;
    } else {

      // CHECK HERE TO SEE IF FIRST CHARACTER WE ARE LOOKING AT IS 
      // A WHITESPACE OF A COMMA.
      if(p1[0] == ' ') {
        returnMe[0] = ' ';
        returnMe[1] = '\0';
        charsSeen++;
        p1 = p1+1;
        return returnMe;
      } else if(p1[0] == ',') {
        returnMe[0] = ',';
        returnMe[1] = '\0';
        charsSeen++;
        p1 = p1+1;
        return returnMe;
      } else {
        // NOW WE KNOW WE ARE PASSED WHITE SPACE AND COMMAS, SO WE 
        // CAN CHECK FOR THE REGULAR TOKENS.
        int i=0;
        while(p1[0] != ' ' && p1[0] != ',' && p1[0] != '\n') {
          returnMe[i] = p1[0];
          i++;
          charsSeen++;
          p1 = p1+1;
        }
        // To finish copying, need to have some indicator for 
        // end of the string. For this we just add '\0' on to end.
        returnMe[i] = '\0';
        
        printf("returned string: %s\n", returnMe);

        if(p1[0] == ' ' || p1[0] == ',') {
          p1 = p1+1;
          charsSeen++;

          printf("Size of string is: %d\n", strlen(buffer));
          printf("charsSeen: %d\n", charsSeen);
          printf("Still more tokens!\n");

          return returnMe;
        } else {
          // If here, p1 currently points to '\n', so no need 
          // to increment pointer. Just return "returnMe".

          printf("End of line. No more tokens here!\n");
          return returnMe;
        }
      }
    }
  }



// rewind()
void rewind() {
  //Just need to bring pointer, p1, back to start of buffer.
  p1 = &buffer;

}

