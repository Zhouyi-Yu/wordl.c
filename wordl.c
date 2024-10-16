#include <stdio.h>
#include <string.h>

const char * const WHITE = "\x1b[0m";
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * current = NULL;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}

int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc != 2) {
        printf("Invalid number of command line arguments\n");
        return 0;
    }

    // Initialize the number of guesses
    int numGuess = 0;
    int tflag = 0;

    // Before it reaches 7 guesses, keep guessing
    while (numGuess < 7) {
        char guess[13]; // 13 is the longest length of the word
        printf("Enter a guess: ");
        scanf("%s", guess);

        int i, j;
        int lenWord = strlen(argv[1]);
        int lenGuess = strlen(guess);
        char word[lenWord];
        strcpy(word, argv[1]);

        // Check the length of the guess
        if (lenGuess != lenWord) {
            printf("Invalid guess, guess length must match word length\n");
            return 0;
        }

        // Flag system for tracking the colors: 0 = white, 1 = green, 2 = yellow
        int flag[13] = {0};

        // Setting the yellow flag
        char yellowflag[lenWord];
        strcpy(yellowflag, guess);

        // Check if the guess matches the word
        if (strcmp(guess, word) == 0) {
            setColour(GREEN);
            printf("%s\n", guess);
            setColour(WHITE);
            printf("Finished in %d guesses\n", numGuess + 1);
            tflag = 1;
            break;
        }

        // Green check
        for (i = 0; i < lenWord; i++) {
            if (guess[i] == word[i] && guess[i] != '\0') {
                word[i] = '\0';  // Mark as guessed
                yellowflag[i] = '\0';
                flag[i] = 1;  // Set green flag
            }
        }

        // Yellow check
        for (i = 0; i < lenGuess; i++) {
            for (j = 0; j < lenWord; j++) {
                if (guess[i] == word[j] && yellowflag[i] != '\0') {
                    flag[i] = 2;  // Set yellow flag
                    yellowflag[i] = '\0';
                    word[j] = '\0';
                    break;
                }
            }
        }

        // Display the guess with corresponding colors
        for (i = 0; i < lenGuess; i++) {
            if (flag[i] == 1) setColour(GREEN);
            else if (flag[i] == 2) setColour(YELLOW);
            else setColour(WHITE);
            printf("%c", guess[i]);
        }
        setColour(WHITE);
        printf("\n");

        numGuess++;
    }

    // If the word is not guessed
    if (tflag != 1) {
        printf("Failed to guess the word: %s\n", argv[1]);
    }

    return 0;
}
