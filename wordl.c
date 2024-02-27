const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}


int main(int argc, char *argv[]){
        //check the number of arguments
        if (argc != 2){
               printf("Invalid number of command line arguments\n");
               return 0;
        }
        //initialize the number of guess
        int numGuess=0;
        //before it reaches 6,keep guessing
        int tflag=0;
        while(numGuess<7){
        char guess[13]; //13 is longest length of the word
        printf("Enter a guess:");
        scanf("%s",guess);
        int i;
        int j;
        int lenWord = strlen(argv[1]);
        int lenGuess = strlen(guess);
        char word[lenWord];
        strcpy(word, argv[1]);
        //check the length of the guess
        if (lenGuess != lenWord){
                printf("Invalid guess, guess length must match word length\n");
                return 0;
        }
        //we also need a flag system to tracking the colors: a number array, 0 = whi 1 = gre, 2 =yel 
        int flag[13]={0};
        //setting the yellow flag
        char yellowflag[lenWord];
        strcpy(yellowflag,guess);
        //check if got the word or no
        int diff;
        diff = strcmp(guess,word);
        //if user guessed the word
        if(diff == 0){
                setColour(GREEN);
                printf("%s\n",guess);
                setColour(WHITE);
                printf("Finished in %d guesses\n", numGuess+1);
                tflag=1;
                break;}
        //if they didn't
        //Green 
        for(i=0; i<lenWord;i++){
                if (guess[i] == word[i] && guess[i] != '\0'){
                //delete the guessed word and delete it from the yellowflag, and set it to green
                word[i] = '\0';
                yellowflag[i] = '\0';
                flag[i]=1;
                }}
        //now find the yellow flag
         for (int i = 0; i < strlen(guess); i++){
      for (int j = 0; j < strlen(guess); j++){
        if (guess[i] == word[j] && yellowflag[i] != '\0'){
          flag[i] = 2;
          yellowflag[i] = '\0';
          word[j] = '\0';
        }
      }
    }
//now we read the flag array, and print the actual guess
for (int i = 0; i < strlen(guess); i++){
      if (flag[i] == 1)setColour(GREEN);
      else if (flag[i] == 2) setColour(YELLOW);
      else setColour(WHITE);
      printf("%c",guess[i]);
    }
    setColour(WHITE);
    printf("\n");
    numGuess++;
    }
if(tflag!=1)printf("Failed to guess the word: %s\n",argv[1]);}

