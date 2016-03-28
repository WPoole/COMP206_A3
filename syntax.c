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



// NEED FUNCTION THAT CAN COUNT LENGTH OF EACH TOKEN. THIS WILL HELP US
// TO RETURN THE POSITION IN THE STRING WHERE THE ERROR IS FOUND.
// int countChars(char *ptr) {
//   int i = 0;
//   while(ptr[i] != '\0') {
//     i++;
//   }
//   return i;
// }

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

// FUNCTION TO CHECK IF CHARACTER IS A DOUBLE QUOTE, ", OR NOT.
// int isDQ(char *dq) {
//   if(dq[0] == '"') {

//   }
// }

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
  errorIndex = 0;

  // INCREMENT LINE NUMBER COUNT EVERY TIME WE CALL THIS FUNCTION.
  lineNumber++;



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

    // INITIALIZE i VARIABLE TO HELP ITERATE THROUGH "repeat" ARRAY.
    // int i = 0;

    // IF THE FIRST WORD IS "REPEAT", WE WILL BE MAKING COMPARISONS
    // WITH THE "repeat" ARRAY.

    // GET NEXT TOKEN AND CHECK IF IT IS AN INTEGER. IF IT IS, WE'RE GOOD AND
    // CAN CONTINUE. IF IT IS NOT, THEN WE RETURN 0 SINCE IT IS BROKEN.





    // ************************************* BE SURE TO GO THROUGH AND FIX ALL THE STUFF LIKE THE LINE BELOW WHERE I TRY
    // TO SET THE TOKEN WITHOUT FIRST CHECKING IF ITS NULL. THEY ALL GIVE SEG FAULTS. 
    // *******************************************!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*************************
    setCurrToken(nextToken());
    currTokenLength = strlen(currToken);

    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;
      setCurrToken(nextToken());
      currTokenLength = strlen(currToken);
    }

    if(!atoi(currToken)) {
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
    setCurrToken(nextToken());
    currTokenLength = strlen(currToken);

    // CHECK FOR WHITESPACES AGAIN.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;
      setCurrToken(nextToken());
      currTokenLength = strlen(currToken);
    }
    printf("TIMES: %s\n", currToken);
    if(strcmp(currToken, repeat[i])) {
      printf("Invalid TIMES.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }

    // NOW AT THIS POINT WE SHOULD HAVE IN FRONT OF US THE "COMMA-SEPARATED-
    // LIST-OF-COMMANDS". SO WE LOOP OVER UNTIL WE GET TO THE END OF THIS LIST.
    if(hasNextToken()) {
      setCurrToken(nextToken());
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
      setCurrToken(nextToken());
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

    // INITIALIZE i VARIABLE TO HELP ITERATE THROUGH "whileNot" ARRAY.
    // int i = 0;

    // IF THE FIRST WORD IS "WHILE", WE WILL BE MAKING COMPARISONS
    // WITH THE "whileNot" ARRAY.

    // GET NEXT TOKEN AND CHECK IF IT IS "NOT". IF IT IS, WE'RE GOOD AND
    // CAN CONTINUE. IF IT IS NOT, THEN WE RETURN 0 SINCE IT IS BROKEN.
    setCurrToken(nextToken());
    currTokenLength = strlen(currToken);

    // INCREMENT "i" SO WE CAN COMPARE TOKEN WITH "NOT" FROM ARRAY.
    i++;
    printf("*****!!!!***** VARIABLE i IS: %d *****!!!!*****\n", i);

    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;
      setCurrToken(nextToken());
      currTokenLength = strlen(currToken);
    }
    printf("NOT: %s\n", currToken);

    if(strcmp(currToken, whileNot[i])) {
      printf("Invalid 'NOT'.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }


    // INCREMENT "i" SO WE CAN COMPARE WITH NEXT ELEMENT IN "whileNot" ARRAY.
    // HERE WE ARE LOOKING FOR THE WORD "DETECTMARKER".
    i++;
    printf("*****!!!!***** VARIABLE i IS: %d *****!!!!*****\n", i);
    // GET AND SET NEXT TOKEN, THEN CHECK IF IT'S LEGIT.
    setCurrToken(nextToken());
    currTokenLength = strlen(currToken);

    // CHECK FOR WHITESPACES AGAIN.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;
      setCurrToken(nextToken());
      currTokenLength = strlen(currToken);
    }
    printf("DETECTMARKER: %s\n", currToken);

    if(strcmp(currToken, whileNot[i])) {
      printf("Invalid DETECTMARKER.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }


    // INCREMENT "i" SO WE CAN COMPARE WITH NEXT ELEMENT IN "whileNot" ARRAY.
    // HERE WE ARE LOOKING FOR THE WORD "DO".
    i++;
    printf("*****!!!!***** VARIABLE i IS: %d *****!!!!*****\n", i);
    // GET AND SET NEXT TOKEN, THEN CHECK IF IT'S LEGIT.
    setCurrToken(nextToken());
    currTokenLength = strlen(currToken);

    // CHECK FOR WHITESPACES AGAIN.
    while(isWhiteSpace()) {
      errorIndex += currTokenLength;
      setCurrToken(nextToken());
      currTokenLength = strlen(currToken);
    }
    printf("DO: %s\n", currToken);

    if(strcmp(currToken, whileNot[i])) {
      printf("Invalid DO.\n\n");
      return errorIndex;
    } else {
      errorIndex += (currTokenLength + 1);
    }


    // NOW AT THIS POINT WE SHOULD HAVE IN FRONT OF US THE "COMMA-SEPARATED-
    // LIST-OF-COMMANDS". SO WE LOOP OVER UNTIL WE GET TO THE END OF THIS LIST.
    if(hasNextToken()) {
      setCurrToken(nextToken());
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
      setCurrToken(nextToken());
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

    // CHECK IF NEXT TOKEN IS NULL AND THEN SET IT.
    char *nextPtr = nextToken();
    if(isNextNull(nextPtr)) {
      return errorIndex;
    } else {
      setCurrToken(nextToken());
    }


    // FIRST GET RID OF ALL WHITESPACES.
    while(isWhiteSpace()) {

      char *ptrToken = nextToken();
      if(isNextNull(ptrToken)) {
        // IF WE GET TO A NULL AT THIS POINT, WE KNOW THERE MUST NOT HAVE BEEN
        // ANY MESSAGE OR OTHER TOKENS ENTERED, SO WE RETURN 0 TO INDICATE ERROR.
        printf("YOU MUST ENTER A MESSAGE AFTER USING 'SAY'. \n");
        return errorIndex;
      } else {
        setCurrToken(ptrToken);

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
            return 45;
          } else {
            // IF WE GET HERE, WE KNOW THERE ARE MORE TOKENS FOLLOWING THE 
            // SECOND DOUBLE QUOTE. HENCE, WE CAN THROW AN ERROR.
            return errorIndex;
          }

        } else {
          // ELSE, THE LENGTH *IS* 1, WE MUST GET REMAINING TOKENS ONE AT A 
          // TIME. FOR EACH ONE, CHECK IF LAST CHAR IS A DOUBLE QUOTE.
          while(hasNextToken()) {

            char *DQPtr = nextToken();

            if(isNextNull(DQPtr)) {
              return errorIndex;

            } else {
              setCurrToken(DQPtr);
              printf("\n\nTHE CURRENT TOKEN IS THE FOLLOWING: %s\n\n\n", DQPtr);

              tokLength = strlen(currToken);
              printf("\n\nITS LENGTH IS: %d\n\n\n", tokLength);

              if(currToken[tokLength-1] == '"') {
                // IF WE FOUND A TOKEN WHOS LAST CHARACTER IS A DOUBLE QUOTE, WE 
                // KNOW WE MUST BE AT THE END. ALL WE NEED TO DO IS CHECK THAT
                // THERE IS NOTHING ELSE BEFORE END OF THE LINE.
                if(isEnd()) {
                  return 50;
                } else {
                  return errorIndex;
                }
              } 
            }
          }
        }

      } else {
        // IF WE GET HERE, WE KNOW WE NEED TO TRY TO LOOK FOR THE SECOND DOUBLE QUOTE.
          
        while(hasNextToken()) {

          char *DQPtr = nextToken();

          if(isNextNull(DQPtr)) {
            return errorIndex;

          } else {
            setCurrToken(DQPtr);
            printf("\n\nTHE CURRENT TOKEN IS THE FOLLOWING: %s\n\n\n", DQPtr);

            tokLength = strlen(currToken);
            printf("\n\nITS LENGTH IS: %d\n\n\n", tokLength);

            if(currToken[tokLength-1] == '"') {
              // IF WE FOUND A TOKEN WHOS LAST CHARACTER IS A DOUBLE QUOTE, WE 
              // KNOW WE MUST BE AT THE END. ALL WE NEED TO DO IS CHECK THAT
              // THERE IS NOTHING ELSE BEFORE END OF THE LINE.
              if(isEnd()) {
                return 50;
              } else {
                return errorIndex;
              }
            } 
          }
        }
      }
    }

  }
  printf("THE EXPRESSION ENTERED WAS VALID\n\n");
  return 0;
}
