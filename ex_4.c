/***********************
* @author Dan Saada
* @version Hanging-Man
* @since 30/11/2021
***********************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <string.h>

#define SIZE_OF_STRING 21
#define NUM_OF_STRINGS 16
#define MAX_MISTAKES 5
#define ASTERISK '*'
#define BOTTOM_DASH '_'
#define SPACE ' '
#define COMMA ","
#define COLON ":"
#define GREEN "\033[0;32m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_RED "\033[1;31m"
#define BLUE "\033[0;34m"
#define SET_COLOR "\033[0m"

/******************
* Function Name: printChoice
* Input: char str1[][21], int counter
* Output: None
* Function Operation: This function is an auxiliary function that prints a numbered list of strings.
* ******************/
void printChoice(char str1[][SIZE_OF_STRING], int counter) {
    //i=1 because we dont want to print the clue.
    printf("choose an option:\n");
    for (int i = 1; i < counter; i++) {
        printf("%d: %s\n", i, str1[i]);
    }
}

/******************
* Function Name: alphaSort
* Input: char str1[][20], int counter
* Output: None
* Function Operation: This function is an auxiliary function that sorts the options entered by the user,
                      in a lexicographic manner, using bouble sort method. 
* ******************/
void alphaSort(char str1[][SIZE_OF_STRING], int counter) {
    char temp[SIZE_OF_STRING];
    for (int i = 1; i < counter; i++) {
        //in the second for lop "counter - i" : becuase the last i organs are allready sorted.
        for (int j = 1; j < counter - i; j++) {
            //j<-->j+1 : sorting between two close organs
            if (strcmp(str1[j], str1[j + 1]) > 0) {
                strcpy(temp, str1[j]);
                strcpy(str1[j], str1[j + 1]);
                strcpy(str1[j + 1], temp);
            }
        }
    }
}

/******************
* Function Name: getChoice
* Input: char str1[][20]
* Output: counter - number of choices the user has.
* Function Operation: This function scans the clue and the selection of options entered by the user,
                      and saves them in a two-dimensional array.
                      The function is then assisted by 2 auxiliary functions which are called: alphaSort, printChoice
                      So that finally, the selection of options entered by the user is numbered in a printed list.
* ******************/
int getChoice(char str1[][SIZE_OF_STRING]) {
    //userInput = An intermediate array designed to store the input from the user for the first time(16*(20+1)=340).
    char userInput[SIZE_OF_STRING * (NUM_OF_STRINGS+1)], *token;
    int counter = 0;
    printf("Welcome to the Hanging-Man game!\n"
        "Please enter a category and optional choices separated by a comma:\n"
        "For example: Food:pizza,apple,pasta\n");
    printf(GREEN);
    scanf("%[^\n]", userInput);
    printf(SET_COLOR);
    //token = A pointer that points to the first string in the userInput array.
    token = strtok(userInput, COLON);
    //Inserting the strings into the str1 array.
    while (token != NULL) {
        /*copying the value of token and inserting the value in a certain order inside the two - dimensional array.
          after insrting the clue in the str1[0] the condition of the strtok changes from ":" to ",".
        */
        strcpy(str1[counter], token);
        token = strtok(NULL, COMMA);
        counter++;
    }
    alphaSort(str1, counter);
    printChoice(str1, counter);
    return counter - 1;
}

/******************
* Function Name: chooseChoice
* Input: char str1[][20]
* Output: str1[num]
* Function Operation: This function scans the user's selection from the list of options he himself has entered,
*                     and returns the specific "string" from that list.
                      If the user enters a number that is not in the list he will get a massage that will ask him
                      to choose again.
* ******************/
char* chooseChoice(char str1[][SIZE_OF_STRING], int numOfChoices) {
    int num;
    printf(GREEN);
    scanf("%d", &num);
    printf(SET_COLOR);
    //checking the user chooses from the list.
    while (num > numOfChoices || num <= 0) {
        printf("Please choose a number from the list above.\n");
        printf(GREEN);
        scanf("%d", &num);
        printf(SET_COLOR);
    }
    return str1[num];
}

/******************
* Function Name: lines
* Input: char word[20], char found[20]
* Output:int count
* Function Operation: This function matches between the number of bottom dashs ('_') that appear in the "found" array,
                      and the number of characters that appear in the "word" array (the word that the user choosed).
                      When the function detects a space character in the "word" array, it also knows to enter a space
                      character in the "found" array.
                      At the end, the function also returns the size of the string not including spaces.
* ******************/
int lines(char word[SIZE_OF_STRING], char found[SIZE_OF_STRING]) {
    int i = 0, count = 0;
    while (word[i] != NULL) {
        if (word[i] == SPACE) {
            found[i] = SPACE;
        }
        else {
            found[i] = BOTTOM_DASH;
            count++;
        }
        i++;
    }
    return count;
}

/******************
* Function Name: printHangingMan
* Input: int mistakes
* Output: None
* Function Operation: This function is an auxiliary function used by the "theGame" function that prints the current
                      state of number of mistakes of the user, by a visual illustration of a "Hanging man".
* ******************/
void printHangingMan(int mistake) {
    switch (mistake) {
        case 0:
            printf(" _________________\n"
                "|                |\n"
                "|                |\n"
                "|                |\n"
                "|                |\n"
                "|                |\n"
                "|________________|\n"
            );
            break;
        case 1:
            printf(" _________________\n"
                   "|                |\n"
                   "|  **            |\n"
                   "|  **            |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n"
            );
            break;
        case 2:
            printf(" _________________\n"
                   "|                |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n"
            );
            break;
        case 3:
            printf(" _________________\n"
                   "|  --            |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n"
            );
            break;
        case 4:
            printf(" _________________\n"
                   "|  --        --  |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n"
            );
            break;
        case 5:
            printf(" _________________\n"
                   "|  --        --  |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "| \\/\\/\\/\\/\\/\\/\\  |\n"
                   "|________________|\n"
            );
            break;
        default:
            break;
    }
}

