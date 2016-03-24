#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global buffer array for each line.
char buffer[300];

// Character array to be returned by nextToken().
char returnMe[13];

// Pointer p1 will never do anything but point to the start of the buffer.
// This is to guarantee that we never lose track of the front of the array.
char *p1;

//Pointer p2 will be used to move across the buffer
char *p2;


// initBuffer()
void initBuffer(char *inputLine) {
  strcpy(buffer, inputLine); 
  
  // Set p1 and p2 to start of buffer.
  p1 = &buffer;
  p2 = &buffer;
}


// hasNextToken()
int hasNextToken() {
    
}


// nextToken()
char *nextToken() {
  if(p2[0] == '\n') {
    printf("You are returning NULL\n");
    return NULL;
    } else {
      int i=0;
      while(p2[0] != ' ' && p2[0] != ',' && p2[0] != '\n') {
        returnMe[i] = p2[0];
        i++;
        p2 = p2+1;
      }
      // To finish copying, need to have some indicator for 
      // end of the string. For this we just add '\0' on to end.
      returnMe[i] = '\0';
      
      printf("returned string: %s\n", returnMe);

      if(p2[0] == ' ' || p2[0] == ',') {
        p2 = p2+1;
        printf("Still more tokens!\n");
        return returnMe;
      } else {
        // If here, p2 currently points to '\n', so no need 
        // to increment pointer. Just return "returnMe".

        printf("End of line. No more tokens here!\n");
        return returnMe;
      }
    }
  }



// rewind()

