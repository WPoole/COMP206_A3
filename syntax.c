#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "parse.c"

// All #define variables.
#define NUM_COMMANDS 8

// "errorIndex" WILL KEEP TRACK OF OUR CURRENT INDEX IN THE EXPRESSION
// AT ALL TIMES AND IS WHAT WE WILL RETURN TO INDICATE THE POSITION OF 
// AN ERROR IF THERE IS ONE.
// NOTE: WE ONLY WANT TO INCREMENT THIS *AFTER* WE CATCH THE ERROR, SO 
// THAT IN "main.c" WE CAN PLACE THE "***" ERROR INDICATOR AT THE 
// APPROPRIATE PLACE, *BEFORE* THE TOKEN THAT CAUSED THE ERROR.
int errorIndex = 0;

// ALSO HAVE VARIABLE TO STORE LENGTH OF CURRENT TOKEN WE ARE LOOKING AT.
int currTokenLength = 0;

// NEED CHARACTER ARRAY HERE TO TEMPORARILY STORE THE NEXT TOKEN.
char currToken[13];

// LIST OF LEGAL COMMANDS.
char *commands[NUM_COMMANDS] = {"TAKEASTEP", "LEFT", "RIGHT", "PICKUP", "DROP", "DETECTMARKER", "TURNON", "TURNOFF"};

// LEGAL EXPRESSIONS.
// 1. REPEAT n TIMES comma-separated-list-of-commands END.
char *repeat[3] = {"REPEAT","TIMES","END"};

// 2. WHILE NOT DETECTMARKER DO comma-separated-list-of-commands END.
char *whileNot[5] = {"WHILE","NOT","DETECTMARKER","DO","END"};

// 3. SAY "message"
char *say[1] = {"SAY"};

// INTEGER TO KEEP TRACK OF LINE NUMBER WE ARE ON.
int lineNumber = 0;



// NEED FUNCTION TO SEE IF TOKEN IS A VALID NUMBER OR NOT.
int isNumber(char *c) {
  printf("THE NUMBER WE ARE TRYING TO CHECK IS: %s\n", c);
  int i = 0;

  while(c[i] != '\0') {
    if(c[i]> 57 || c[i]< 48) {
      return 0;
    }
    i++;
  }
  return 1;
}


// HELPER SETTER FUNCTION.
void setCurrToken(char *token) {
  strcpy(currToken, token);
}

// HELPER FUNCTION TO SEE IF WE ARE AT "END" OF EXPRESSION.
int checkEnd() {
  // IF currToken IS EQUAL TO "END", RETURN 1, ELSE RETURN 0.
  if(!strcmp(currToken, repeat[2])) {
    return 1;
  } else {
    return 0;
  }
}

// NEED FUNCTION THAT CHECKS IF *ANYTHING* (OTHER THAN WHITESPACE)
// IS WRITTEN AFTER "END" HAS BEEN SEEN. RETURNS 0 IF THERE WAS 
// ANYHING OTHER THAN WHITESPACE AFTER "END", 1 OTHERWISE.
int isEnd() {
  errorIndex += (currTokenLength + 1);
  while(!isNextNull(currToken)) {
    char *nextTokenPointer = nextToken();

    if(nextTokenPointer == NULL) {
      printf("THE END IS ALL GOOD!!!!\n");
      return 1;
    } else {
      setCurrToken(nextTokenPointer);
      if(!isWhiteSpace()) {
        printf("THE END CANNOT HAVE ANYTHING AFTER IT!!! \n");
        return 0;
      } else {
        // ELSE WE KNOW IT IS WHITE SPACE...
        currTokenLength = strlen(nextTokenPointer);
        errorIndex += (currTokenLength);
      }
    }
  }
  printf("THE END IS GOOD!!!!\n");
  return 1;
}

// CHECK IF NEXT TOKEN IS NULL FUNCTION
int isNextNull(char *nextTokenPointer) { 
  if(nextTokenPointer == NULL) {
    printf("POINTER IS SET TO NULL!!!!!!!!! \n");
    printf("VALID EXPRESSION SINCE WE FOUND NULL!!!!!\n");
    return 1;
  } else {
    return 0;
  }
}

