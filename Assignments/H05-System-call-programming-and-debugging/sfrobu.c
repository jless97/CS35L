#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#define SP ' '
#define TRUE 1
#define FALSE 0

struct character {
    char newCharacter[1];
    ssize_t isEOF;
};

struct character fetchCharacter();
char *increaseLetterArraySize(char *letters, size_t numLetters);
char **increaseWordArraySize(char **words, size_t numWords);
int frobcmp(char const *a, char const *b);
int compareWords(const void* a, const void* b);
int ffrobcmp(char const *a, char const *b);
int fcompareWords(const void* a, const void*b);
void writeOutput(char **finalWordArray, size_t numWords);
void freeArrays(char **finalWordArray, char *finalLetter, size_t numWords);

int main(int argc, char *argv[])
{
    //Use fstat to check that the file is of the correct type from STDIN
    struct stat stbuf;
    if (fstat(0, &stbuf) < 0) {
        fprintf(stderr, "Error: fstat!");
        exit(1);
    }
    
    int fOption = FALSE;
    if (argc >= 2 && 0 == strcmp(argv[1], "-f"))
        fOption = TRUE;
    
    //Create the letter and word counters for static implementation
    size_t i, j, letterCount = 0, wordCount = 0;
    char **wordArray, *staticArray;
    
    //If regular file => allocate enough memory initially
    if (S_ISREG(stbuf.st_mode)) {
        staticArray = (char *)malloc(stbuf.st_size * sizeof(char));
        if ((read(0, staticArray, stbuf.st_size)) > 0) {
            for (i = 0; i < stbuf.st_size; i++) {
                if (staticArray[i] != SP && staticArray[i + 1] == EOF)
                    staticArray[i] = SP;
                if (staticArray[i] == SP) {
                    wordCount++;
                }
            }
        }
        
        //For the not growing regular file, add the words to the word array
        wordArray = (char **)malloc(wordCount * sizeof(char *));
        wordCount = 0;
        
        for (i = 0; i < stbuf.st_size; i++) {
            if (i == 0 && staticArray[i] != SP) {
                wordArray[wordCount++] = &staticArray[i];
            }
            if (staticArray[i] == SP) {
                if (staticArray[i + 1] != EOF && staticArray[i + 1] != SP) {
                    wordArray[wordCount++] = &staticArray[i + 1];
                }
            }
        }
    }
    //If the regular file grows while you are reading it:
    else {
        wordArray = (char **)malloc(sizeof(char *));
    }
    
    //Create the letter array
    char *letterArray = (char *)malloc(sizeof(char));

    //Reset letter and word counters for the dynamic implementation
    letterCount = 0;
    
    //Create two variables to keep track of the current and next letter from STDIN
    //Use of a struct to account for current byte and
    struct character currentLetter = fetchCharacter();
    struct character nextLetter = fetchCharacter();

    //Keep reading until the file ends
    while (currentLetter.isEOF > 0) {
        //Add a character to the letter array
        //Resize with new character added
        letterArray[letterCount] = currentLetter.newCharacter[0];
        letterArray = increaseLetterArraySize(letterArray, letterCount);
        
        //If a space is reached, then this is the end of the current word
        if (currentLetter.newCharacter[0] == SP) {
            //Add word to the word array
            //Resize with new word added
            wordArray[wordCount++] = letterArray;
            wordArray = increaseWordArraySize(wordArray, wordCount);
            
            //Reset the letter array
            letterArray = NULL;
            letterArray = (char *)malloc(sizeof(char));
            letterCount = -1;
        }
        
        //If there is a proper space at the EOF, and EOF is reached, then done
        if (currentLetter.newCharacter[0] == SP && nextLetter.isEOF == 0) {
            break;
        }
        //If the EOF is missing a space character, then add one as requested
        else if (currentLetter.newCharacter[0] != SP && nextLetter.isEOF == 0) {
            currentLetter.newCharacter[0] = SP;
            letterCount++;
            continue;
        }
        //If there is a line with multiple spaces in a row, then remove them
        else if (currentLetter.newCharacter[0] == SP &&
                 nextLetter.newCharacter[0] == SP) {
            while (currentLetter.newCharacter[0] == SP) {
                currentLetter = fetchCharacter();
            }
            nextLetter = fetchCharacter();
            letterCount++;
            continue;
        }
        
        //Normal Scenario: Both currentLetter and nextLetter are valid characters
        currentLetter.newCharacter[0] = nextLetter.newCharacter[0];
        nextLetter = fetchCharacter();
        letterCount++;
    }
    
    //Sort the output normally or with -f option (i.e. toupper)
    if (fOption) {
        qsort(wordArray, wordCount, sizeof(char *), fcompareWords);
    }
    else {
        qsort(wordArray, wordCount, sizeof(char *), compareWords);
    }
    
    //Write the output after the words are all collected
    writeOutput(wordArray, wordCount);

    //Free memory
    freeArrays(wordArray, letterArray, wordCount);
    
    exit(0);
}