/******************
* Function Name: gameResult
* Input: int mistakes, char word[], int countLines
* Output: None
* Function Operation: This function is an auxiliary function used by the "theGame" function that prints the
                      game result according to the data it receives.
* ******************/
void gameResult(int mistakes, char word[], int countLines) {
    //win
    if (countLines == 0) {
        printHangingMan(mistakes);
        printf(BOLD_GREEN);
        printf("The word is: %s, YOU WIN!\n", word);
        printf(SET_COLOR);
    }
    //lose
    if (mistakes == MAX_MISTAKES) {
        printHangingMan(mistakes);
        printf(BOLD_RED);
        printf("The word is: %s, GAME OVER!\n", word);
        printf(SET_COLOR);
    }
}

/******************
* Function Name: theGame
* Input: char found[], char word[], int countLines, char clue[21]
* Output: None
* Function Operation: This function initializes the game.
                      During the game the user enters characters in order to correctly guess the word.
                      If the user was able to guess the word in less than MAX_MISTAKES he will be sent a message
                      that he won, otherwise he will be sent a message that he lost.
                      The user receives in each attempt a message that asks him if he wants a clue, if the user wants
                      to get a clue he enters '*'. After geting the clue the message will stop appearing on the screen.
                      In addition, each time the user enters a character (except '*') he will receive a message on the
                      next attempt that will print the letters he has already tried.
                      If the user still chooses to try a letter that he has already tried, the program will print to
                      him that he has already tried this letter and will not consider the same letter as another
                      mistake if it is indeed a mistake in the first time.
                      As long as the game continues, in each attempt the user will be able to know his condition in
                      terms of mistakes with the help of an auxiliary function called "printHangingMan" that prints a
                      visual illustration of a hanging man.
                      Each time the user guesses incorrectly, another part is added to the hanging man.
                      The game ends when the user wins or loses.
* ******************/
void theGame(char found[], char word[], int countLines, char clue[SIZE_OF_STRING]) {
    int i = 0, mistakes = 0, flagIsClue = 0, flagIsTried = 0, flagIsPrint = 0, temp = countLines;
    //An array that contains characters that the user guesses.
    char alreadyTried[30] = { "\0" };
    char attempt = "\0";
    char enter;
    //Conditions for game continuity.
    while (mistakes < MAX_MISTAKES && countLines > 0) {
        flagIsTried = 0;
        printHangingMan(mistakes);
        //Print the bottom dash lines
        printf("%s\n", found);
        //after getting the clue, flag changes to 1, and the program would stop asking if the user wants a clue.
        if (flagIsClue == 0) {
            printf("do you want a clue? press -> *\n");
        }
        printf("The letters that you already tried:");
        //at the first itertion the user didn't try any character yet, so no character would be print out on the screen
        if (flagIsPrint >= 1) {
            printf(" %c", alreadyTried[0]);
        }
        if (strlen(alreadyTried) > 0) {
            for (i = 1; i < strlen(alreadyTried); i++) {
                printf(", %c", alreadyTried[i]);
            }
        }
        printf("\n");
        flagIsPrint++;
        printf("please choose a letter:\n");
        i = 0;
        printf(GREEN);
        scanf("%*[^\n]");
        scanf("%*[^\n]%*c");
        scanf("%c %c", &enter, &attempt);
        printf(SET_COLOR);
        //Check if the user has already tried to entered a specific character.
        while (alreadyTried[i] != NULL) {
            if (alreadyTried[i] == attempt) {
                printf("You've already tried that letter.\n");
                flagIsTried = 1;
                // when we find the letter we can stop to search it.
                break;
            }
            i++;
        }
        if (flagIsTried == 1) {
            continue;
        }
        //the program doesn't print '*' as a character that the user already tried.
        if (attempt != ASTERISK) {
           alreadyTried[i] = attempt;
        }
        i = 0;
        //giving the clue to the user.
        if (attempt == ASTERISK) {
            if (flagIsClue == 0) {
                printf("the clue is:");
                printf(BLUE);
                printf(" %s.\n", clue);
                printf(SET_COLOR);
                flagIsClue = 1;
            }
            continue;
        }
        //checking if the user was able to correctly guess a character in the selected word.
        while (word[i] != NULL) {
            if (attempt == word[i]) {
                found[i] = word[i];
                //when countLines reachs 0 the user wins.
                countLines--; 
            }
            i++;
        }
        i = 0;
        
        //the user didn't guessed correctly
        if (temp == countLines) {
            //when mistakes reachs MAX_MISTAKES the user loses.
            mistakes++;
        }
        temp = countLines;
    }
    //printing the game's result
    gameResult(mistakes, word, countLines);
}

/******************
* Function Name: main
* Input: None
* Output: None
* Function Operation: This function initializes the program.
* ******************/
void main() {
    char str1[NUM_OF_STRINGS][SIZE_OF_STRING];
    //Getting all the options from the user and saving them in a two-dimensional array.
    int numOfChoices = getChoice(str1);
    char word[SIZE_OF_STRING] = { "\0" };
    //Saving the string that the user choosed from the list he inserted in an array called word.
    strcpy(word, chooseChoice(str1, numOfChoices));
    //found = An array that will contain the bottom dash instead of letters in the guessing phase.
    char found[SIZE_OF_STRING] = { "\0" };
    //countLines = An integer containing the number of bottom dashs
    int countLines = lines(word, found);
    theGame(found, word, countLines, str1[0]);
}