// ALSO NEED A FUNCTION THAT CHECKS IF THE NEXT TOKEN IS A WHITE SPACE.
int isWhiteSpace() {
  char *whiteSpace = " ";
  // RETURN 1 IF THE CURRENT TOKEN IS A WHITESPACE, 0 OTHERWISE.
  if(!strcmp(currToken, whiteSpace)) {
    printf("YOU FOUND A WHITESPACE.\n");
    return 1;
  } else {
    return 0;
  }
}

// SIMILARLY, NEED A FUNCTION THAT CHECKS IF THE NEXT TOKEN IS A WHITE SPACE.
int isComma() {
  char *comma = ",";
  // RETURN 1 IF THE CURRENT TOKEN IS A WHITESPACE, 0 OTHERWISE.
  if(!strcmp(currToken, comma)) {
    printf("YOU FOUND A COMMA.\n");
    return 1;
  } else {
    return 0;
  }
}

// LASTLY, ALSO NEED ONE THAT WILL CHECK IF THE NEXT TOKEN IS *EITHER* A
// WHITE SPACE OR A COMMA.

int isCommaOrWhite() {
  char *whiteSpace = " ";
  char *comma = ",";
  // RETURN 1 IF THE CURRENT TOKEN IS A WHITESPACE OR COMMA, 0 OTHERWISE.
  if(!strcmp(currToken, whiteSpace) || !strcmp(currToken, comma)) {
    printf("YOU FOUND A COMMA OR WHITESPACE.\n");
    return 1;
  } else {
    return 0;
  }
}




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

  // RESET "errorIndex".
  // IMPORTANT NOTE: "errorIndex" MUST BE INITIALIZED TO 1, NOT 0, IN ORDER
  // FOR US TO NOT GET CONFUSED BETWEEN AN ERROR THAT IS OCCURRING AT THE FIRST
  // INDEX, AND A VALID EXPRESSION WHICH ALSO RETURNS 0.
  errorIndex = 1;

  // GET FIRST TOKEN AND SEE IF IT IS NULL. IF IT IS, WE JUST HAVE AN EMPTY
  // LINE (WHICH IS FINE), SO WE RETURN 0. OTHERWISE, WE SET IT TO currToken.
  char *firstToken = nextToken();


  if(isNextNull(firstToken)) {
    return 0;
  } else {
    currTokenLength = strlen(firstToken);
    setCurrToken(firstToken);
  }

  // ALSO NEED TO CHECK FOR JUST A FULL LINE OF WHITESPACE, AS THIS IS ALSO OK.
  while(isWhiteSpace()) {
    errorIndex += currTokenLength;
    char *pointNextToken = nextToken();

    // WE KNOW THAT IF nextToken() RETURNS "NULL" TO US, THAT
    // WE HAVE MADE IT TO THE END OF THE LINE WITHOUT OTHER ERRORS.
    if(isNextNull(pointNextToken)) {
      return 0;
    } else {
      currTokenLength = strlen(pointNextToken);
      setCurrToken(pointNextToken);
    }
  }

  printf("**@*@*@*@*@*@*@*@ INDEX HERE IS: %d\n", errorIndex);

  // PRINTING FOR TESTING.
  printf("\nCURRENT TOKEN IS: %s\n", currToken);
  printf("Repeat[0] is: %s\n", repeat[0]);
  printf("WhileNot[0] is: %s\n", whileNot[0]);  
  printf("strcmp(currToken, repeat[0]) is: %d\n", strcmp(currToken, repeat[0]));
  printf("strcmp(currToken, whileNot[0]) is: %d\n", strcmp(currToken, whileNot[0]));  
  
  // INITIALIZE i VARIABLE TO HELP ITERATE THROUGH "repeat" ARRAY.
  int i = 0;

  // FIRST CHECK TO SEE IF THE EXPRESSION INPUTED IS JUST A SINGLE COMMAND. NOTE THERE 
  // CAN ONLY BE ONE COMMAND PER LINE IF THIS IS THE CASE.
  if(isValidCommand(currToken)) {
    if(isEnd()) {
      return 0;
    } else {
      return errorIndex;
    }
  }


  // CHECK IF FIRST WORD MATCHES WITH A VALID EXPRESSION (EITHER "REPEAT" OR "WHILE").
  else if(strcmp(currToken, repeat[i]) && strcmp(currToken, whileNot[i]) && strcmp(currToken, say[i])) {
    printf("Invalid Expression\n\n");
    return errorIndex;



  // *******************************************************************************
  // IF FIRST WORD IS "REPEAT".
  // *******************************************************************************
  } else if(!strcmp(currToken, repeat[0])) {

    currTokenLength = strlen(currToken);


    // NOTE: IN CASES WHERE WE ACTUALLY SAW A TOKEN THAT WAS *NOT* A WHITE SPACE, 
    // WE NEED TO ADD AN EXTRA +1 TO THE "errorIndex" TO ACCOUNT FOR THE EXTRA
    // SPACE THAT GETS ADDED AFTER THE TOKEN HAS BEEN READ.
    errorIndex += (currTokenLength + 1);

    // IF THE FIRST WORD IS "REPEAT", WE WILL BE MAKING COMPARISONS
    // WITH THE "repeat" ARRAY.
    // GET NEXT TOKEN AND CHECK IF IT IS AN INTEGER. IF IT IS, WE'RE GOOD AND
    // CAN CONTINUE. IF IT IS NOT, THEN WE RETURN 0 SINCE IT IS BROKEN.

    char *tempPtr = nextToken();
    if(isNextNull(tempPtr)) {
      printf("MUST HAVE STUFF AFTER 'REPEAT'\n");
      return errorIndex;
    }

    setCurrToken(tempPtr);
    currTokenLength = strlen(currToken);

    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;

      char *tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'REPEAT' HERE!!\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);
    }


    if(!isNumber(currToken)) {
      printf("Invalid number.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);

      printf("NUMBER n: %d\n", atoi(currToken));
    }


    // INCREMENT "i" SO WE CAN COMPARE WITH NEXT ELEMENT IN "repeat" ARRAY.
    // HERE WE ARE LOOKING FOR THE WORD "TIMES".
    i++;
    // GET AND SET NEXT TOKEN, THEN CHECK IF IT'S LEGIT.
    tempPtr = nextToken();
    if(isNextNull(tempPtr)) {
      printf("MUST HAVE STUFF AFTER 'NUMBER'\n");
      return errorIndex;
    }

    setCurrToken(tempPtr);
    currTokenLength = strlen(currToken);

    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;

      char *tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'NUMBER' HERE!!\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);
    }

    // CHECK IF CURRENT TOKEN EQUALS "TIMES".
    if(strcmp(currToken, repeat[i])) {
      printf("Invalid TIMES.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }

    // NOW AT THIS POINT WE SHOULD HAVE IN FRONT OF US THE "COMMA-SEPARATED-
    // LIST-OF-COMMANDS". SO WE LOOP OVER UNTIL WE GET TO THE END OF THIS LIST.
    if(hasNextToken()) {

      char *tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'TIMES'\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);


      // BEFORE LOOPING, WE JUST WANT TO CHECK WHAT THE *FIRST* TOKEN IS. THIS 
      // WILL ALLOW TO CHECK FOR: 1. NO COMMAS BEFORE FIRST COMMAND. 2. WHETHER 
      // THERE ARE ANY COMMANDS OR IF IT JUST GOES STRAIGHT TO END.
      while(isWhiteSpace()) {
        errorIndex += currTokenLength;

        char *pointerToken = nextToken();
        if(isNextNull(pointerToken)) {
          // IF WE GET TO A NULL AT THIS POINT, WE KNOW THERE MUST NOT HAVE BEEN
          // ANY COMMANDS OR "END" ENTERED, SO WE RETURN 0 TO INDICATE ERROR.
          printf("YOU MUST ENTER COMMA-SEPARATED-COMMANDS FOLLOWED BY 'END' \n");
          return errorIndex;
        } else {
          setCurrToken(pointerToken);
          currTokenLength = strlen(currToken);
        }
        // setCurrToken(nextToken());
      }


      // NEED TO CHECK FOR "END" AND REGULAR COMMANDS SEPARATELY HERE. IF WE SEE "END", 
      // AND KNOW THERE IS NOTHING AFTER IT, WE KNOW THE EXPRESSION IS CHECKED AND WE 
      // CAN CONFIRM IT IS CORRECT.
      if(checkEnd()) {
        printf("NO COMMANDS ENTERED!\n\n");
        // CHECK IF THERE WAS ANYTHING OTHER THAN WHITESPACE AFTER "END".
        if(isEnd()) {
          printf("THIS EXPRESSION FINISHED WITH 'END' AND IS VALID!\n");
          return 0;
        } else {
          printf("CANNOT HAVE ANYTHING EXCEPT WHITESPACE AFTER 'END'!\n");
          return errorIndex;
        }
      }

      // HERE WE CHECK FOR JUST THE VALID COMMANDS.
      if(isValidCommand(currToken)) {
        errorIndex += (currTokenLength + 1);
        printf("THE FIRST LEGIT TOKEN IS VALID AND IS: %s\n", currToken);

      } else {
        // ELSE WE KNOW THE TOKEN IS INVALID.
        printf("INVALID FIRST TOKEN HERE.\n\n");
        return errorIndex;
      }

    } else {
      // ELSE (IF WE GET HERE), WE KNOW THERE IS NO NEXT TOKEN, SO RETURN 0.
      printf("CANNOT LEAVE BLANK HERE!!.\n\n");
      return errorIndex;
    }



    // THIS IS THE FINAL WHILE LOOP NOW THAT WILL LOOP OVER ALL REMAINING
    // THINGS IN THE EXPRESSION.
    while(hasNextToken()) {

      char *tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'COMMAND'\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);


      // INTEGER TO KEEP TRACK OF NUMBER OF COMMAS SEEN.
      int numCommas = 0;
      // ********************** IDEA: JUST SET POINTER BACK BY ONE SPOT
      // AND CHECK IF ITS A COMMA.

      // CHECK TO SEE IF FIRST TOKEN IS COMMA
      if(isComma) {
        numCommas++;
      }



      // HERE THERE CAN BE COMMAS OR WHITE SPACES SO WE CHECK FOR BOTH.
      while(isCommaOrWhite()) {
        errorIndex += currTokenLength;

        char *nextTokenPtr = nextToken();
        if(isNextNull(nextTokenPtr)) {
          // IF WE SEE THE TOKEN IS NULL WITHOUT HAVING SEEN "END", WE 
          // KNOW THERE IS A MISTAKE AND RETURN 0.
          printf("YOU FORGOT TO ADD AN 'END' TO YOUR EXPRESSION!!!\n");
          return errorIndex;
        } else {
          // NEED TO ENSURE THAT THERE IS AT LEAST ONE COMMA BETWEEN EACH 
          // COMMAND. TO DO THIS, COUNT EACH COMMA WE SEE. IF OUR COUNT IS
          // ZERO AT THE END OF THIS LOOP, THEN WE KNOW THEY WERE MISSING 
          // A COMMA, SO WE THROW AN ERROR AND RETURN 0.
          if(isComma) {
            numCommas++;
          }
          setCurrToken(nextTokenPtr);
          currTokenLength = strlen(currToken);
        }
      }

      // CHECK "numCommas". IF EQUAL TO 0, RETURN 0 SINCE THERE MUST BE
      // AT LEAST ONE COMMA BETWEEN EACH COMMAND.
      printf("****** NUMBER OF COMMAS SEEN THIS LINE IS : %d *******\n", numCommas);
      if(numCommas == 0) {
        printf("ALL COMMANDS MUST BE SEPARATED BY AT LEAST ONE COMMA!!!\n");
        return 0;
      }

      // CHECK EACH TIME THROUGH LOOP IF WE ARE AT 'END' COMMAND.
      if(checkEnd()) {
        printf("YOU HAVE REACHED THE END!\n\n");
        // CHECK IF THERE WAS ANYTHING OTHER THAN WHITESPACE AFTER "END".
        if(isEnd()) {
          printf("FINISHED WITH END! SWEET!!\n");
          return 0;
        } else {
          printf("NICE TRY..... CANT HAVE ANYTHING AFTER 'END'!\n");
          return errorIndex;
        }        
      } else if(isValidCommand(currToken)) {
        // IF NOT AT 'END', WE MUST VERIFY IF CURRENT TOKEN IS VALID. IF 
        // IT IS WE KEEP GOING.
        errorIndex += (currTokenLength + 1);

        printf("THE CURRENT TOKEN IS VALID AND IS: %s\n", currToken);
        continue;
      } else {
        // IF IT IS NOT VALID, WE EXIT.
        printf("THE CURRENT TOKEN IS ***NOT*** VALID AND IS: %s\n", currToken);
        return errorIndex;
      }
    }

    // VERY IMPORTANT: IF WE GET TO THIS POINT HERE, WE KNOW THAT THERE WAS NO
    // "END" STATEMENT IN THE EXPRESSION. HOW DO WE KNOW THIS? BECAUSE IF THERE
    // WAS AN "END", IT WOULD HAVE CAUSED THE PROGRAM TO "RETURN" EITHER 1 OR 0,
    // THUS EXITING THE PROGRAM. THEREFORE, IF WE GET TO THIS POINT, WE HAVE TO 
    // RETURN 0 SINCE WE KNOW THERE MUST BE A PROBLEM.
    printf("INVALID EXPRESSION!! NEED AN 'END' PLEASE TRY AGAIN!!\n");
    return errorIndex;



  // *******************************************************************************
  // IF FIRST WORD IS "WHILE".
  // *******************************************************************************
  } else if(!strcmp(currToken, whileNot[0])) {

    currTokenLength = strlen(currToken);

    errorIndex += (currTokenLength + 1);

    // IF THE FIRST WORD IS "WHILE", WE WILL BE MAKING COMPARISONS
    // WITH THE "whileNot" ARRAY.
    // GET NEXT TOKEN AND CHECK IF IT IS "NOT". IF IT IS, WE'RE GOOD AND
    // CAN CONTINUE. IF IT IS NOT, THEN WE RETURN 0 SINCE IT IS BROKEN.
    
    // INCREMENT "i" SO WE CAN COMPARE TOKEN WITH "NOT" FROM ARRAY.
    i++;

    char *tempPtr = nextToken();
    if(isNextNull(tempPtr)) {
      printf("MUST HAVE STUFF AFTER 'WHILE'\n");
      return errorIndex;
    }
    setCurrToken(tempPtr);
    currTokenLength = strlen(currToken);

    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;

      tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'WHILE' HERE!!\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);
    }

    // CHECK IF TOKEN IS "NOT".
    if(strcmp(currToken, whileNot[i])) {
      printf("Invalid 'NOT'.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }


    // INCREMENT "i" SO WE CAN COMPARE WITH NEXT ELEMENT IN "whileNot" ARRAY.
    // HERE WE ARE LOOKING FOR THE WORD "DETECTMARKER".
    i++;


    tempPtr = nextToken();
    if(isNextNull(tempPtr)) {
      printf("MUST HAVE STUFF AFTER 'NOT'\n");
      return errorIndex;
    }
    setCurrToken(tempPtr);
    currTokenLength = strlen(currToken);

    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;

      tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'NOT' HERE!!\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);
    }

    // CHECK IF TOKEN IS "DETECTMARKER"
    if(strcmp(currToken, whileNot[i])) {
      printf("Invalid DETECTMARKER.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }


    // INCREMENT "i" SO WE CAN COMPARE WITH NEXT ELEMENT IN "whileNot" ARRAY.
    // HERE WE ARE LOOKING FOR THE WORD "DO".
    i++;

    // NEED TO CHECK IF FIRST CHAR IS NULL.
    tempPtr = nextToken();
    if(isNextNull(tempPtr)) {
      printf("MUST HAVE STUFF AFTER 'DETECTMARKER'\n");
      return errorIndex;
    }
    setCurrToken(tempPtr);
    currTokenLength = strlen(currToken);

    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;

      tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'DETECTMARKER' HERE!!\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);
    }

    if(strcmp(currToken, whileNot[i])) {
      printf("Invalid DO.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }


    // NOW AT THIS POINT WE SHOULD HAVE IN FRONT OF US THE "COMMA-SEPARATED-
    // LIST-OF-COMMANDS". SO WE LOOP OVER UNTIL WE GET TO THE END OF THIS LIST.
    if(hasNextToken()) {

      char *tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'DO'\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);


      // BEFORE LOOPING, WE JUST WANT TO CHECK WHAT THE *FIRST* TOKEN IS. THIS 
      // WILL ALLOW TO CHECK FOR: 1. NO COMMAS BEFORE FIRST COMMAND. 2. WHETHER 
      // THERE ARE ANY COMMANDS OR IF IT JUST GOES STRAIGHT TO END.
      while(isWhiteSpace()) {
        errorIndex += currTokenLength;

        char *pointerToken = nextToken();
        if(isNextNull(pointerToken)) {
          // IF WE GET TO A NULL AT THIS POINT, WE KNOW THERE MUST NOT HAVE BEEN
          // ANY COMMANDS OR "END" ENTERED, SO WE RETURN 0 TO INDICATE ERROR.
          printf("YOU MUST ENTER COMMA-SEPARATED-COMMANDS FOLLOWED BY 'END' \n");
          return errorIndex;
        } else {
          setCurrToken(pointerToken);
          currTokenLength = strlen(currToken);
        }
        // setCurrToken(nextToken());
      }


      // NEED TO CHECK FOR "END" AND REGULAR COMMANDS SEPARATELY HERE. IF WE SEE "END", 
      // AND KNOW THERE IS NOTHING AFTER IT, WE KNOW THE EXPRESSION IS CHECKED AND WE 
      // CAN CONFIRM IT IS CORRECT.
      if(checkEnd()) {
        printf("NO COMMANDS ENTERED!\n\n");
        // CHECK IF THERE WAS ANYTHING OTHER THAN WHITESPACE AFTER "END".
        if(isEnd()) {
          printf("THIS EXPRESSION FINISHED WITH 'END' AND IS VALID!\n");
          return 0;
        } else {
          printf("CANNOT HAVE ANYTHING EXCEPT WHITESPACE AFTER 'END'!\n");
          return errorIndex;
        }
      }

      // HERE WE CHECK FOR JUST THE VALID COMMANDS.
      if(isValidCommand(currToken)) {
        errorIndex += (currTokenLength + 1);
        printf("THE FIRST LEGIT TOKEN IS VALID AND IS: %s\n", currToken);
      } else {
        printf("INVALID FIRST TOKEN HERE.\n\n");
        return errorIndex;
      }


    } else {
      // ELSE (IF WE GET HERE), WE KNOW THERE IS NO NEXT TOKEN, SO RETURN 0.
      printf("CANNOT LEAVE BLANK HERE!!.\n\n");
      return errorIndex;
    }


    // THIS IS THE FINAL WHILE LOOP NOW THAT WILL LOOP OVER ALL REMAINING
    // THINGS IN THE EXPRESSION.
    while(hasNextToken()) {

      // MAKE SURE FIRST TOKEN ISN'T NULL.
      char *tempPtr = nextToken();
      if(isNextNull(tempPtr)) {
        printf("MUST HAVE STUFF AFTER 'COMMAND'\n");
        return errorIndex;
      }
      setCurrToken(tempPtr);
      currTokenLength = strlen(currToken);


      // INTEGER TO KEEP TRACK OF NUMBER OF COMMAS SEEN.
      int numCommas = 0;

      // CHECK TO SEE IF FIRST TOKEN IS COMMA
      if(isComma) {
        numCommas++;
      }


      // HERE THERE CAN BE COMMAS OR WHITE SPACES SO WE CHECK FOR BOTH.
      while(isCommaOrWhite()) {
        errorIndex += currTokenLength;

        char *nextTokenPtr = nextToken();
        if(isNextNull(nextTokenPtr)) {
          // IF WE SEE THE TOKEN IS NULL WITHOUT HAVING SEEN "END", WE 
          // KNOW THERE IS A MISTAKE AND RETURN 0.
          printf("YOU FORGOT TO ADD AN 'END' TO YOUR EXPRESSION!!!\n");
          return errorIndex;
        } else {
          // NEED TO ENSURE THAT THERE IS AT LEAST ONE COMMA BETWEEN EACH 
          // COMMAND. TO DO THIS, COUNT EACH COMMA WE SEE. IF OUR COUNT IS
          // ZERO AT THE END OF THIS LOOP, THEN WE KNOW THEY WERE MISSING 
          // A COMMA, SO WE THROW AN ERROR AND RETURN 0.
          if(isComma) {
            numCommas++;
          }
          setCurrToken(nextTokenPtr);
          currTokenLength = strlen(currToken);
        }
      }

      // CHECK "numCommas". IF EQUAL TO 0, RETURN 0 SINCE THERE MUST BE
      // AT LEAST ONE COMMA BETWEEN EACH COMMAND.
      printf("****** NUMBER OF COMMAS SEEN THIS LINE IS : %d *******\n", numCommas);
      if(numCommas == 0) {
        printf("ALL COMMANDS MUST BE SEPARATED BY AT LEAST ONE COMMA!!!\n");
        return 0;
      }

      // CHECK EACH TIME THROUGH LOOP IF WE ARE AT 'END' COMMAND.
      if(checkEnd()) {
        printf("YOU HAVE REACHED THE END!\n\n");
        // CHECK IF THERE WAS ANYTHING OTHER THAN WHITESPACE AFTER "END".
        if(isEnd()) {
          printf("FINISHED WITH END! SWEET!!\n");
          return 0;
        } else {
          printf("NICE TRY..... CANT HAVE ANYTHING AFTER 'END'!\n");
          return errorIndex;
        }        
      } else if(isValidCommand(currToken)) {
        // IF NOT AT 'END', WE MUST VERIFY IF CURRENT TOKEN IS VALID. IF 
        // IT IS WE KEEP GOING.
        errorIndex += (currTokenLength + 1);

        printf("THE CURRENT TOKEN IS VALID AND IS: %s\n", currToken);
        continue;
      } else {
        // IF IT IS NOT VALID, WE EXIT.
        printf("THE CURRENT TOKEN IS ***NOT*** VALID AND IS: %s\n", currToken);
        return errorIndex;
      }
    }

    // VERY IMPORTANT: IF WE GET TO THIS POINT HERE, WE KNOW THAT THERE WAS NO
    // "END" STATEMENT IN THE EXPRESSION. HOW DO WE KNOW THIS? BECAUSE IF THERE
    // WAS AN "END", IT WOULD HAVE CAUSED THE PROGRAM TO "RETURN" EITHER 1 OR 0,
    // THUS EXITING THE PROGRAM. THEREFORE, IF WE GET TO THIS POINT, WE HAVE TO 
    // RETURN 0 SINCE WE KNOW THERE MUST BE A PROBLEM.
    printf("INVALID EXPRESSION!! NEED AN 'END' PLEASE TRY AGAIN!!\n");
    return errorIndex;



  // *******************************************************************************
  // IF FIRST WORD IS "SAY".
  // *******************************************************************************
  } else if(!strcmp(currToken, say[0])) {

    currTokenLength = strlen(currToken);

    errorIndex += (currTokenLength + 1);

    // CHECK IF NEXT TOKEN IS NULL AND THEN SET IT.
    char *nextPtr = nextToken();
    if(isNextNull(nextPtr)) {
      return errorIndex;
    } 
      
    setCurrToken(nextPtr);
    currTokenLength = strlen(currToken);





    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;

      char *ptrToken = nextToken();
      if(isNextNull(ptrToken)) {
        // IF WE GET TO A NULL AT THIS POINT, WE KNOW THERE MUST NOT HAVE BEEN
        // ANY MESSAGE OR OTHER TOKENS ENTERED, SO WE RETURN 0 TO INDICATE ERROR.
        printf("YOU MUST ENTER A MESSAGE AFTER USING 'SAY'. \n");
        return errorIndex;
      } else {
        setCurrToken(ptrToken);
        currTokenLength = strlen(currToken);
      }
    }

    printf("SAY: %s\n", currToken);

    // IF FIRST CHAR AFTER SAY IS NOT A DOUBLE QUOTE, THERE IS A MISTAKE.
    if(currToken[0] != '"') {
      printf("FIRST CHARACTER WAS **NOT** A DOUBLE QUOTE!!! .\n\n");
      return errorIndex;

    } else {
      // IF HERE, WE KNOW THE FIRST CHARACTER WAS A DOUBLE QUOTE, AS EXPECTED.
      printf("FIRST CHARACTER AFTER 'SAY' IS A DOUBLE QUOTE!!! .\n\n");



      int tokLength = strlen(currToken);
      // FIRST THING TO DO, IF WE KNOW THE FIRST CHAR WAS A DOUBLE QUOTE OF 
      // THIS TOKEN, IS TO THEN CHECK THE LAST CHARACTER OF THIS SAME TOKEN 
      // TO SEE IF IT TOO IS A DOUBLE QUOTE. THIS NEEDS TO BE HANDLED 
      // SEPARATELY THAN IF MORE THAN ONE TOKEN MAKE UP THE MESSAGE BODY.
      
      // IF WE ENTER THIS "if" STATEMENT, THE DOUBLE QUOTE IS EITHER BY
      // ITSELF OF THE START AND END DOUBLE QUOTES ARE IN THE SAME TOKEN.
      if(currToken[tokLength-1] == '"') {

        // EXAMPLE: "abc".
        if(tokLength != 1) {
          printf("\nOMG WTF PLEASE HAPPEN\n\n");
          if(isEnd()) {
            printf("SEEEEEEEEE\n");
            return 0;
          } else {
            // IF WE GET HERE, WE KNOW THERE ARE MORE TOKENS FOLLOWING THE 
            // SECOND DOUBLE QUOTE. HENCE, WE CAN THROW AN ERROR.
            return errorIndex;
          }

        } else {
          // ELSE, THE LENGTH *IS* 1, WE MUST GET REMAINING TOKENS ONE AT A 
          // TIME. FOR EACH ONE, CHECK IF LAST CHAR IS A DOUBLE QUOTE.
          
          while(hasNextToken()) {

            if(isCommaOrWhite()) {
              errorIndex += currTokenLength;
            } else {
              errorIndex += (currTokenLength + 1);
            }
            printf("ERROR INDEX: %d\n", errorIndex);

            char *DQPtr = nextToken();
            if(isNextNull(DQPtr)) {
              printf("TOKEN IS NULL HERE DO SOMETHING DIFFERENT!!!\n");
              return errorIndex;

            } else {
              setCurrToken(DQPtr);
              currTokenLength = strlen(DQPtr);

              tokLength = strlen(currToken);
              printf("\n\nITS LENGTH IS: %d\n\n\n", tokLength);

              if(currToken[tokLength-1] == '"') {
                // IF WE FOUND A TOKEN WHOS LAST CHARACTER IS A DOUBLE QUOTE, WE 
                // KNOW WE MUST BE AT THE END. ALL WE NEED TO DO IS CHECK THAT
                // THERE IS NOTHING ELSE BEFORE END OF THE LINE.
                if(isEnd()) {   
                  return 0;
                } else {                  
                  return errorIndex;
                }
              } else {
                // ELSE, IF THE LAST TOKEN IS *NOT* A DOUBLE QUOTE, WE JUST WANT TO
                // LOOP AGAIN.
              } 
            }
          }
        }

      } else {
        // IF WE GET HERE, WE KNOW WE NEED TO TRY TO LOOK FOR THE SECOND DOUBLE QUOTE.

        while(hasNextToken()) {

          if(isCommaOrWhite()) {
            errorIndex += currTokenLength;
          } else {
            errorIndex += (currTokenLength + 1);
          }
          printf("ERROR INDEX: %d\n", errorIndex);

          char *DQPtr = nextToken();
          if(isNextNull(DQPtr)) {
            printf("TOKEN IS NULL HERE DO SOMETHING DIFFERENT!!!\n");
            return errorIndex;

          } else {
            setCurrToken(DQPtr);
            currTokenLength = strlen(DQPtr);

            tokLength = strlen(currToken);
            printf("\n\nITS LENGTH IS: %d\n\n\n", tokLength);

            if(currToken[tokLength-1] == '"') {
              // IF WE FOUND A TOKEN WHOS LAST CHARACTER IS A DOUBLE QUOTE, WE 
              // KNOW WE MUST BE AT THE END. ALL WE NEED TO DO IS CHECK THAT
              // THERE IS NOTHING ELSE BEFORE END OF THE LINE.
              if(isEnd()) {   
                return 0;
              } else {                  
                return errorIndex;
              }
            } else {
              // ELSE, IF THE LAST TOKEN IS *NOT* A DOUBLE QUOTE, WE JUST WANT TO
              // LOOP AGAIN.
            } 
          }
        }
      }
    }

  }
  printf("THE EXPRESSION ENTERED WAS VALID\n\n");
  return 0;
}
