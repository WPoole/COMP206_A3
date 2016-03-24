#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global buffer array for each line.
char buffer[300];

// Character array to be returned by nextToken().
char returnMe[13];



// initBuffer()
void initBuffer(char *inputLine) {
  // EXPLAIN WHY THIS DOESN'T WORK. HOW TO DO THIS WITHOUT STRCPY()?
  //buffer = &inputLine[0];
  strcpy(buffer, inputLine); 
  //printf("%s\n",inputLine);
  //printf("%s\n", buffer);
}


// hasNextToken()
int hasNextToken() {
    
  
}


// nextToken()
char *nextToken() {
  if(buffer[0] == '\n') {
    printf("You are returning NULL\n");
    return NULL;
    } else {
    // char* to be returned. We choose 13 as the size to account for 
    // biggest possible word, "detectmarker".
    //char returnMe[13];
    int i = 0;
    while(buffer[i] != ' ' || buffer[i] != ',' || buffer[i] != '\n') {
      returnMe[i] = buffer[i];
      i++;
      printf("%d", i);
    }
    
    int j = 0;
    if(buffer[i] == ' ' || buffer[i] == ',') {
      // Need to increment i by one to get it off the space or comma to start 
      // of next token.
      i++;
      
      while(buffer[i] != '\n') {
        // Next shift all elements down to start of array.
        buffer[j] = buffer[i];
        j++;
        i++;
      }

      // Lastly, copy the '\n' into shifted buffer array.
      buffer[j] = buffer[i];
      
      //Lastly, want to return the token.
      return returnMe;
    } else {
      // In this case, we know we have come to the end. i.e. We hit '\n'.
      // If this happens, set first thing in new array to be buffer[i], which
      // should be '\n'.
      buffer[0] = buffer[i];
      
      // Lastly, (same as if case above) we want to return the token.
      return returnMe;
    }
  }
}


// rewind()

