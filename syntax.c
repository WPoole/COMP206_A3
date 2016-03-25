#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// All #define variables.
#define NUM_COMMANDS 8


// List of legal Commands
char *commands[NUM_COMMANDS] ={"TAKEASTEP", "LEFT", "RIGHT", "PICKUP", "DROP", "DETECTMARKER", "TURNON", "TURNOFF"};


// isValidCommand()
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