//getchar() with error check
struct character fetchCharacter()
{
    struct character createCharacter;
    createCharacter.isEOF = read(0, createCharacter.newCharacter, 1);
    
    if(createCharacter.isEOF < 0) {
        fprintf(stderr, "Error: Input/Output/Memory Allocation Failure!");
        exit(1);
    }
    return createCharacter;
}

//Resize the letter array as new character is added
char *increaseLetterArraySize(char *letters, size_t numLetters)
{
    char *newLetterArray = (char *)malloc(sizeof(char));
    newLetterArray = realloc(letters, (numLetters + 2) * sizeof(char));
    if(newLetterArray == NULL) {
        fprintf(stderr, "Error: Input/Output/Memory Allocation Failure!");
        exit(1);
    }
    
    return newLetterArray;
}

//Resize the word array as new word is added
char **increaseWordArraySize(char **words, size_t numWords)
{
    char **newWordArray = (char **)malloc(sizeof(char *));
    newWordArray = realloc(words, (numWords + 2) * sizeof(char *));
    if(newWordArray == NULL) {
        fprintf(stderr, "Error: Input/Output/Memory Allocation Failure!");
        exit(1);
    }
    
    return newWordArray;
}

int ffrobcmp(char const *a, char const *b)
{
    char afrob, bfrob;
    for (;; a++, b++) {
        afrob = toupper(*a ^ 42);
        bfrob = toupper(*b ^ 42);
        if (*a == SP && *b == SP)
            return 0;
        else if (*a == SP || (afrob < bfrob))
            return -1;
        else if (*b == SP || (bfrob < afrob))
            return 1;
    }
}

//Properly format parameters for qsort
int fcompareWords(const void* a, const void* b)
{
    return ffrobcmp(*((const char **) a), *((const char **) b));
}

int frobcmp(char const *a, char const *b)
{
    char afrob, bfrob;
    for (;; a++, b++) {
        afrob = *a ^ 42;
        bfrob = *b ^ 42;
        if (*a == SP && *b == SP)
            return 0;
        else if (*a == SP || (afrob < bfrob))
            return -1;
        else if (*b == SP || (bfrob < afrob))
            return 1;
    }
}

//Properly format parameters for qsort
int compareWords(const void* a, const void* b)
{
    return frobcmp(*((const char **) a), *((const char **) b));
}

//Write output until the space char is hit (i.e. EOF)
void writeOutput(char **finalWordArray, size_t numWords)
{
    char currentByte[1];
    for (size_t i = 0; i < numWords; i++) {
        for (size_t j = 0; ; j++) {
            if(finalWordArray[i][j] == SP)
                break;
            currentByte[0] = finalWordArray[i][j];
            write(1, currentByte, sizeof(char));
        }
        currentByte[0] = SP;
        write(1, currentByte, sizeof(char));
    }
}

//Free memory
void freeArrays(char **finalWordArray, char *finalLetterArray, size_t numWords)
{
    for (size_t i = 0; i < numWords; i++) {
        free(finalWordArray[i]);
    }
    free(finalWordArray);
    free(finalLetterArray);
}

